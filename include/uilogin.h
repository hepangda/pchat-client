#ifndef UILOGIN_H
#define UILOGIN_H

#include <QWidget>

namespace Ui {
class UILogin;
}

class UILogin : public QWidget
{
    Q_OBJECT

public:
    explicit UILogin(QWidget *parent = 0);
    ~UILogin();

private slots:
    void on_btnRegister_clicked();

    void on_btnLogin_clicked();

    void on_btnForget_clicked();

    void on_btnExit_clicked();

private:
    Ui::UILogin *ui;
    std::string JsonlizeUI();
};

#endif // UILOGIN_H
