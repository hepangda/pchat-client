#include<include/uilogin.h>
#include<include/uiregister.h>
#include<include/uiresetpwd.h>
#include<ui_uilogin.h>
#include<QMessageBox>
#include<json/json.h>
#include<string>
#include<portal/crypt.h>
#include<portal/network.h>
#include<package.h>
#include<iostream>
#include<service.h>
#include<include/uimainchat.h>
#include<condition_variable>
using namespace libportal;
using namespace std;

EXTERN_SRV_USRID
extern TCPSocket ipconn;
extern UIMainchat *mainchat;
extern condition_variable pcv_cansolve;

UILogin::UILogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UILogin)
{
    ui->setupUi(this);
    ui->btnLogin->setShortcut(QKeySequence::InsertParagraphSeparator);
    ui->btnLogin->setShortcut(Qt::Key_Enter);
    ui->btnLogin->setShortcut(Qt::Key_Return);
}

UILogin::~UILogin()
{
    delete ui;
}

string UILogin::JsonlizeUI()
{
    string ret;
    Json::Value root;
    Json::FastWriter writer;
    root["un"] = (const char *)ui->txtUsername->text().toLocal8Bit();

    string pwd = (const char *)ui->txtPasswd->text().toLocal8Bit();
    root["pwd"] = CryptMD5::encrypt(pwd);
    ret = writer.write(root);
    ret[ret.length() - 1] = '\0';
    return ret;
}

void UILogin::on_btnRegister_clicked()
{
    UIRegister *reg = new UIRegister;
    reg->show();
}

void UILogin::on_btnLogin_clicked()
{
    pkg_t thispkg;
    thispkg.jsdata = JsonlizeUI();
    cout << thispkg.jsdata << endl;
    thispkg.head.wopr = 100;
    thispkg.head.datasize = sizeof(pkg_head_t) + thispkg.jsdata.length();
    ipconn.Write((char *)&thispkg.head, sizeof(pkg_head_t));
    ipconn.Write(thispkg.jsdata);

    pkg_t recvpkg;
    ipconn.Read((char *)&recvpkg.head, sizeof(pkg_head_t));
    ipconn.Read(recvpkg.jsdata, recvpkg.head.datasize - sizeof(pkg_head_t));

    Json::Value rev;
    Json::Reader reader;
    reader.parse(recvpkg.jsdata, rev);
    if (rev["res"].asInt() == 0) {
        QMessageBox::information(NULL, "PChat", "登录成功！", QMessageBox::Ok, QMessageBox::Ok);
        g_LoginIdentity = rev["un"].asString();
        pcv_cansolve.notify_all();
        mainchat->show();
        close();
    } else {
        QMessageBox::information(NULL, "result", "登录失败！", QMessageBox::Ok, QMessageBox::Ok);
    }
}

void UILogin::on_btnForget_clicked()
{
    UIResetpwd *rst = new UIResetpwd;
    rst->show();
}

void UILogin::on_btnExit_clicked()
{
    exit(0);
}
