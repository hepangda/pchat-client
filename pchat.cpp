#include<portal/network.h>
#include<uilogin.h>
#include<uimainchat.h>
#include<QApplication>
#include<QMessageBox>
#include<string>
#include<fpkg.h>

using namespace std;
using namespace libportal;

const std::string PCHAT_SERVER = "192.168.30.121";
const unsigned int PCHAT_PORT = 6542;

UIMainchat *mainchat;
TCPSocket ipconn(PCHAT_SERVER, PCHAT_PORT);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mainchat = new UIMainchat;
    if (ipconn.Connect() < 0) {
        QMessageBox::critical(NULL, "PChat", "无法连接到PChat服务器。\n请检查您的网络并尝试重新连接。",
                              QMessageBox::Ok, QMessageBox::Ok);
        exit(0);
        return a.exec();
    }

    UILogin *login = new UILogin;
    login->show();
    network_module();

    return a.exec();
}
