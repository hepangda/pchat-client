#ifndef UIMAINCHAT_H
#define UIMAINCHAT_H

#include <QMainWindow>

namespace Ui {
class UIMainchat;
}

class UIMainchat : public QMainWindow
{
    Q_OBJECT

public:
    explicit UIMainchat(QWidget *parent = 0);
    ~UIMainchat();
    Ui::UIMainchat *getUI() { return ui; }
    void puiSetStatus(QString status);

public slots:
    void srvAddFriend();
private:
    Ui::UIMainchat *ui;


};

#endif // UIMAINCHAT_H
