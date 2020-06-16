/********************************************************************************
** Form generated from reading UI file 'UnlockDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNLOCKDLG_H
#define UI_UNLOCKDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UnlockDlg
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *passwordEdit;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *UnlockDlg)
    {
        if (UnlockDlg->objectName().isEmpty())
            UnlockDlg->setObjectName(QStringLiteral("UnlockDlg"));
        UnlockDlg->resize(531, 218);
        UnlockDlg->setStyleSheet(QStringLiteral(""));
        horizontalLayout_3 = new QHBoxLayout(UnlockDlg);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(UnlockDlg);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe \346\245\267\344\275\223 Std R"));
        font.setPointSize(50);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral("background-color: rgb(85, 170, 255);"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(UnlockDlg);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setEnabled(true);
        label_2->setMaximumSize(QSize(130, 130));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/images/Resources/images/error.png")));
        label_2->setScaledContents(true);

        horizontalLayout_2->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(UnlockDlg);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Adobe \346\245\267\344\275\223 Std R"));
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        label_3->setFont(font1);

        horizontalLayout->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        passwordEdit = new QLineEdit(UnlockDlg);
        passwordEdit->setObjectName(QStringLiteral("passwordEdit"));
        passwordEdit->setEchoMode(QLineEdit::Password);

        horizontalLayout->addWidget(passwordEdit);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout);


        retranslateUi(UnlockDlg);

        QMetaObject::connectSlotsByName(UnlockDlg);
    } // setupUi

    void retranslateUi(QDialog *UnlockDlg)
    {
        UnlockDlg->setWindowTitle(QApplication::translate("UnlockDlg", "UnlockDlg", 0));
        label->setText(QApplication::translate("UnlockDlg", "\346\265\213\350\257\225NG\350\257\267\350\247\243\351\224\201", 0));
        label_2->setText(QString());
        label_3->setText(QApplication::translate("UnlockDlg", "\350\257\267\350\276\223\345\205\245\350\247\243\351\224\201\345\257\206\347\240\201", 0));
    } // retranslateUi

};

namespace Ui {
    class UnlockDlg: public Ui_UnlockDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNLOCKDLG_H
