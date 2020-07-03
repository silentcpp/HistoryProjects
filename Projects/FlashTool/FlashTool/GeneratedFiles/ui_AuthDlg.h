/********************************************************************************
** Form generated from reading UI file 'AuthDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHDLG_H
#define UI_AUTHDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AuthDlg
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QLineEdit *userName;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_3;
    QLineEdit *password;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *affirm;
    QSpacerItem *horizontalSpacer;
    QPushButton *exit;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *AuthDlg)
    {
        if (AuthDlg->objectName().isEmpty())
            AuthDlg->setObjectName(QStringLiteral("AuthDlg"));
        AuthDlg->resize(386, 182);
        verticalLayout = new QVBoxLayout(AuthDlg);
        verticalLayout->setSpacing(5);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(AuthDlg);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe \346\245\267\344\275\223 Std R"));
        font.setPointSize(30);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral(""));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        label_2 = new QLabel(AuthDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        userName = new QLineEdit(AuthDlg);
        userName->setObjectName(QStringLiteral("userName"));

        horizontalLayout->addWidget(userName);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        label_3 = new QLabel(AuthDlg);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        password = new QLineEdit(AuthDlg);
        password->setObjectName(QStringLiteral("password"));

        horizontalLayout_2->addWidget(password);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        affirm = new QPushButton(AuthDlg);
        affirm->setObjectName(QStringLiteral("affirm"));

        horizontalLayout_3->addWidget(affirm);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        exit = new QPushButton(AuthDlg);
        exit->setObjectName(QStringLiteral("exit"));

        horizontalLayout_3->addWidget(exit);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(AuthDlg);

        QMetaObject::connectSlotsByName(AuthDlg);
    } // setupUi

    void retranslateUi(QWidget *AuthDlg)
    {
        AuthDlg->setWindowTitle(QApplication::translate("AuthDlg", "AuthDlg", 0));
        label->setText(QApplication::translate("AuthDlg", "\344\277\256\346\224\271\350\256\244\350\257\201", 0));
        label_2->setText(QApplication::translate("AuthDlg", "\347\224\250\346\210\267\345\220\215", 0));
        label_3->setText(QApplication::translate("AuthDlg", "\345\257\206  \347\240\201", 0));
        affirm->setText(QApplication::translate("AuthDlg", "\347\241\256\350\256\244", 0));
        exit->setText(QApplication::translate("AuthDlg", "\351\200\200\345\207\272", 0));
    } // retranslateUi

};

namespace Ui {
    class AuthDlg: public Ui_AuthDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHDLG_H
