#include<condition_variable>
#include<watchdog.h>
#include<portal/network.h>
#include<functional>
#include<fpkg.h>
#include<thread>
#include<queue>
#include<mutex>
#include<map>
#include<uimainchat.h>
#include<QMessageBox>
#include<json/json.h>
#include<iostream>
#include<uicr.h>
using namespace std;

EXTERN_PKG_QM
EXTERN_WATCHDOGS
extern UIMainchat *mainchat;
extern string g_LoginIdentity;

static map<uint16_t, function<int(pkg_t)> > mPkgfunc;
extern condition_variable pcv_sendchanged;

mutex pmtx_recvchanged;
condition_variable pcv_recvchanged;

map<string, string> mUnString; //un->chatmsg;
map<string, string> mGnString; //gn->chatmsg;
map<int, pair<string,int>> friendList;
map<int, pair<string,int>> groupList;
map<string, map<int, string>> groupmemberList;

void dpkg_init() {
    mPkgfunc[PT_ADDFRI_REQ] = dpkg_addfriend_req;
    mPkgfunc[PT_ADDFRI_RES] = dpkg_addfriend_res;
    mPkgfunc[PT_DELFRI_RES] = dpkg_delfriend;
    mPkgfunc[PT_ONLINE] = dpkg_online;
    mPkgfunc[PT_OFFLINE] = dpkg_offline;
    mPkgfunc[PT_FL] = dpkg_friendlist;
    mPkgfunc[PT_GL] = dpkg_grouplist;
    mPkgfunc[PT_GM] = dpkg_gmlist;
    mPkgfunc[PT_MSG_GRP] = dpkg_msg_grp;
    mPkgfunc[PT_MSG_FRI] = dpkg_msg_fri;
    mPkgfunc[PT_PKEY_REQ] = dpkg_pkey_req;
    mPkgfunc[PT_PKEY_RES] = dpkg_pkey_req;
    mPkgfunc[PT_MUTE_RES] = dpkg_mute_res;
    mPkgfunc[PT_MGRC_NOT] = dpkg_mgrc_not;
    mPkgfunc[PT_EXGRP_NOT] = dpkg_exgrp_not;
    mPkgfunc[PT_ENGRP_RES] = dpkg_engrp_res;
    mPkgfunc[PT_DISGRP_NOT] = dpkg_disgrp_not;
    mPkgfunc[PT_DISMUTE_RES] = dpkg_dismute_res;
    mPkgfunc[PT_FETCHCR_RES] = dpkg_fetchcr_res;
    mPkgfunc[PT_CRGRP_RES] = dpkg_crgrp_res;
    mPkgfunc[PT_EXGRP_PCNOT] = dpkg_exgrp_pcnot;
    mPkgfunc[PT_ENGRP_PCNOT] = dpkg_engrp_pcnot;
    mPkgfunc[PT_FCH_RES] = dpkg_fch;
    thread dpkg_thread(dpkg_distribute);
    dpkg_thread.join();
}

void dpkg_distribute() {
    while (WATCHDOG_DPKG) {
        unique_lock<mutex> pul_recvchanged(pmtx_recvchanged);
        pcv_recvchanged.wait(pul_recvchanged);

        while (true) {
            pkglk_recv.lock();
            if (!qpkgRecv.empty()) {
                pkg_t thispkg = qpkgRecv.front();
                qpkgRecv.pop();
                pkglk_recv.unlock();
                cerr << thispkg.jsdata << endl;
                mPkgfunc[thispkg.head.wopr](thispkg);
            } else {
                pkglk_recv.unlock();
                break;
            }
        }
    }

}

int dpkg_fch(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    uiCR *cr = new uiCR(QString::fromStdString(root["rc"].asString()));
    cr->setAttribute(Qt::WA_DeleteOnClose);
    cr->show();
    return 0;
}

int dpkg_grouplist(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    groupList.clear();
    for (auto i = 0u; i < root["gl"].size(); i++) {
        auto j = make_pair(root["gl"][i]["gn"].asString(), root["gl"][i]["gpw"].asInt());
        groupList[i] = j;
    }
    mainchat->puiRefreshGL();
    return 0;
}

int dpkg_gmlist(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    groupmemberList.clear();
    cerr << "\033[33msize=" << root["gml"].size() << "\033[0m\n";
    for (auto i = 0u; i < root["gml"].size(); i++) {
        auto j = root["gml"][i].asString();
        cerr << "\033[33mj=" << j << "\033[0m\n";
        groupmemberList[root["gn"].asString()][i] = j;
    }
    mainchat->puiRefreshGM();
    return 0;
}

int dpkg_friendlist(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    friendList.clear();
    for (auto i = 0u; i < root["fl"].size(); i++) {
        auto j = make_pair(root["fl"][i]["fun"].asString(), root["fl"][i]["fst"].asInt());
        friendList[i] = j;
    }
    mainchat->puiRefreshFL();
    return 0;
}

int dpkg_addfriend_req(pkg_t pkg) {
    Json::Value root, res;
    Json::Reader reader;
    Json::FastWriter writer;
    reader.parse(pkg.jsdata, root);
    auto ans = QMessageBox::question(NULL, "PChat", QString(root["un"].asCString())
            + "想要添加您作为好友， 是否同意？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    res["un"] = root["un"].asString();
    res["afwho"] = root["afwho"].asString();
    if (ans == QMessageBox::Yes) {
        res["agr"] = 0;
    } else {
        res["agr"] = 1;
    }

    pkg_t recvpkg;
    recvpkg.jsdata = writer.write(res);
    recvpkg.head.wopr = PT_ADDFRI_APP;
    recvpkg.head.datasize = sizeof(pkg_head_t) + recvpkg.jsdata.length();

    pkglk_send.lock();
    qpkgSend.push(recvpkg);
    pcv_sendchanged.notify_all();
    pkglk_send.unlock();
    return 0;
}


int dpkg_online(pkg_t pkg) {
    return 0;
}

int dpkg_offline(pkg_t pkg) {

    return 0;
}

int dpkg_msg_grp(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;
    reader.parse(pkg.jsdata, root);
    mGnString[root["gn"].asString()] +=root["sd"].asString() + ": " + root["msg"].asString() + "\n";

    if (root["sd"] != g_LoginIdentity) {
        string sts = string("群 ") + root["gn"].asString() + string(" 发来了新消息！");
        mainchat->puiSetStatus(QString(sts.c_str()));
    }
    mainchat->RefreshMsg();
    return 0;
}

int dpkg_msg_fri(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;
    reader.parse(pkg.jsdata, root);
    string id;
    if (root["sd"].asString() == g_LoginIdentity) {
        id = root["rv"].asString();
    } else {
        id = root["sd"].asString();
    }
    mUnString[id] += root["sd"].asString() + ": " + root["msg"].asString() + "\n";
    if (root["sd"] != g_LoginIdentity) {
        string sts = string("你的好友 ") + id + string(" 发来了新消息！");
        mainchat->puiSetStatus(QString(sts.c_str()));
    }
    mainchat->RefreshMsg();
    return 0;
}

int dpkg_pkey_req(pkg_t pkg) {
    return 0;
}

int dpkg_pkey_res(pkg_t pkg) {
    return 0;
}

int dpkg_fetchcr_res(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    uiCR *cr = new uiCR(QString::fromStdString(root["rc"].asString()));
    cr->setAttribute(Qt::WA_DeleteOnClose);
    cr->show();
    return 0;
}

int dpkg_engrp_pcnot(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    QMessageBox::information(NULL, "PChat", QString("您加入群") +
            root["gn"].asCString() + "的请求已经被服务器拒绝！\n该群可能不存在。", QMessageBox::Ok, QMessageBox::Ok);
}


int dpkg_delfriend(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    QMessageBox::information(NULL, "PChat", QString(root["un"].asCString()) + "已经成功删除了" +
            root["dfwho"].asCString() + "！", QMessageBox::Ok, QMessageBox::Ok);
    mainchat->pntRefreshFL();
    return 0;
}

int dpkg_addfriend_res(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);

    if (root["un"].asString() == root["afwho"].asString())
        return 0;
    if (root["res"].asInt() == 0)
        QMessageBox::information(NULL, "PChat", QString(root["afwho"].asCString()) + "已经同意添加了" +
                root["un"].asCString() + "！", QMessageBox::Ok, QMessageBox::Ok);
    else
        QMessageBox::information(NULL, "PChat", QString(root["afwho"].asCString()) + "拒绝添加了" +
                root["un"].asCString() + "！", QMessageBox::Ok, QMessageBox::Ok);
    mainchat->pntRefreshFL();
    return 0;
}

int dpkg_mute_res(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    QMessageBox::information(NULL, "PChat", QString("您已经成功的屏蔽了用户") + root["mtwho"].asCString() + "！",
            QMessageBox::Ok, QMessageBox::Ok);
    mainchat->pntRefreshFL();
    return 0;
}

int dpkg_mgrc_not(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    mainchat->puiSetStatus("您加入的群" + QString(root["gn"].asCString()) + "改变了管理员。");
    return 0;
}

//TODO: 刷新群成员列表！！！！
int dpkg_exgrp_not(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    mainchat->puiSetStatus("您加入的群" + QString(root["gn"].asCString()) + "有群成员退出。");
    return 0;
}

int dpkg_engrp_res(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    QMessageBox::information(NULL, "PChat", QString(root["un"].asCString()) +  "已经加入了群"
            + root["gn"].asCString() + "！", QMessageBox::Ok, QMessageBox::Ok);
    return 0;
}

//TODO: 刷新群列表！！！
int dpkg_disgrp_not(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    QMessageBox::information(NULL, "PChat", QString("你加入的群") + root["gn"].asCString() + "已经被群主解散！",
            QMessageBox::Ok, QMessageBox::Ok);
    mainchat->pntRefreshGL();
    return 0;
}

int dpkg_dismute_res(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    QMessageBox::information(NULL, "PChat", QString(root["mtwho"].asCString()) + "已经解除屏蔽！",
            QMessageBox::Ok, QMessageBox::Ok);
    mainchat->pntRefreshFL();
    return 0;
}

int dpkg_crgrp_res(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    QMessageBox::information(NULL, "PChat", QString("您已经成功的创建了群") + root["gn"].asCString() + "！",
            QMessageBox::Ok, QMessageBox::Ok);
    mainchat->pntRefreshGL();
    return 0;
}

int dpkg_exgrp_pcnot(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    QMessageBox::information(NULL, "PChat", QString("您已经成功的退出了群") + root["gn"].asCString() + "！",
            QMessageBox::Ok, QMessageBox::Ok);
    mainchat->pntRefreshGL();
    return 0;
}
