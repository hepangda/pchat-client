#include "include/uimainchat.h"
#include "ui_uimainchat.h"

UIMainchat::UIMainchat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UIMainchat)
{
    ui->setupUi(this);
}

UIMainchat::~UIMainchat()
{
    delete ui;
}
