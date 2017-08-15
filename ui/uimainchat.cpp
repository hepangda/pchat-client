#include "include/uimainchat.h"
#include "ui_uimainchat.h"
#include<fpkg.h>
#include<QInputDialog>
#include<QMessageBox>
#include<service.h>
#include<json/json.h>
#include<condition_variable>
EXTERN_PKG_QM
EXTERN_LISTS
EXTERN_SRV_USRID


using namespace std;
extern condition_variable pcv_sendchanged;


UIMainchat::UIMainchat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UIMainchat)
{
    ui->setupUi(this);

    QAction *qac_delfri = new QAction("删除该好友");
    QAction *qac_refreshfl = new QAction("刷新好友列表");
    QAction *qac_refreshgl = new QAction("刷新群列表");
    QAction *qac_refreshgm = new QAction("刷新成员列表");


    ui->lstFriend->addAction(qac_delfri);
    ui->lstFriend->addAction(qac_refreshfl);

    connect(qac_delfri, SIGNAL(triggered()), this, SLOT(open()));

    connect(ui->actAddFriend, SIGNAL(triggered()), this, SLOT(srvAddFriend()));
}

UIMainchat::~UIMainchat()
{
    delete ui;
}

void UIMainchat::puiSetStatus(QString status) {
    ui->lblStatus->setText(status);
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
