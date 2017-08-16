#include "include/uicr.h"
#include "ui_uicr.h"

uiCR::uiCR(QString text, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::uiCR)
{
    ui->setupUi(this);
    ui->txt->setText(text);
}

uiCR::~uiCR()
{
    delete ui;
}
