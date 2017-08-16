#include"include/uimainchat.h"
#include"ui_uimainchat.h"
#include<fpkg.h>
#include<QInputDialog>
#include<QMessageBox>
#include<service.h>
#include<json/json.h>
#include<condition_variable>
#include<QListWidget>
#include<QTabWidget>
#include<QPlainTextEdit>
#include<mutex>
#include<iostream>
#include<watchdog.h>
EXTERN_PKG_QM
EXTERN_LISTS
EXTERN_SRV_USRID
EXTERN_WATCHDOGS

using namespace std;
extern condition_variable pcv_sendchanged;
mutex ref_fl;
mutex ref_gl;
mutex ref_gm;

UIMainchat::UIMainchat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UIMainchat)
{
    ui->setupUi(this);

    QAction *qac_delfri = new QAction("删除该好友");
    QAction *qac_refreshfl = new QAction("刷新好友列表");
    QAction *qac_refreshgl = new QAction("刷新群列表");
    QAction *qac_refreshgm = new QAction("刷新成员列表");
    QAction *qac_exitgroup = new QAction("退出该群");
    QAction *qac_crone= new QAction("查看聊天记录");
    QAction *qac_crgroup = new QAction("查看聊天记录");
    QAction *qac_mute = new QAction("屏蔽此人");
    QAction *qac_dismute = new QAction("解除屏蔽");
    QAction *qac_dismiss = new QAction("解散此群");
//    QAction *qac_kick = new QAction("踢出此人");

    ui->lstFriend->addAction(qac_crone);
    ui->lstFriend->addAction(qac_refreshfl);
    ui->lstFriend->addAction(qac_delfri);
    ui->lstFriend->addAction(qac_mute);
    ui->lstFriend->addAction(qac_dismute);

    ui->lstGroup->addAction(qac_crgroup);
    ui->lstGroup->addAction(qac_refreshgl);
    ui->lstGroup->addAction(qac_exitgroup);
    ui->lstGroup->addAction(qac_dismiss);

    ui->lstGroupMember->addAction(qac_refreshgm);
    //ui->lstGroupMember->addAction(qac_kick);

    connect(qac_delfri, SIGNAL(triggered()), this, SLOT(srvDelFriend()));
    connect(qac_refreshfl, SIGNAL(triggered()), this, SLOT(pntRefreshFL()));
    connect(qac_mute, SIGNAL(triggered()), this, SLOT(srvMuteone()));
    connect(qac_dismute, SIGNAL(triggered()), this, SLOT(srvDismuteone()));
    connect(qac_dismiss, SIGNAL(triggered()), this, SLOT(srvDismissGroup()));
    connect(qac_exitgroup, SIGNAL(triggered()), this, SLOT(srvExitGroup()));
    connect(qac_refreshgm, SIGNAL(triggered()), this, SLOT(pntRefreshGM()));
    connect(qac_refreshgl, SIGNAL(triggered()), this, SLOT(pntRefreshGL()));
    connect(qac_crgroup, SIGNAL(triggered()), this, SLOT(srvRCGroup()));
    connect(qac_crone, SIGNAL(triggered()), this, SLOT(srvRCOne()));
    connect(ui->actAddFriend, SIGNAL(triggered()), this, SLOT(srvAddFriend()));
    connect(ui->actCreateGroup, SIGNAL(triggered()), this, SLOT(srvCreateGroup()));
    connect(ui->actJoinGroup, SIGNAL(triggered()), this, SLOT(srvJoinGroup()));
    connect(ui->actMsgbox, SIGNAL(triggered()), this, SLOT(srvFetch()));
    connect(ui->actQuit, SIGNAL(triggered()), this, SLOT(srvQuit()));
}

void UIMainchat::srvQuit() {
    WATCHDOG_DPKG = false;
    WATCHDOG_SPKG = false;
    WATCHDOG_RVPKG = false;
    WATCHDOG_UI = false;
    pcv_sendchanged.notify_all();
    pcv_sendchanged.notify_all();
    close();
    terminate();
    exit(0);
}

UIMainchat::~UIMainchat() {
    WATCHDOG_DPKG = false;
    WATCHDOG_SPKG = false;
    WATCHDOG_RVPKG = false;
    WATCHDOG_UI = false;
    delete ui;
}

void UIMainchat::onInit() {
    getNeed();
}

void UIMainchat::srvFetch() {
    QMessageBox::information(NULL, "PChat 查看离线消息", "稍等片刻，即将显示离线消息",
                             QMessageBox::Ok, QMessageBox::Ok);

    pkg_t recvpkg;
    Json::Value root;
    Json::FastWriter writer;
    root["un"] = g_LoginIdentity;

    recvpkg.head.wopr = PT_FCH_REQ;
    recvpkg.jsdata = writer.write(root);
    recvpkg.head.datasize = sizeof(pkg_head_t) + recvpkg.jsdata.length();

    pkglk_send.lock();
    qpkgSend.push(recvpkg);
    pcv_sendchanged.notify_all();
    pkglk_send.unlock();
}

void UIMainchat::puiSetStatus(QString status) {
    ui->lblStatus->setText(status);
}

void UIMainchat::srvRCOne() {
    QMessageBox::information(NULL, "PChat 查看聊天记录", "稍等片刻，即将显示聊天记录",
                             QMessageBox::Ok, QMessageBox::Ok);

    pkg_t recvpkg;
    Json::Value root;
    Json::FastWriter writer;
    root["un"] = g_LoginIdentity;
    int item = ui->lstFriend->currentRow();
    root["fun"] = friendList[item].first;
    root["gn"] = "";
    root["typ"] = 0;

    recvpkg.head.wopr = PT_FETCHCR_REQ;
    recvpkg.jsdata = writer.write(root);
    recvpkg.head.datasize = sizeof(pkg_head_t) + recvpkg.jsdata.length();

    pkglk_send.lock();
    qpkgSend.push(recvpkg);
    pcv_sendchanged.notify_all();
    pkglk_send.unlock();
}

void UIMainchat::srvRCGroup() {
    if (ui->lstGroup->currentRow() == -1)
        return;
    QMessageBox::information(NULL, "PChat 查看聊天记录", "稍等片刻，即将显示聊天记录",
                                     QMessageBox::Ok, QMessageBox::Ok);

    pkg_t recvpkg;
    Json::Value root;
    Json::FastWriter writer;
    root["un"] = g_LoginIdentity;
    int item = ui->lstGroup->currentRow();
    root["gn"] = groupList[item].first;
    root["fun"] = "";
    root["typ"] = 1;

    recvpkg.head.wopr = PT_FETCHCR_REQ;
    recvpkg.jsdata = writer.write(root);
    recvpkg.head.datasize = sizeof(pkg_head_t) + recvpkg.jsdata.length();

    pkglk_send.lock();
    qpkgSend.push(recvpkg);
    pcv_sendchanged.notify_all();
    pkglk_send.unlock();
}

void UIMainchat::srvJoinGroup() {
    bool ifok;
    QString store;
    store = QInputDialog::getText(NULL, "PChat 加入群", "您想要加入哪个群呢？", QLineEdit::Normal, "", &ifok);

    if (ifok) {
        pkg_t recvpkg;
        Json::Value root;
        Json::FastWriter writer;
        root["un"] = g_LoginIdentity;
        root["gn"] = store.toStdString();

        recvpkg.head.wopr = PT_ENGRP_REQ;
        recvpkg.jsdata = writer.write(root);
        recvpkg.head.datasize = sizeof(pkg_head_t) + recvpkg.jsdata.length();

        pkglk_send.lock();
        qpkgSend.push(recvpkg);
        pcv_sendchanged.notify_all();
        pkglk_send.unlock();
        QMessageBox::information(NULL, "PChat", "入群请求已发送！", QMessageBox::Ok, QMessageBox::Ok);
    }
}

void UIMainchat::srvAddFriend() {
    bool ifok;
    QString store;
    store = QInputDialog::getText(NULL, "PChat 添加好友", "您要添加谁为好友呢？", QLineEdit::Normal, "", &ifok);

    if (ifok) {
        pkg_t recvpkg;
        Json::Value root;
        Json::FastWriter writer;
        root["un"] = g_LoginIdentity;
        root["afwho"] = store.toStdString();

        recvpkg.head.wopr = PT_ADDFRI_REQ;
        recvpkg.jsdata = writer.write(root);
        recvpkg.head.datasize = sizeof(pkg_head_t) + recvpkg.jsdata.length();

        pkglk_send.lock();
        qpkgSend.push(recvpkg);
        pcv_sendchanged.notify_all();
        pkglk_send.unlock();
        QMessageBox::information(NULL, "PChat", "好友请求已发送！", QMessageBox::Ok, QMessageBox::Ok);
    }
}

void UIMainchat::srvExitGroup() {
    if (ui->lstGroup->currentRow() == -1)
        return;
    auto store = QMessageBox::information(NULL, "PChat 退出群", "确定要退出这个群吗？",
                                          QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (store == QMessageBox::Yes) {
        pkg_t recvpkg;
        Json::Value root;
        Json::FastWriter writer;
        root["un"] = g_LoginIdentity;
        int item = ui->lstGroup->currentRow();
        root["gn"] = groupList[item].first;;

        recvpkg.head.wopr = PT_EXGRP_REQ;
        recvpkg.jsdata = writer.write(root);
        recvpkg.head.datasize = sizeof(pkg_head_t) + recvpkg.jsdata.length();

        pkglk_send.lock();
        qpkgSend.push(recvpkg);
        pcv_sendchanged.notify_all();
        pkglk_send.unlock();
    }
}

void UIMainchat::srvDismissGroup() {
    if (ui->lstGroup->currentRow() == -1)
        return;
    auto store = QMessageBox::information(NULL, "PChat 解散群", "确定要解散这个群吗？",
                                          QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (store == QMessageBox::Yes) {
        pkg_t recvpkg;
        Json::Value root;
        Json::FastWriter writer;
        root["un"] = g_LoginIdentity;
        int item = ui->lstGroup->currentRow();
        root["gn"] = groupList[item].first;;

        recvpkg.head.wopr = PT_DISGRP_REQ;
        recvpkg.jsdata = writer.write(root);
        recvpkg.head.datasize = sizeof(pkg_head_t) + recvpkg.jsdata.length();

        pkglk_send.lock();
        qpkgSend.push(recvpkg);
        pcv_sendchanged.notify_all();
        pkglk_send.unlock();
    }
}

void UIMainchat::puiSetText(QString text) {
    ui->txtMsg->setText(text);
}

void UIMainchat::srvDelFriend() {
    if (ui->lstFriend->currentRow() == -1)
        return;
    auto store = QMessageBox::information(NULL, "PChat 删除好友", "确定要删除他吗？",
                                          QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (store == QMessageBox::Yes) {
        pkg_t recvpkg;
        Json::Value root;
        Json::FastWriter writer;
        root["un"] = g_LoginIdentity;
        int item = ui->lstFriend->currentRow();
        root["dfwho"] = friendList[item].first;;

        recvpkg.head.wopr = PT_DELFRI_REQ;
        recvpkg.jsdata = writer.write(root);
        recvpkg.head.datasize = sizeof(pkg_head_t) + recvpkg.jsdata.length();

        pkglk_send.lock();
        qpkgSend.push(recvpkg);
        pcv_sendchanged.notify_all();
        pkglk_send.unlock();
    }
}

void UIMainchat::srvMuteone() {
    if (ui->lstFriend->currentRow() == -1)
        return;
    auto store = QMessageBox::information(NULL, "PChat 屏蔽好友", "确定要屏蔽他吗？",
                                          QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (store == QMessageBox::Yes) {
        pkg_t recvpkg;
        Json::Value root;
        Json::FastWriter writer;
        root["un"] = g_LoginIdentity;
        int item = ui->lstFriend->currentRow();
        root["mtwho"] = friendList[item].first;;

        recvpkg.head.wopr = PT_MUTE_REQ;
        recvpkg.jsdata = writer.write(root);
        recvpkg.head.datasize = sizeof(pkg_head_t) + recvpkg.jsdata.length();

        pkglk_send.lock();
        qpkgSend.push(recvpkg);
        pcv_sendchanged.notify_all();
        pkglk_send.unlock();
    }
}

void UIMainchat::srvDismuteone() {
    if (ui->lstFriend->currentRow() == -1)
        return;
    auto store = QMessageBox::information(NULL, "PChat 解除屏蔽好友", "确定要解除屏蔽他吗？",
                                          QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (store == QMessageBox::Yes) {
        pkg_t recvpkg;
        Json::Value root;
        Json::FastWriter writer;
        root["un"] = g_LoginIdentity;
        int item = ui->lstFriend->currentRow();
        root["mtwho"] = friendList[item].first;

        recvpkg.head.wopr = PT_DISMUTE_REQ;
        recvpkg.jsdata = writer.write(root);
        recvpkg.head.datasize = sizeof(pkg_head_t) + recvpkg.jsdata.length();

        pkglk_send.lock();
        qpkgSend.push(recvpkg);
        pcv_sendchanged.notify_all();
        pkglk_send.unlock();
    }
}


void UIMainchat::srvCreateGroup() {
    bool ifok;
    QString store;
    store = QInputDialog::getText(NULL, "PChat 创建群", "请输入想要创建的群名：", QLineEdit::Normal, "", &ifok);

    if (ifok) {
        pkg_t recvpkg;
        Json::Value root;
        Json::FastWriter writer;
        root["un"] = g_LoginIdentity;
        root["gn"] = store.toStdString();

        recvpkg.head.wopr = PT_CRGRP_REQ;
        recvpkg.jsdata = writer.write(root);
        recvpkg.head.datasize = sizeof(pkg_head_t) + recvpkg.jsdata.length();

        pkglk_send.lock();
        qpkgSend.push(recvpkg);
        pcv_sendchanged.notify_all();
        pkglk_send.unlock();
        QMessageBox::information(NULL, "PChat", "建立请求已经发送！", QMessageBox::Ok, QMessageBox::Ok);
    }
}

void UIMainchat::getNeed() {
    pntRefreshFL();
    pntRefreshGL();
    pntRefreshGM();
}

void UIMainchat::pntRefreshFL() {
    ref_fl.lock();
    pkg_t thispkg;
    thispkg.head.wopr = PT_REFRESH_FL;
    thispkg.jsdata = "{\"un\":\"" + g_LoginIdentity + "\"}";
    thispkg.head.datasize = sizeof(pkg_head_t) + thispkg.jsdata.length();

    pkglk_send.lock();
    qpkgSend.push(thispkg);
    pcv_sendchanged.notify_all();
    pkglk_send.unlock();
    ref_fl.unlock();
}

void UIMainchat::pntRefreshGL() {
    ref_gl.lock();
    pkg_t thispkg;
    thispkg.head.wopr = PT_REFRESH_GL;
    thispkg.jsdata = "{\"un\":\"" + g_LoginIdentity + "\"}";
    thispkg.head.datasize = sizeof(pkg_head_t) + thispkg.jsdata.length();

    pkglk_send.lock();
    qpkgSend.push(thispkg);
    pcv_sendchanged.notify_all();
    pkglk_send.unlock();
    ref_gl.unlock();
}

void UIMainchat::pntRefreshGM() {
    ref_gm.lock();
    pkg_t thispkg;
    thispkg.head.wopr = PT_REFRESH_GM;
    if (ui->lstGroup->currentRow() == -1) {
        ref_gm.unlock();
        return;
    }
    QString gn = ui->lstGroup->currentItem()->text();
    thispkg.jsdata = "{\"un\":\"" + g_LoginIdentity + "\",\"gn\":\"" +
            gn.toStdString() + "\"}";

    cerr << thispkg.jsdata << endl;
    thispkg.head.datasize = sizeof(pkg_head_t) + thispkg.jsdata.length();

    pkglk_send.lock();
    qpkgSend.push(thispkg);
    pcv_sendchanged.notify_all();
    pkglk_send.unlock();
    ref_gm.unlock();
}

void UIMainchat::puiRefreshFL() {
    auto lst = ui->lstFriend;
    lst->clear();
    for (auto i : friendList) {
        QString what = i.second.first.c_str();
        if (i.second.second == 0)
            what += " [在线]";
        else if (i.second.second == 1)
            what += " [离线]";
        else if (i.second.second == 2)
            what += " [已屏蔽]";
        lst->addItem(what);
    }
}

void UIMainchat::puiRefreshGL() {
    auto lst = ui->lstGroup;
    lst->clear();
    for (auto i : groupList) {
        lst->addItem(QString(i.second.first.c_str()));
    }
}

void UIMainchat::puiRefreshGM() {
    auto lst = ui->lstGroupMember,
            ls = ui->lstGroup;
    lst->clear();
    if (ls->currentRow() == -1)
        return;
    QString gn = ls->currentItem()->text();

    for (auto i: groupmemberList[gn.toStdString()]) {
        lst->addItem(QString(i.second.c_str()));
    }
}

void UIMainchat::on_btnSend_clicked()
{
    Json::Value root;
    Json::FastWriter writer;
    pkg_t thispkg;
    if (ui->tabWidget->currentIndex() == 0) {
        thispkg.head.wopr = PT_MSG_FRI;
        int item = ui->lstFriend->currentRow();
        root["sd"] = g_LoginIdentity;
        root["rv"] = friendList[item].first;
        root["msg"] = ui->txtSend->toPlainText().toStdString();
        thispkg.jsdata = writer.write(root);
        thispkg.head.datasize = sizeof(pkg_head_t) + thispkg.jsdata.length();
    } else {
        thispkg.head.wopr = PT_MSG_GRP;
        int item = ui->lstGroup->currentRow();
        root["sd"] = g_LoginIdentity;
        root["gn"] = groupList[item].first;
        root["msg"] = ui->txtSend->toPlainText().toStdString();
        thispkg.jsdata = writer.write(root);
        thispkg.head.datasize = sizeof(pkg_head_t) + thispkg.jsdata.length();
    }
    pkglk_send.lock();
    qpkgSend.push(thispkg);
    pcv_sendchanged.notify_all();
    pkglk_send.unlock();
}



void UIMainchat::on_lstFriend_currentRowChanged(int currentRow)
{
    string now = friendList[currentRow].first;
    ui->txtMsg->setText(QString(mUnString[now].c_str()));
}

void UIMainchat::RefreshMsg()
{
    if (ui->tabWidget->currentIndex() == 0) {
        int ori = ui->lstFriend->currentRow();
        ui->lstFriend->setCurrentRow(-1);
        ui->lstFriend->setCurrentRow(ori);
    } else {
        int ori = ui->lstGroup->currentRow();
        ui->lstGroup->setCurrentRow(-1);
        ui->lstGroup->setCurrentRow(ori);
    }
}

void UIMainchat::on_lstGroup_currentRowChanged(int currentRow)
{
    string now = groupList[currentRow].first;
    ui->txtMsg->setText(QString(mGnString[now].c_str()));
}
