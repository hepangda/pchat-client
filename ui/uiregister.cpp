#include<uiregister.h>
#include<ui_uiregister.h>
#include<string>
#include<json/json.h>
#include<QMessageBox>
#include<package.h>
#include<portal/crypt.h>
#include<portal/network.h>
using namespace std;
using namespace libportal;
extern TCPSocket ipconn;
static QString failedString[] = { "用户名应当在5到15位之间", "密码应当在8到30位之间",
                                  "两次输入的密码不一致", "密码提示答案不能为空" };

UIRegister::UIRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UIRegister)
{
    ui->setupUi(this);
    ui->btnRegister->setShortcut(QKeySequence::InsertParagraphSeparator);
    ui->btnRegister->setShortcut(Qt::Key_Enter);
    ui->btnRegister->setShortcut(Qt::Key_Return);

}

UIRegister::~UIRegister()
{
    delete ui;
}

string UIRegister::JsonlizeUI()
{
    string ret;
    Json::Value root;
    Json::FastWriter writer;
    root["un"] = (const char *)ui->txtUsername->text().toLocal8Bit();

    string pwd = (const char *)ui->txtPasswd->text().toLocal8Bit();
    root["pwd"] = CryptMD5::encrypt(pwd);
    root["qst"] = ui->cbxQst->currentIndex();
    string ans = (const char *)ui->txtAns->text().toLocal8Bit();
    root["ans"] = CryptMD5::encrypt(ans);
    ret = writer.write(root);
    ret[ret.length() - 1] = '\0';
    return ret;
}

int UIRegister::checkUI()
{
    QString str_un = ui->txtUsername->text(),
            str_pwd = ui->txtPasswd->text(),
            str_chkpwd = ui->txtChkpasswd->text(),
            str_ans = ui->txtAns->text();
    if (str_un.size() < 5 || str_un.size() >= 15)
        return 1;
    if (str_pwd.size() < 8 || str_pwd.size() >= 30)
        return 2;
    if (str_chkpwd != str_pwd)
        return 3;
    if (str_ans.size() == 0)
        return 4;
    return 0;
}

void UIRegister::on_txtChkpasswd_editingFinished()
{
    QString pwd1 = ui->txtPasswd->text(),
            pwd2 = ui->txtChkpasswd->text();

    if (pwd1 != pwd2) {
        ui->txtChkpasswd->setText("");
        ui->txtChkpasswd->setPlaceholderText("两次输入的密码不一致");
    }
}

void UIRegister::on_btnRegister_clicked()
{
    int ret;
    if ((ret = checkUI()) != 0) {
        QMessageBox::warning(NULL, "注册失败", "输入的信息不合法:\n*" + failedString[ret - 1],
                QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    pkg_t thispkg;
    thispkg.jsdata = JsonlizeUI();
    thispkg.head.wopr = PT_REG_REQ;
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
        QMessageBox::information(NULL, "PChat", "注册成功！", QMessageBox::Ok, QMessageBox::Ok);
        close();
    } else {
        QMessageBox::critical(NULL, "PChat", "注册失败，原因可能是：\n1.用户名与已存在的用户重复\n2.服务器关闭了注册",
                              QMessageBox::Ok, QMessageBox::Ok);
    }
}

void UIRegister::on_btnCancel_clicked()
{
    close();
}
