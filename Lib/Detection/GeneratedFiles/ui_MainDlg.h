/********************************************************************************
** Form generated from reading UI file 'MainDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDLG_H
#define UI_MAINDLG_H

#include <Detection/QLabelEx.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainDlgClass
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabelEx *imageLabel;
    QListWidget *recordList;
    QVBoxLayout *verticalLayout;
    QLabel *resultLabel;
    QListWidget *resultList;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *systemLabel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *statusLabel;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *cpuLabel;
    QLabel *label_5;
    QLabel *memLabel;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *settingButton;
    QPushButton *connectButton;
    QPushButton *exitButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *MainDlgClass)
    {
        if (MainDlgClass->objectName().isEmpty())
            MainDlgClass->setObjectName(QStringLiteral("MainDlgClass"));
        MainDlgClass->resize(1011, 697);
        horizontalLayout_3 = new QHBoxLayout(MainDlgClass);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        imageLabel = new QLabelEx(MainDlgClass);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(imageLabel->sizePolicy().hasHeightForWidth());
        imageLabel->setSizePolicy(sizePolicy);
        imageLabel->setMinimumSize(QSize(720, 480));
        imageLabel->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));

        verticalLayout_2->addWidget(imageLabel);

        recordList = new QListWidget(MainDlgClass);
        recordList->setObjectName(QStringLiteral("recordList"));

        verticalLayout_2->addWidget(recordList);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        resultLabel = new QLabel(MainDlgClass);
        resultLabel->setObjectName(QStringLiteral("resultLabel"));
        QFont font;
        font.setPointSize(150);
        resultLabel->setFont(font);
        resultLabel->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        resultLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(resultLabel);

        resultList = new QListWidget(MainDlgClass);
        resultList->setObjectName(QStringLiteral("resultList"));

        verticalLayout->addWidget(resultList);

        groupBox_2 = new QGroupBox(MainDlgClass);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setAutoFillBackground(false);
        label->setFrameShape(QFrame::NoFrame);
        label->setTextFormat(Qt::AutoText);
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/Resources/images/system.ico")));
        label->setScaledContents(false);

        horizontalLayout_4->addWidget(label);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(9);
        label_2->setFont(font1);

        horizontalLayout_4->addWidget(label_2);

        systemLabel = new QLabel(groupBox_2);
        systemLabel->setObjectName(QStringLiteral("systemLabel"));

        horizontalLayout_4->addWidget(systemLabel);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/images/Resources/images/system.ico")));

        horizontalLayout_2->addWidget(label_4);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_3);

        statusLabel = new QLabel(groupBox_2);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));

        horizontalLayout_2->addWidget(statusLabel);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);
        label_7->setPixmap(QPixmap(QString::fromUtf8(":/images/Resources/images/system.ico")));

        horizontalLayout_6->addWidget(label_7);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(label_6);

        cpuLabel = new QLabel(groupBox_2);
        cpuLabel->setObjectName(QStringLiteral("cpuLabel"));
        sizePolicy1.setHeightForWidth(cpuLabel->sizePolicy().hasHeightForWidth());
        cpuLabel->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setPointSize(9);
        font2.setBold(true);
        font2.setItalic(true);
        font2.setWeight(75);
        cpuLabel->setFont(font2);

        horizontalLayout_6->addWidget(cpuLabel);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(label_5);

        memLabel = new QLabel(groupBox_2);
        memLabel->setObjectName(QStringLiteral("memLabel"));
        QFont font3;
        font3.setBold(true);
        font3.setItalic(true);
        font3.setWeight(75);
        memLabel->setFont(font3);

        horizontalLayout_6->addWidget(memLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_6);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(MainDlgClass);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        settingButton = new QPushButton(groupBox);
        settingButton->setObjectName(QStringLiteral("settingButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Resources/images/setting.ico"), QSize(), QIcon::Normal, QIcon::Off);
        settingButton->setIcon(icon);

        horizontalLayout->addWidget(settingButton);

        connectButton = new QPushButton(groupBox);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/Resources/images/connect.ico"), QSize(), QIcon::Normal, QIcon::Off);
        connectButton->setIcon(icon1);

        horizontalLayout->addWidget(connectButton);

        exitButton = new QPushButton(groupBox);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/Resources/images/exit.ico"), QSize(), QIcon::Normal, QIcon::Off);
        exitButton->setIcon(icon2);

        horizontalLayout->addWidget(exitButton);


        verticalLayout->addWidget(groupBox);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        retranslateUi(MainDlgClass);

        QMetaObject::connectSlotsByName(MainDlgClass);
    } // setupUi

    void retranslateUi(QWidget *MainDlgClass)
    {
        MainDlgClass->setWindowTitle(QApplication::translate("MainDlgClass", "\345\212\237\350\203\275\346\243\200\346\265\213", 0));
        imageLabel->setText(QString());
        resultLabel->setText(QApplication::translate("MainDlgClass", "NO", 0));
        groupBox_2->setTitle(QApplication::translate("MainDlgClass", "\346\265\213\350\257\225\347\212\266\346\200\201", 0));
        label->setText(QString());
        label_2->setText(QApplication::translate("MainDlgClass", "\347\263\273\347\273\237\347\212\266\346\200\201:", 0));
        systemLabel->setText(QString());
        label_4->setText(QString());
        label_3->setText(QApplication::translate("MainDlgClass", "\345\275\223\345\211\215\347\212\266\346\200\201:", 0));
        statusLabel->setText(QString());
        label_7->setText(QString());
        label_6->setText(QApplication::translate("MainDlgClass", "CPU \345\215\240\347\224\250:", 0));
        cpuLabel->setText(QApplication::translate("MainDlgClass", "  0.00%", 0));
        label_5->setText(QApplication::translate("MainDlgClass", "\345\206\205\345\255\230\345\215\240\347\224\250:", 0));
        memLabel->setText(QApplication::translate("MainDlgClass", "0%", 0));
        groupBox->setTitle(QApplication::translate("MainDlgClass", "\346\265\213\350\257\225\346\214\211\351\222\256", 0));
        settingButton->setText(QApplication::translate("MainDlgClass", "\350\256\276\347\275\256", 0));
        connectButton->setText(QApplication::translate("MainDlgClass", "\350\277\236\346\216\245", 0));
        exitButton->setText(QApplication::translate("MainDlgClass", "\351\200\200\345\207\272", 0));
    } // retranslateUi

};

namespace Ui {
    class MainDlgClass: public Ui_MainDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDLG_H
