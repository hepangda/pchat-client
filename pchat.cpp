#include<portal/network.h>
#include<uilogin.h>
#include<QApplication>
#include<QMessageBox>
#include<string>
using namespace libportal;

const std::string PCHAT_SERVER = "127.0.0.1";
const unsigned int PCHAT_PORT = 14001;

TCPSocket ipconn(PCHAT_SERVER, PCHAT_PORT);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (ipconn.Connect() < 0) {
        QMessageBox::critical(NULL, "PChat", "无法连接到PChat服务器。\n请检查您的网络并尝试重新连接。",
                              QMessageBox::Ok, QMessageBox::Ok);
        return a.exec();
    }
    UILogin *login = new UILogin;
    login->show();

    return a.exec();
}
