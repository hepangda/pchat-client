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
using namespace std;

EXTERN_PKG_QM
EXTERN_WATCHDOGS
extern UIMainchat *mainchat;

static map<uint16_t, function<int(pkg_t)> > mPkgfunc;
extern condition_variable pcv_sendchanged;

mutex pmtx_recvchanged;
condition_variable pcv_recvchanged;

map<string, string> mUnString; //un->chatmsg;
map<string, string> mGnString; //gn->chatmsg;
map<int, string> friendList;
map<int, string> groupList;
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

    thread dpkg_thread(dpkg_distribute);
    dpkg_thread.join();
}

void dpkg_distribute() {
    while (WATCHDOG_DPKG) {
        unique_lock<mutex> pul_recvchanged(pmtx_recvchanged);
        pcv_recvchanged.wait(pul_recvchanged);
        pkglk_recv.lock();
        if (qpkgRecv.empty()) {
            pkglk_recv.unlock();
            continue;
        }
        pkg_t thispkg = qpkgRecv.front();
        qpkgRecv.pop();
        pkglk_recv.unlock();
        mPkgfunc[thispkg.head.wopr](thispkg);
    }
}

int dpkg_grouplist(pkg_t pkg) {
    return 0;
}

int dpkg_gmlist(pkg_t pkg) {
    return 0;
}

int dpkg_friendlist(pkg_t pkg) {
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
    return 0;
}

int dpkg_msg_fri(pkg_t pkg) {
    return 0;
}

int dpkg_pkey_req(pkg_t pkg) {
    return 0;
}

int dpkg_pkey_res(pkg_t pkg) {
    return 0;
}

int dpkg_fetchcr_res(pkg_t pkg) {
    return 0;
}

int dpkg_delfriend(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    QMessageBox::information(NULL, "PChat", QString(root["un"].asCString()) + "已经成功删除了" +
            root["dfwho"].asCString() + "！", QMessageBox::Ok, QMessageBox::Ok);
    return 0;
}

int dpkg_addfriend_res(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    QMessageBox::information(NULL, "PChat", QString(root["un"].asCString()) + "已经同意添加了" +
            root["afwho"].asCString() + "！", QMessageBox::Ok, QMessageBox::Ok);
    return 0;
}

int dpkg_mute_res(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    QMessageBox::information(NULL, "PChat", QString("您已经成功的屏蔽了用户") + root["mtwho"].asCString() + "！",
            QMessageBox::Ok, QMessageBox::Ok);
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
    QMessageBox::information(NULL, "PChat", QString("您已经加入了群") + root["gn"].asCString() + "！",
            QMessageBox::Ok, QMessageBox::Ok);
    return 0;
}

//TODO: 刷新群列表！！！
int dpkg_disgrp_not(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    QMessageBox::information(NULL, "PChat", QString("你加入的群") + root["gn"].asCString() + "已经被群主解散！",
            QMessageBox::Ok, QMessageBox::Ok);
    return 0;
}

int dpkg_dismute_res(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    QMessageBox::information(NULL, "PChat", QString(root["mtwho"].asCString()) + "已经解除屏蔽！",
            QMessageBox::Ok, QMessageBox::Ok);
    return 0;
}

int dpkg_crgrp_res(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    QMessageBox::information(NULL, "PChat", QString("您已经成功的创建了群") + root["gn"].asCString() + "！",
            QMessageBox::Ok, QMessageBox::Ok);
    return 0;
}

int dpkg_exgrp_pcnot(pkg_t pkg) {
    Json::Value root;
    Json::Reader reader;

    reader.parse(pkg.jsdata, root);
    QMessageBox::information(NULL, "PChat", QString("您已经成功的退出了群") + root["gn"].asCString() + "！",
            QMessageBox::Ok, QMessageBox::Ok);

    return 0;
}
