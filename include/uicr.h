#ifndef UICR_H
#define UICR_H

#include <QWidget>

namespace Ui {
class uiCR;
}

class uiCR : public QWidget
{
    Q_OBJECT

public:
    explicit uiCR(QString text, QWidget *parent = 0);
    ~uiCR();
private:
    Ui::uiCR *ui;
};

#endif // UICR_H
