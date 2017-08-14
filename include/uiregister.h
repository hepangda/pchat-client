#ifndef UIREGISTER_H
#define UIREGISTER_H

#include <QWidget>

namespace Ui {
class UIRegister;
}

class UIRegister : public QWidget
{
    Q_OBJECT

public:
    explicit UIRegister(QWidget *parent = 0);
    ~UIRegister();

private slots:
    void on_txtChkpasswd_editingFinished();
    void on_btnRegister_clicked();

    void on_btnCancel_clicked();

private:
    Ui::UIRegister *ui;
    std::string JsonlizeUI();
    int checkUI();
};

#endif // UIREGISTER_H
