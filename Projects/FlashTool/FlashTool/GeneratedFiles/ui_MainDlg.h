/********************************************************************************
** Form generated from reading UI file 'MainDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDLG_H
#define UI_MAINDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainDlg
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *title;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_9;
    QLabel *label_3;
    QComboBox *enableName;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QLabel *label_5;
    QLabel *burnMode;
    QSpacerItem *horizontalSpacer;
    QLabel *label_6;
    QLabel *label_4;
    QLabel *cpuUsageRate;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_8;
    QLabel *label_7;
    QLabel *memUsageRate;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label_10;
    QLabel *label_2;
    QComboBox *enableChannel;
    QPushButton *reload;
    QPushButton *setting;
    QPushButton *connect;
    QPushButton *exit;

    void setupUi(QWidget *MainDlg)
    {
        if (MainDlg->objectName().isEmpty())
            MainDlg->setObjectName(QStringLiteral("MainDlg"));
        MainDlg->resize(882, 522);
        MainDlg->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(MainDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 5, 0, 0);
        title = new QLabel(MainDlg);
        title->setObjectName(QStringLiteral("title"));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(40);
        font.setItalic(true);
        title->setFont(font);
        title->setStyleSheet(QStringLiteral("background-image: url(:/Images/Resources/Images/yishu_shuma.jpg);"));
        title->setFrameShape(QFrame::NoFrame);
        title->setLineWidth(2);
        title->setMidLineWidth(2);
        title->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(title);

        scrollArea = new QScrollArea(MainDlg);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setFrameShadow(QFrame::Plain);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 882, 355));
        scrollAreaWidgetContents->setStyleSheet(QStringLiteral(""));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        groupBox_2 = new QGroupBox(MainDlg);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setPixmap(QPixmap(QString::fromUtf8(":/Images/Resources/Images/chrome.ico")));

        horizontalLayout_2->addWidget(label_9);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        label_3->setFont(font1);

        horizontalLayout_2->addWidget(label_3);

        enableName = new QComboBox(groupBox_2);
        enableName->setObjectName(QStringLiteral("enableName"));
        enableName->setEnabled(false);

        horizontalLayout_2->addWidget(enableName);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/Images/Resources/Images/type.ico")));

        horizontalLayout_2->addWidget(label);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        label_5->setFont(font2);

        horizontalLayout_2->addWidget(label_5);

        burnMode = new QLabel(groupBox_2);
        burnMode->setObjectName(QStringLiteral("burnMode"));
        QFont font3;
        font3.setPointSize(10);
        burnMode->setFont(font3);

        horizontalLayout_2->addWidget(burnMode);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/Images/Resources/Images/activity.ico")));

        horizontalLayout_2->addWidget(label_6);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font3);

        horizontalLayout_2->addWidget(label_4);

        cpuUsageRate = new QLabel(groupBox_2);
        cpuUsageRate->setObjectName(QStringLiteral("cpuUsageRate"));
        QFont font4;
        font4.setBold(true);
        font4.setItalic(true);
        font4.setWeight(75);
        cpuUsageRate->setFont(font4);

        horizontalLayout_2->addWidget(cpuUsageRate);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setPixmap(QPixmap(QString::fromUtf8(":/Images/Resources/Images/dash.ico")));

        horizontalLayout_2->addWidget(label_8);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font3);

        horizontalLayout_2->addWidget(label_7);

        memUsageRate = new QLabel(groupBox_2);
        memUsageRate->setObjectName(QStringLiteral("memUsageRate"));
        memUsageRate->setFont(font4);

        horizontalLayout_2->addWidget(memUsageRate);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(MainDlg);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setFont(font3);
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);
        label_10->setMaximumSize(QSize(16, 16777215));
        label_10->setPixmap(QPixmap(QString::fromUtf8(":/Images/Resources/Images/chrome.ico")));

        horizontalLayout->addWidget(label_10);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setFont(font2);

        horizontalLayout->addWidget(label_2);

        enableChannel = new QComboBox(groupBox);
        enableChannel->setObjectName(QStringLiteral("enableChannel"));

        horizontalLayout->addWidget(enableChannel);

        reload = new QPushButton(groupBox);
        reload->setObjectName(QStringLiteral("reload"));
        reload->setFont(font2);
        reload->setStyleSheet(QStringLiteral(""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Images/Resources/Images/reload.png"), QSize(), QIcon::Normal, QIcon::Off);
        reload->setIcon(icon);

        horizontalLayout->addWidget(reload);

        setting = new QPushButton(groupBox);
        setting->setObjectName(QStringLiteral("setting"));
        setting->setFont(font2);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Images/Resources/Images/book.ico"), QSize(), QIcon::Normal, QIcon::Off);
        setting->setIcon(icon1);

        horizontalLayout->addWidget(setting);

        connect = new QPushButton(groupBox);
        connect->setObjectName(QStringLiteral("connect"));
        connect->setFont(font3);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Images/Resources/Images/wifi.ico"), QSize(), QIcon::Normal, QIcon::Off);
        connect->setIcon(icon2);

        horizontalLayout->addWidget(connect);

        exit = new QPushButton(groupBox);
        exit->setObjectName(QStringLiteral("exit"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Images/Resources/Images/exit.ico"), QSize(), QIcon::Normal, QIcon::Off);
        exit->setIcon(icon3);

        horizontalLayout->addWidget(exit);


        verticalLayout->addWidget(groupBox);


        retranslateUi(MainDlg);

        QMetaObject::connectSlotsByName(MainDlg);
    } // setupUi

    void retranslateUi(QWidget *MainDlg)
    {
        MainDlg->setWindowTitle(QApplication::translate("MainDlg", "Flash\347\203\247\345\275\225\345\267\245\345\205\267", 0));
        title->setText(QApplication::translate("MainDlg", "FLASH/EEPROM\347\203\247\345\275\225\345\267\245\345\205\267", 0));
        groupBox_2->setTitle(QApplication::translate("MainDlg", "\347\203\247\345\275\225\345\214\272\345\237\237", 0));
        label_9->setText(QString());
        label_3->setText(QApplication::translate("MainDlg", "\347\203\247\345\275\225\346\234\272\347\247\215\345\220\215:", 0));
        label->setText(QString());
        label_5->setText(QApplication::translate("MainDlg", "\347\203\247\345\275\225\346\250\241\345\274\217:", 0));
        burnMode->setText(QApplication::translate("MainDlg", "019\346\221\204\345\203\217\345\244\264\347\203\247\345\275\225", 0));
        label_6->setText(QString());
        label_4->setText(QApplication::translate("MainDlg", "CPU\345\215\240\347\224\250:", 0));
        cpuUsageRate->setText(QApplication::translate("MainDlg", "100%", 0));
        label_8->setText(QString());
        label_7->setText(QApplication::translate("MainDlg", "\345\206\205\345\255\230\345\215\240\347\224\250:", 0));
        memUsageRate->setText(QApplication::translate("MainDlg", "90%", 0));
        groupBox->setTitle(QApplication::translate("MainDlg", "\346\214\211\351\222\256\345\214\272\345\237\237", 0));
        label_10->setText(QString());
        label_2->setText(QApplication::translate("MainDlg", "\345\220\257\347\224\250\351\200\232\351\201\223\346\225\260:", 0));
        reload->setText(QApplication::translate("MainDlg", "\351\207\215\346\226\260\345\212\240\350\275\275\350\256\276\345\244\207", 0));
        setting->setText(QApplication::translate("MainDlg", "\346\237\245\347\234\213\351\205\215\347\275\256\344\277\241\346\201\257", 0));
        connect->setText(QApplication::translate("MainDlg", "\350\277\236\346\216\245", 0));
        exit->setText(QApplication::translate("MainDlg", "\351\200\200\345\207\272", 0));
    } // retranslateUi

};

namespace Ui {
    class MainDlg: public Ui_MainDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDLG_H
