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
    void puiRefreshFL();
    void puiRefreshGL();
    void puiRefreshGM();
    void RefreshMsg();
    void onInit();
    void puiSetText(QString text);
public slots:
    void srvAddFriend();
    void srvCreateGroup();
    void srvDelFriend();
    void srvJoinGroup();
    void srvMuteone();
    void srvDismuteone();
    void pntRefreshFL();
    void pntRefreshGL();
    void pntRefreshGM();
    void srvExitGroup();
    void srvDismissGroup();
    void srvRCOne();
    void srvRCGroup();
    void srvFetch();
    void srvQuit();
private slots:
    void on_btnSend_clicked();

    void on_lstFriend_currentRowChanged(int currentRow);

    void on_lstGroup_currentRowChanged(int currentRow);

private:
    Ui::UIMainchat *ui;
    void getNeed();

};

#endif // UIMAINCHAT_H
