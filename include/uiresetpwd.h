#ifndef UIRESETPWD_H
#define UIRESETPWD_H

#include <QWidget>

namespace Ui {
class UIResetpwd;
}

class UIResetpwd : public QWidget
{
    Q_OBJECT

public:
    explicit UIResetpwd(QWidget *parent = 0);
    ~UIResetpwd();

private slots:
    void on_txtChkpasswd_editingFinished();

    void on_btnRegister_clicked();

    void on_btnCancel_clicked();

private:
    Ui::UIResetpwd *ui;
    std::string JsonlizeUI();
    int checkUI();
};

#endif // UIRESETPWD_H
