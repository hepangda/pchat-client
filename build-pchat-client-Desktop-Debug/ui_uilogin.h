/********************************************************************************
** Form generated from reading UI file 'uilogin.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UILOGIN_H
#define UI_UILOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UILogin
{
public:
    QLineEdit *txtUsername;
    QLineEdit *txtPasswd;
    QPushButton *btnLogin;
    QLabel *lbl_username;
    QLabel *lbl_passwd;
    QPushButton *btnRegister;
    QPushButton *btnForget;

    void setupUi(QWidget *UILogin)
    {
        if (UILogin->objectName().isEmpty())
            UILogin->setObjectName(QStringLiteral("UILogin"));
        UILogin->setWindowModality(Qt::WindowModal);
        UILogin->resize(382, 216);
        UILogin->setMinimumSize(QSize(382, 216));
        UILogin->setMaximumSize(QSize(382, 216));
        txtUsername = new QLineEdit(UILogin);
        txtUsername->setObjectName(QStringLiteral("txtUsername"));
        txtUsername->setGeometry(QRect(140, 50, 191, 32));
        txtPasswd = new QLineEdit(UILogin);
        txtPasswd->setObjectName(QStringLiteral("txtPasswd"));
        txtPasswd->setGeometry(QRect(140, 100, 191, 31));
        txtPasswd->setEchoMode(QLineEdit::Password);
        txtPasswd->setClearButtonEnabled(false);
        btnLogin = new QPushButton(UILogin);
        btnLogin->setObjectName(QStringLiteral("btnLogin"));
        btnLogin->setGeometry(QRect(20, 170, 103, 33));
        btnLogin->setAcceptDrops(false);
        lbl_username = new QLabel(UILogin);
        lbl_username->setObjectName(QStringLiteral("lbl_username"));
        lbl_username->setGeometry(QRect(60, 50, 61, 24));
        lbl_passwd = new QLabel(UILogin);
        lbl_passwd->setObjectName(QStringLiteral("lbl_passwd"));
        lbl_passwd->setGeometry(QRect(80, 100, 77, 24));
        btnRegister = new QPushButton(UILogin);
        btnRegister->setObjectName(QStringLiteral("btnRegister"));
        btnRegister->setGeometry(QRect(140, 170, 103, 33));
        btnForget = new QPushButton(UILogin);
        btnForget->setObjectName(QStringLiteral("btnForget"));
        btnForget->setGeometry(QRect(260, 170, 103, 33));

        retranslateUi(UILogin);

        btnLogin->setDefault(true);


        QMetaObject::connectSlotsByName(UILogin);
    } // setupUi

    void retranslateUi(QWidget *UILogin)
    {
        UILogin->setWindowTitle(QApplication::translate("UILogin", "PChat \347\231\273\345\275\225", Q_NULLPTR));
        txtPasswd->setInputMask(QString());
        btnLogin->setText(QApplication::translate("UILogin", "\347\231\273\345\275\225", Q_NULLPTR));
        lbl_username->setText(QApplication::translate("UILogin", "<html><head/><body><p><span style=\" font-weight:600;\">\347\224\250\346\210\267\345\220\215\357\274\232</span></p></body></html>", Q_NULLPTR));
        lbl_passwd->setText(QApplication::translate("UILogin", "<html><head/><body><p><span style=\" font-weight:600;\">\345\257\206\347\240\201\357\274\232</span></p></body></html>", Q_NULLPTR));
        btnRegister->setText(QApplication::translate("UILogin", "\346\263\250\345\206\214", Q_NULLPTR));
        btnForget->setText(QApplication::translate("UILogin", "\345\277\230\350\256\260\345\257\206\347\240\201\357\274\237", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UILogin: public Ui_UILogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UILOGIN_H
