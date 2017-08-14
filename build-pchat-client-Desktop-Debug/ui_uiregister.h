/********************************************************************************
** Form generated from reading UI file 'uiregister.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIREGISTER_H
#define UI_UIREGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UIRegister
{
public:
    QLineEdit *txtUsername;
    QLineEdit *txtPasswd;
    QLineEdit *txtChkpasswd;
    QLineEdit *txtAns;
    QComboBox *cbxQst;
    QLabel *lbl_username;
    QLabel *lbl_passwd;
    QLabel *lbl_chkpwd;
    QLabel *lbl_qst;
    QLabel *lbl_ans;
    QPushButton *btnRegister;
    QPushButton *btnCancel;

    void setupUi(QWidget *UIRegister)
    {
        if (UIRegister->objectName().isEmpty())
            UIRegister->setObjectName(QStringLiteral("UIRegister"));
        UIRegister->resize(454, 352);
        txtUsername = new QLineEdit(UIRegister);
        txtUsername->setObjectName(QStringLiteral("txtUsername"));
        txtUsername->setGeometry(QRect(160, 40, 231, 32));
        txtPasswd = new QLineEdit(UIRegister);
        txtPasswd->setObjectName(QStringLiteral("txtPasswd"));
        txtPasswd->setGeometry(QRect(160, 90, 231, 32));
        txtPasswd->setEchoMode(QLineEdit::Password);
        txtChkpasswd = new QLineEdit(UIRegister);
        txtChkpasswd->setObjectName(QStringLiteral("txtChkpasswd"));
        txtChkpasswd->setGeometry(QRect(160, 140, 231, 32));
        txtChkpasswd->setEchoMode(QLineEdit::Password);
        txtChkpasswd->setDragEnabled(false);
        txtAns = new QLineEdit(UIRegister);
        txtAns->setObjectName(QStringLiteral("txtAns"));
        txtAns->setGeometry(QRect(190, 240, 201, 32));
        cbxQst = new QComboBox(UIRegister);
        cbxQst->setObjectName(QStringLiteral("cbxQst"));
        cbxQst->setGeometry(QRect(190, 190, 201, 32));
        lbl_username = new QLabel(UIRegister);
        lbl_username->setObjectName(QStringLiteral("lbl_username"));
        lbl_username->setGeometry(QRect(90, 40, 71, 24));
        lbl_passwd = new QLabel(UIRegister);
        lbl_passwd->setObjectName(QStringLiteral("lbl_passwd"));
        lbl_passwd->setGeometry(QRect(100, 90, 51, 24));
        lbl_chkpwd = new QLabel(UIRegister);
        lbl_chkpwd->setObjectName(QStringLiteral("lbl_chkpwd"));
        lbl_chkpwd->setGeometry(QRect(70, 140, 81, 24));
        lbl_qst = new QLabel(UIRegister);
        lbl_qst->setObjectName(QStringLiteral("lbl_qst"));
        lbl_qst->setGeometry(QRect(60, 190, 121, 24));
        lbl_ans = new QLabel(UIRegister);
        lbl_ans->setObjectName(QStringLiteral("lbl_ans"));
        lbl_ans->setGeometry(QRect(60, 240, 161, 24));
        btnRegister = new QPushButton(UIRegister);
        btnRegister->setObjectName(QStringLiteral("btnRegister"));
        btnRegister->setEnabled(true);
        btnRegister->setGeometry(QRect(50, 290, 211, 33));
        btnCancel = new QPushButton(UIRegister);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(290, 290, 103, 33));

        retranslateUi(UIRegister);

        btnRegister->setDefault(true);


        QMetaObject::connectSlotsByName(UIRegister);
    } // setupUi

    void retranslateUi(QWidget *UIRegister)
    {
        UIRegister->setWindowTitle(QApplication::translate("UIRegister", "PChat \346\263\250\345\206\214", Q_NULLPTR));
        txtPasswd->setPlaceholderText(QApplication::translate("UIRegister", "\345\257\206\347\240\201\345\272\224\344\270\215\345\260\221\344\272\2168\344\275\215", Q_NULLPTR));
        txtChkpasswd->setPlaceholderText(QApplication::translate("UIRegister", "\350\257\267\351\207\215\345\244\215\345\257\206\347\240\201", Q_NULLPTR));
        cbxQst->clear();
        cbxQst->insertItems(0, QStringList()
         << QApplication::translate("UIRegister", "\344\275\240\347\210\266\344\272\262\347\232\204\350\201\214\344\270\232\357\274\237", Q_NULLPTR)
         << QApplication::translate("UIRegister", "\344\275\240\347\210\266\344\272\262\347\232\204\345\247\223\345\220\215\357\274\237", Q_NULLPTR)
         << QApplication::translate("UIRegister", "\344\275\240\347\232\204\345\255\246\345\217\267(\345\267\245\345\217\267)\357\274\237", Q_NULLPTR)
         << QApplication::translate("UIRegister", "\344\275\240\346\257\215\344\272\262\347\232\204\347\224\237\346\227\245\357\274\237", Q_NULLPTR)
         << QApplication::translate("UIRegister", "\345\260\217\345\255\246\347\217\255\344\270\273\344\273\273\345\220\215\345\255\227\357\274\237", Q_NULLPTR)
         << QApplication::translate("UIRegister", "\344\275\240\351\205\215\345\201\266\347\232\204\345\247\223\345\220\215\357\274\237", Q_NULLPTR)
         << QApplication::translate("UIRegister", "\344\275\240\351\205\215\345\201\266\347\232\204\350\201\214\344\270\232\357\274\237", Q_NULLPTR)
         << QApplication::translate("UIRegister", "\345\210\235\344\270\255\347\217\255\344\270\273\344\273\273\345\220\215\345\255\227\357\274\237", Q_NULLPTR)
         << QApplication::translate("UIRegister", "\344\275\240\347\232\204\345\207\272\347\224\237\345\234\260\357\274\237", Q_NULLPTR)
         << QApplication::translate("UIRegister", "\344\275\240\346\257\215\344\272\262\347\232\204\350\201\214\344\270\232\357\274\237", Q_NULLPTR)
         << QApplication::translate("UIRegister", "\344\275\240\346\257\215\344\272\262\347\232\204\345\247\223\345\220\215\357\274\237", Q_NULLPTR)
         << QApplication::translate("UIRegister", "\344\275\240\347\210\266\344\272\262\347\232\204\347\224\237\346\227\245\357\274\237", Q_NULLPTR)
         << QApplication::translate("UIRegister", "\344\275\240\351\205\215\345\201\266\347\232\204\347\224\237\346\227\245\357\274\237", Q_NULLPTR)
         << QApplication::translate("UIRegister", "\351\253\230\344\270\255\347\217\255\344\270\273\344\273\273\345\220\215\345\255\227\357\274\237", Q_NULLPTR)
        );
        lbl_username->setText(QApplication::translate("UIRegister", "<html><head/><body><p><span style=\" font-weight:600;\">\347\224\250\346\210\267\345\220\215\357\274\232</span></p></body></html>", Q_NULLPTR));
        lbl_passwd->setText(QApplication::translate("UIRegister", "<b>\345\257\206\347\240\201\357\274\232</b>", Q_NULLPTR));
        lbl_chkpwd->setText(QApplication::translate("UIRegister", "<b>\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232</b>", Q_NULLPTR));
        lbl_qst->setText(QApplication::translate("UIRegister", "<html><head/><body><p><span style=\" font-weight:600;\">\346\211\276\345\233\236\345\257\206\347\240\201\351\227\256\351\242\230\357\274\232</span></p></body></html>", Q_NULLPTR));
        lbl_ans->setText(QApplication::translate("UIRegister", "<html><head/><body><p><span style=\" font-weight:600;\">\346\211\276\345\233\236\345\257\206\347\240\201\347\255\224\346\241\210\357\274\232</span></p></body></html>", Q_NULLPTR));
        btnRegister->setText(QApplication::translate("UIRegister", "\347\241\256\350\256\244\344\277\241\346\201\257\346\227\240\350\257\257\357\274\214\346\263\250\345\206\214\357\274\201", Q_NULLPTR));
        btnCancel->setText(QApplication::translate("UIRegister", "\345\217\226\346\266\210\346\263\250\345\206\214", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UIRegister: public Ui_UIRegister {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIREGISTER_H
