/********************************************************************************
** Form generated from reading UI file 'SettingDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDLG_H
#define UI_SETTINGDLG_H

#include <Detection/QLabelEx.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingDlg
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QTreeWidget *configTree;
    QHBoxLayout *horizontalLayout;
    QPushButton *configExpand;
    QPushButton *configAdd;
    QPushButton *configDel;
    QPushButton *configSave;
    QPushButton *configExit;
    QWidget *tab_8;
    QVBoxLayout *verticalLayout_14;
    QGridLayout *gridLayout_8;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_10;
    QGridLayout *gridLayout_4;
    QCheckBox *relayIo8;
    QCheckBox *relayIo0;
    QCheckBox *relayIo9;
    QCheckBox *relayIo3;
    QCheckBox *relayIo1;
    QCheckBox *relayIo10;
    QCheckBox *relayIo11;
    QCheckBox *relayIo12;
    QCheckBox *relayIo13;
    QCheckBox *relayIo14;
    QCheckBox *relayIo15;
    QCheckBox *relayIo2;
    QCheckBox *relayIo4;
    QCheckBox *relayIo5;
    QCheckBox *relayIo6;
    QCheckBox *relayIo7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_15;
    QComboBox *relayCombo;
    QPushButton *relayConnect;
    QSpacerItem *verticalSpacer_4;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_11;
    QGridLayout *gridLayout_5;
    QLabel *label_18;
    QLabel *label_17;
    QLineEdit *powerVoltage;
    QComboBox *powerCombo;
    QLineEdit *powerCurrent;
    QLabel *label_16;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *powerOn;
    QPushButton *powerConnect;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_12;
    QGridLayout *gridLayout_6;
    QLabel *label_19;
    QLineEdit *currentValue;
    QLabel *label_20;
    QComboBox *currentCombo;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *currentGetValue;
    QPushButton *currentConnect;
    QSpacerItem *verticalSpacer_5;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_13;
    QGridLayout *gridLayout_7;
    QLabel *label_21;
    QLineEdit *voltageValue;
    QLabel *label_22;
    QComboBox *voltageCombo;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *voltageGetValue;
    QPushButton *voltageConnect;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *horizontalSpacer_5;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_13;
    QLabelEx *label;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *startCapture;
    QPushButton *stopCapture;
    QPushButton *saveCoord;
    QSpacerItem *horizontalSpacer_4;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *canTable;
    QTabWidget *tabWidget_2;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *canFrameId;
    QLineEdit *canDataEdit;
    QLabel *label_4;
    QComboBox *canFrameType;
    QPushButton *canBaseStop;
    QLabel *label_3;
    QLineEdit *canSendDelay;
    QLabel *label_6;
    QPushButton *canBaseSend;
    QComboBox *canFrameFormat;
    QLineEdit *canSendCount;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_5;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *canStartup;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *tableWidget;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_7;
    QGridLayout *gridLayout_2;
    QLabel *label_8;
    QLineEdit *lineEdit;
    QLabel *label_9;
    QLineEdit *lineEdit_2;
    QLabel *label_10;
    QLineEdit *lineEdit_3;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *advanceSend;
    QPushButton *advanceStop;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QSpacerItem *verticalSpacer;
    QWidget *tab_7;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QLabel *label_11;
    QLabel *frameVersion;
    QLabel *label_12;
    QLabel *fileVersion;
    QLabel *label_14;
    QLabel *appVersion;

    void setupUi(QWidget *SettingDlg)
    {
        if (SettingDlg->objectName().isEmpty())
            SettingDlg->setObjectName(QStringLiteral("SettingDlg"));
        SettingDlg->resize(762, 592);
        verticalLayout = new QVBoxLayout(SettingDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(SettingDlg);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        configTree = new QTreeWidget(tab);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        configTree->setHeaderItem(__qtreewidgetitem);
        configTree->setObjectName(QStringLiteral("configTree"));

        verticalLayout_2->addWidget(configTree);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        configExpand = new QPushButton(tab);
        configExpand->setObjectName(QStringLiteral("configExpand"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Resources/images/expand.ico"), QSize(), QIcon::Normal, QIcon::Off);
        configExpand->setIcon(icon);

        horizontalLayout->addWidget(configExpand);

        configAdd = new QPushButton(tab);
        configAdd->setObjectName(QStringLiteral("configAdd"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/Resources/images/add.ico"), QSize(), QIcon::Normal, QIcon::Off);
        configAdd->setIcon(icon1);

        horizontalLayout->addWidget(configAdd);

        configDel = new QPushButton(tab);
        configDel->setObjectName(QStringLiteral("configDel"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/Resources/images/del.ico"), QSize(), QIcon::Normal, QIcon::Off);
        configDel->setIcon(icon2);

        horizontalLayout->addWidget(configDel);

        configSave = new QPushButton(tab);
        configSave->setObjectName(QStringLiteral("configSave"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/Resources/images/save.ico"), QSize(), QIcon::Normal, QIcon::Off);
        configSave->setIcon(icon3);

        horizontalLayout->addWidget(configSave);

        configExit = new QPushButton(tab);
        configExit->setObjectName(QStringLiteral("configExit"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/Resources/images/treeExit.ico"), QSize(), QIcon::Normal, QIcon::Off);
        configExit->setIcon(icon4);

        horizontalLayout->addWidget(configExit);


        verticalLayout_2->addLayout(horizontalLayout);

        tabWidget->addTab(tab, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QStringLiteral("tab_8"));
        verticalLayout_14 = new QVBoxLayout(tab_8);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(6);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        groupBox_5 = new QGroupBox(tab_8);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        verticalLayout_10 = new QVBoxLayout(groupBox_5);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        relayIo8 = new QCheckBox(groupBox_5);
        relayIo8->setObjectName(QStringLiteral("relayIo8"));

        gridLayout_4->addWidget(relayIo8, 0, 1, 1, 1);

        relayIo0 = new QCheckBox(groupBox_5);
        relayIo0->setObjectName(QStringLiteral("relayIo0"));

        gridLayout_4->addWidget(relayIo0, 0, 0, 1, 1);

        relayIo9 = new QCheckBox(groupBox_5);
        relayIo9->setObjectName(QStringLiteral("relayIo9"));

        gridLayout_4->addWidget(relayIo9, 1, 1, 1, 1);

        relayIo3 = new QCheckBox(groupBox_5);
        relayIo3->setObjectName(QStringLiteral("relayIo3"));

        gridLayout_4->addWidget(relayIo3, 3, 0, 1, 1);

        relayIo1 = new QCheckBox(groupBox_5);
        relayIo1->setObjectName(QStringLiteral("relayIo1"));

        gridLayout_4->addWidget(relayIo1, 1, 0, 1, 1);

        relayIo10 = new QCheckBox(groupBox_5);
        relayIo10->setObjectName(QStringLiteral("relayIo10"));

        gridLayout_4->addWidget(relayIo10, 2, 1, 1, 1);

        relayIo11 = new QCheckBox(groupBox_5);
        relayIo11->setObjectName(QStringLiteral("relayIo11"));

        gridLayout_4->addWidget(relayIo11, 3, 1, 1, 1);

        relayIo12 = new QCheckBox(groupBox_5);
        relayIo12->setObjectName(QStringLiteral("relayIo12"));

        gridLayout_4->addWidget(relayIo12, 4, 1, 1, 1);

        relayIo13 = new QCheckBox(groupBox_5);
        relayIo13->setObjectName(QStringLiteral("relayIo13"));

        gridLayout_4->addWidget(relayIo13, 5, 1, 1, 1);

        relayIo14 = new QCheckBox(groupBox_5);
        relayIo14->setObjectName(QStringLiteral("relayIo14"));

        gridLayout_4->addWidget(relayIo14, 6, 1, 1, 1);

        relayIo15 = new QCheckBox(groupBox_5);
        relayIo15->setObjectName(QStringLiteral("relayIo15"));

        gridLayout_4->addWidget(relayIo15, 7, 1, 1, 1);

        relayIo2 = new QCheckBox(groupBox_5);
        relayIo2->setObjectName(QStringLiteral("relayIo2"));

        gridLayout_4->addWidget(relayIo2, 2, 0, 1, 1);

        relayIo4 = new QCheckBox(groupBox_5);
        relayIo4->setObjectName(QStringLiteral("relayIo4"));

        gridLayout_4->addWidget(relayIo4, 4, 0, 1, 1);

        relayIo5 = new QCheckBox(groupBox_5);
        relayIo5->setObjectName(QStringLiteral("relayIo5"));

        gridLayout_4->addWidget(relayIo5, 5, 0, 1, 1);

        relayIo6 = new QCheckBox(groupBox_5);
        relayIo6->setObjectName(QStringLiteral("relayIo6"));

        gridLayout_4->addWidget(relayIo6, 6, 0, 1, 1);

        relayIo7 = new QCheckBox(groupBox_5);
        relayIo7->setObjectName(QStringLiteral("relayIo7"));

        gridLayout_4->addWidget(relayIo7, 7, 0, 1, 1);


        verticalLayout_10->addLayout(gridLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_15 = new QLabel(groupBox_5);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_5->addWidget(label_15);

        relayCombo = new QComboBox(groupBox_5);
        relayCombo->setObjectName(QStringLiteral("relayCombo"));

        horizontalLayout_5->addWidget(relayCombo);

        relayConnect = new QPushButton(groupBox_5);
        relayConnect->setObjectName(QStringLiteral("relayConnect"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/Resources/images/key.ico"), QSize(), QIcon::Normal, QIcon::Off);
        relayConnect->setIcon(icon5);

        horizontalLayout_5->addWidget(relayConnect);


        verticalLayout_10->addLayout(horizontalLayout_5);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_4);


        gridLayout_8->addWidget(groupBox_5, 1, 0, 2, 1);

        groupBox_6 = new QGroupBox(tab_8);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        verticalLayout_11 = new QVBoxLayout(groupBox_6);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_18 = new QLabel(groupBox_6);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_5->addWidget(label_18, 1, 0, 1, 1);

        label_17 = new QLabel(groupBox_6);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_5->addWidget(label_17, 0, 0, 1, 1);

        powerVoltage = new QLineEdit(groupBox_6);
        powerVoltage->setObjectName(QStringLiteral("powerVoltage"));

        gridLayout_5->addWidget(powerVoltage, 0, 1, 1, 1);

        powerCombo = new QComboBox(groupBox_6);
        powerCombo->setObjectName(QStringLiteral("powerCombo"));

        gridLayout_5->addWidget(powerCombo, 2, 1, 1, 1);

        powerCurrent = new QLineEdit(groupBox_6);
        powerCurrent->setObjectName(QStringLiteral("powerCurrent"));

        gridLayout_5->addWidget(powerCurrent, 1, 1, 1, 1);

        label_16 = new QLabel(groupBox_6);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_5->addWidget(label_16, 2, 0, 1, 1);


        verticalLayout_11->addLayout(gridLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        powerOn = new QPushButton(groupBox_6);
        powerOn->setObjectName(QStringLiteral("powerOn"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/Resources/images/dash.ico"), QSize(), QIcon::Normal, QIcon::Off);
        powerOn->setIcon(icon6);

        horizontalLayout_6->addWidget(powerOn);

        powerConnect = new QPushButton(groupBox_6);
        powerConnect->setObjectName(QStringLiteral("powerConnect"));
        powerConnect->setIcon(icon5);

        horizontalLayout_6->addWidget(powerConnect);


        verticalLayout_11->addLayout(horizontalLayout_6);


        gridLayout_8->addWidget(groupBox_6, 0, 0, 1, 2);

        groupBox_7 = new QGroupBox(tab_8);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        verticalLayout_12 = new QVBoxLayout(groupBox_7);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        label_19 = new QLabel(groupBox_7);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_6->addWidget(label_19, 0, 0, 1, 1);

        currentValue = new QLineEdit(groupBox_7);
        currentValue->setObjectName(QStringLiteral("currentValue"));
        currentValue->setEnabled(false);

        gridLayout_6->addWidget(currentValue, 0, 1, 1, 1);

        label_20 = new QLabel(groupBox_7);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout_6->addWidget(label_20, 1, 0, 1, 1);

        currentCombo = new QComboBox(groupBox_7);
        currentCombo->setObjectName(QStringLiteral("currentCombo"));

        gridLayout_6->addWidget(currentCombo, 1, 1, 1, 1);


        verticalLayout_12->addLayout(gridLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        currentGetValue = new QPushButton(groupBox_7);
        currentGetValue->setObjectName(QStringLiteral("currentGetValue"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/Resources/images/monitor.ico"), QSize(), QIcon::Normal, QIcon::Off);
        currentGetValue->setIcon(icon7);

        horizontalLayout_7->addWidget(currentGetValue);

        currentConnect = new QPushButton(groupBox_7);
        currentConnect->setObjectName(QStringLiteral("currentConnect"));
        currentConnect->setIcon(icon5);

        horizontalLayout_7->addWidget(currentConnect);


        verticalLayout_12->addLayout(horizontalLayout_7);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_12->addItem(verticalSpacer_5);


        gridLayout_8->addWidget(groupBox_7, 1, 1, 1, 1);

        groupBox_8 = new QGroupBox(tab_8);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        verticalLayout_13 = new QVBoxLayout(groupBox_8);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        label_21 = new QLabel(groupBox_8);
        label_21->setObjectName(QStringLiteral("label_21"));

        gridLayout_7->addWidget(label_21, 0, 0, 1, 1);

        voltageValue = new QLineEdit(groupBox_8);
        voltageValue->setObjectName(QStringLiteral("voltageValue"));
        voltageValue->setEnabled(false);

        gridLayout_7->addWidget(voltageValue, 0, 1, 1, 1);

        label_22 = new QLabel(groupBox_8);
        label_22->setObjectName(QStringLiteral("label_22"));

        gridLayout_7->addWidget(label_22, 1, 0, 1, 1);

        voltageCombo = new QComboBox(groupBox_8);
        voltageCombo->setObjectName(QStringLiteral("voltageCombo"));

        gridLayout_7->addWidget(voltageCombo, 1, 1, 1, 1);


        verticalLayout_13->addLayout(gridLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        voltageGetValue = new QPushButton(groupBox_8);
        voltageGetValue->setObjectName(QStringLiteral("voltageGetValue"));
        voltageGetValue->setIcon(icon7);

        horizontalLayout_8->addWidget(voltageGetValue);

        voltageConnect = new QPushButton(groupBox_8);
        voltageConnect->setObjectName(QStringLiteral("voltageConnect"));
        voltageConnect->setIcon(icon5);

        horizontalLayout_8->addWidget(voltageConnect);


        verticalLayout_13->addLayout(horizontalLayout_8);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_13->addItem(verticalSpacer_6);


        gridLayout_8->addWidget(groupBox_8, 2, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_5, 1, 2, 1, 1);


        verticalLayout_14->addLayout(gridLayout_8);

        tabWidget->addTab(tab_8, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayout_4 = new QVBoxLayout(tab_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_13 = new QLabel(tab_3);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setStyleSheet(QStringLiteral("color: rgb(255, 0, 255);"));

        verticalLayout_4->addWidget(label_13);

        label = new QLabelEx(tab_3);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(720, 480));
        label->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));

        verticalLayout_4->addWidget(label);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        startCapture = new QPushButton(tab_3);
        startCapture->setObjectName(QStringLiteral("startCapture"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/Resources/images/connect.ico"), QSize(), QIcon::Normal, QIcon::Off);
        startCapture->setIcon(icon8);

        horizontalLayout_4->addWidget(startCapture);

        stopCapture = new QPushButton(tab_3);
        stopCapture->setObjectName(QStringLiteral("stopCapture"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/images/Resources/images/exit.ico"), QSize(), QIcon::Normal, QIcon::Off);
        stopCapture->setIcon(icon9);

        horizontalLayout_4->addWidget(stopCapture);

        saveCoord = new QPushButton(tab_3);
        saveCoord->setObjectName(QStringLiteral("saveCoord"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/images/Resources/images/setting.ico"), QSize(), QIcon::Normal, QIcon::Off);
        saveCoord->setIcon(icon10);

        horizontalLayout_4->addWidget(saveCoord);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(horizontalLayout_4);

        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_5 = new QVBoxLayout(tab_2);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        canTable = new QTableWidget(tab_2);
        if (canTable->columnCount() < 8)
            canTable->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        canTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        canTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        canTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        canTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        canTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        canTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        canTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        canTable->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        canTable->setObjectName(QStringLiteral("canTable"));

        verticalLayout_5->addWidget(canTable);

        tabWidget_2 = new QTabWidget(tab_2);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setTabPosition(QTabWidget::South);
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        verticalLayout_3 = new QVBoxLayout(tab_4);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox = new QGroupBox(tab_4);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setAutoFillBackground(false);
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        canFrameId = new QLineEdit(groupBox);
        canFrameId->setObjectName(QStringLiteral("canFrameId"));

        gridLayout->addWidget(canFrameId, 0, 3, 1, 1);

        canDataEdit = new QLineEdit(groupBox);
        canDataEdit->setObjectName(QStringLiteral("canDataEdit"));

        gridLayout->addWidget(canDataEdit, 0, 5, 1, 2);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 0, 2, 1, 1);

        canFrameType = new QComboBox(groupBox);
        canFrameType->setObjectName(QStringLiteral("canFrameType"));

        gridLayout->addWidget(canFrameType, 0, 1, 1, 1);

        canBaseStop = new QPushButton(groupBox);
        canBaseStop->setObjectName(QStringLiteral("canBaseStop"));
        canBaseStop->setIcon(icon2);

        gridLayout->addWidget(canBaseStop, 1, 7, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        canSendDelay = new QLineEdit(groupBox);
        canSendDelay->setObjectName(QStringLiteral("canSendDelay"));

        gridLayout->addWidget(canSendDelay, 1, 6, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 0, 4, 1, 1);

        canBaseSend = new QPushButton(groupBox);
        canBaseSend->setObjectName(QStringLiteral("canBaseSend"));
        canBaseSend->setIcon(icon3);

        gridLayout->addWidget(canBaseSend, 0, 7, 1, 1);

        canFrameFormat = new QComboBox(groupBox);
        canFrameFormat->setObjectName(QStringLiteral("canFrameFormat"));

        gridLayout->addWidget(canFrameFormat, 1, 1, 1, 1);

        canSendCount = new QLineEdit(groupBox);
        canSendCount->setObjectName(QStringLiteral("canSendCount"));

        gridLayout->addWidget(canSendCount, 1, 3, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 8, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 3, 3, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 1, 2, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 1, 4, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 8, 1, 1);

        canStartup = new QPushButton(groupBox);
        canStartup->setObjectName(QStringLiteral("canStartup"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/images/Resources/images/bird.ico"), QSize(), QIcon::Normal, QIcon::Off);
        canStartup->setIcon(icon11);

        gridLayout->addWidget(canStartup, 2, 7, 1, 1);


        verticalLayout_3->addWidget(groupBox);

        tabWidget_2->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        verticalLayout_6 = new QVBoxLayout(tab_5);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        groupBox_2 = new QGroupBox(tab_5);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        tableWidget = new QTableWidget(groupBox_2);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem12);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(100);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(tableWidget);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 0, 0, 1, 1);

        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_2->addWidget(lineEdit, 0, 1, 1, 2);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 1, 0, 1, 2);

        lineEdit_2 = new QLineEdit(groupBox_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout_2->addWidget(lineEdit_2, 1, 2, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_2->addWidget(label_10, 2, 0, 1, 2);

        lineEdit_3 = new QLineEdit(groupBox_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout_2->addWidget(lineEdit_3, 2, 2, 1, 1);


        verticalLayout_7->addLayout(gridLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        advanceSend = new QPushButton(groupBox_2);
        advanceSend->setObjectName(QStringLiteral("advanceSend"));
        advanceSend->setIcon(icon3);

        horizontalLayout_2->addWidget(advanceSend);

        advanceStop = new QPushButton(groupBox_2);
        advanceStop->setObjectName(QStringLiteral("advanceStop"));
        advanceStop->setIcon(icon2);

        horizontalLayout_2->addWidget(advanceStop);


        verticalLayout_7->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_7);


        verticalLayout_6->addWidget(groupBox_2);

        tabWidget_2->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        verticalLayout_9 = new QVBoxLayout(tab_6);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        groupBox_3 = new QGroupBox(tab_6);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_8 = new QVBoxLayout(groupBox_3);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        checkBox_6 = new QCheckBox(groupBox_3);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));

        verticalLayout_8->addWidget(checkBox_6);

        checkBox = new QCheckBox(groupBox_3);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        verticalLayout_8->addWidget(checkBox);

        checkBox_2 = new QCheckBox(groupBox_3);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        verticalLayout_8->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(groupBox_3);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        verticalLayout_8->addWidget(checkBox_3);

        checkBox_4 = new QCheckBox(groupBox_3);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));

        verticalLayout_8->addWidget(checkBox_4);

        checkBox_5 = new QCheckBox(groupBox_3);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));

        verticalLayout_8->addWidget(checkBox_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer);


        verticalLayout_9->addWidget(groupBox_3);

        tabWidget_2->addTab(tab_6, QString());

        verticalLayout_5->addWidget(tabWidget_2);

        tabWidget->addTab(tab_2, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        groupBox_4 = new QGroupBox(tab_7);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 40, 201, 131));
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_3->addWidget(label_11, 0, 0, 1, 1);

        frameVersion = new QLabel(groupBox_4);
        frameVersion->setObjectName(QStringLiteral("frameVersion"));

        gridLayout_3->addWidget(frameVersion, 0, 1, 1, 1);

        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_3->addWidget(label_12, 1, 0, 1, 1);

        fileVersion = new QLabel(groupBox_4);
        fileVersion->setObjectName(QStringLiteral("fileVersion"));

        gridLayout_3->addWidget(fileVersion, 1, 1, 1, 1);

        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_3->addWidget(label_14, 2, 0, 1, 1);

        appVersion = new QLabel(groupBox_4);
        appVersion->setObjectName(QStringLiteral("appVersion"));

        gridLayout_3->addWidget(appVersion, 2, 1, 1, 1);

        tabWidget->addTab(tab_7, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(SettingDlg);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SettingDlg);
    } // setupUi

    void retranslateUi(QWidget *SettingDlg)
    {
        SettingDlg->setWindowTitle(QApplication::translate("SettingDlg", "\350\256\276\347\275\256", 0));
        configExpand->setText(QApplication::translate("SettingDlg", "\345\205\250\351\203\250\345\261\225\345\274\200", 0));
        configAdd->setText(QApplication::translate("SettingDlg", "\346\267\273\345\212\240\350\212\202\347\202\271", 0));
        configDel->setText(QApplication::translate("SettingDlg", "\345\210\240\351\231\244\350\212\202\347\202\271", 0));
        configSave->setText(QApplication::translate("SettingDlg", "\344\277\235\345\255\230\346\225\260\346\215\256", 0));
        configExit->setText(QApplication::translate("SettingDlg", "\351\200\200\345\207\272", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SettingDlg", "\351\205\215\347\275\256", 0));
        groupBox_5->setTitle(QApplication::translate("SettingDlg", "\347\273\247\347\224\265\345\231\250", 0));
        relayIo8->setText(QApplication::translate("SettingDlg", "8", 0));
        relayIo0->setText(QApplication::translate("SettingDlg", "0", 0));
        relayIo9->setText(QApplication::translate("SettingDlg", "9", 0));
        relayIo3->setText(QApplication::translate("SettingDlg", "3", 0));
        relayIo1->setText(QApplication::translate("SettingDlg", "1", 0));
        relayIo10->setText(QApplication::translate("SettingDlg", "10", 0));
        relayIo11->setText(QApplication::translate("SettingDlg", "11", 0));
        relayIo12->setText(QApplication::translate("SettingDlg", "12", 0));
        relayIo13->setText(QApplication::translate("SettingDlg", "13", 0));
        relayIo14->setText(QApplication::translate("SettingDlg", "14", 0));
        relayIo15->setText(QApplication::translate("SettingDlg", "15", 0));
        relayIo2->setText(QApplication::translate("SettingDlg", "2", 0));
        relayIo4->setText(QApplication::translate("SettingDlg", "4", 0));
        relayIo5->setText(QApplication::translate("SettingDlg", "5", 0));
        relayIo6->setText(QApplication::translate("SettingDlg", "6", 0));
        relayIo7->setText(QApplication::translate("SettingDlg", "7", 0));
        label_15->setText(QApplication::translate("SettingDlg", "\344\270\262\345\217\243\345\217\267:", 0));
        relayConnect->setText(QApplication::translate("SettingDlg", "\350\277\236\346\216\245", 0));
        groupBox_6->setTitle(QApplication::translate("SettingDlg", "\347\224\265\346\272\220", 0));
        label_18->setText(QApplication::translate("SettingDlg", "\347\224\265\346\265\201(A):", 0));
        label_17->setText(QApplication::translate("SettingDlg", "\347\224\265\345\216\213(V):", 0));
        label_16->setText(QApplication::translate("SettingDlg", "\344\270\262\345\217\243\345\217\267:", 0));
        powerOn->setText(QApplication::translate("SettingDlg", "\345\274\200\345\220\257", 0));
        powerConnect->setText(QApplication::translate("SettingDlg", "\350\277\236\346\216\245", 0));
        groupBox_7->setTitle(QApplication::translate("SettingDlg", "\347\224\265\346\265\201\350\241\250", 0));
        label_19->setText(QApplication::translate("SettingDlg", "\347\224\265\346\265\201(\316\274A):", 0));
        label_20->setText(QApplication::translate("SettingDlg", "\344\270\262\345\217\243\345\217\267:", 0));
        currentGetValue->setText(QApplication::translate("SettingDlg", "\350\216\267\345\217\226\347\224\265\346\265\201", 0));
        currentConnect->setText(QApplication::translate("SettingDlg", "\350\277\236\346\216\245", 0));
        groupBox_8->setTitle(QApplication::translate("SettingDlg", "\347\224\265\345\216\213\350\241\250", 0));
        label_21->setText(QApplication::translate("SettingDlg", "\347\224\265\345\216\213(V):", 0));
        label_22->setText(QApplication::translate("SettingDlg", "\344\270\262\345\217\243\345\217\267:", 0));
        voltageGetValue->setText(QApplication::translate("SettingDlg", "\350\216\267\345\217\226\347\224\265\345\216\213", 0));
        voltageConnect->setText(QApplication::translate("SettingDlg", "\350\277\236\346\216\245", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_8), QApplication::translate("SettingDlg", "\347\241\254\344\273\266", 0));
        label_13->setText(QApplication::translate("SettingDlg", "\345\217\213\346\203\205\346\217\220\347\244\272:\346\211\200\347\224\273\345\233\276\345\203\217\351\241\272\345\272\217\344\276\235\346\254\241\344\270\272:\345\211\215\345\220\216\345\267\246\345\217\263,\345\246\202\346\236\234\347\224\273\347\232\204\344\270\215\346\273\241\346\204\217,\351\274\240\346\240\207\345\217\263\351\224\256\346\222\244\351\224\200.", 0));
        label->setText(QString());
        startCapture->setText(QApplication::translate("SettingDlg", "\345\274\200\345\247\213\346\212\223\345\233\276", 0));
        stopCapture->setText(QApplication::translate("SettingDlg", "\345\201\234\346\255\242\346\212\223\345\233\276", 0));
        saveCoord->setText(QApplication::translate("SettingDlg", "\344\277\235\345\255\230\345\235\220\346\240\207", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("SettingDlg", "\347\224\273\345\233\276", 0));
        QTableWidgetItem *___qtablewidgetitem = canTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SettingDlg", "\345\272\217\345\217\267", 0));
        QTableWidgetItem *___qtablewidgetitem1 = canTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SettingDlg", "\344\274\240\350\276\223\346\226\271\345\220\221", 0));
        QTableWidgetItem *___qtablewidgetitem2 = canTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("SettingDlg", "\346\227\266\351\227\264\346\240\207\350\257\206", 0));
        QTableWidgetItem *___qtablewidgetitem3 = canTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("SettingDlg", "\345\270\247ID", 0));
        QTableWidgetItem *___qtablewidgetitem4 = canTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("SettingDlg", "\345\270\247\346\240\274\345\274\217", 0));
        QTableWidgetItem *___qtablewidgetitem5 = canTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("SettingDlg", "\345\270\247\347\261\273\345\236\213", 0));
        QTableWidgetItem *___qtablewidgetitem6 = canTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("SettingDlg", "\346\225\260\346\215\256\351\225\277\345\272\246", 0));
        QTableWidgetItem *___qtablewidgetitem7 = canTable->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("SettingDlg", "\346\225\260\346\215\256(HEX)", 0));
        groupBox->setTitle(QApplication::translate("SettingDlg", "\345\237\272\346\234\254\346\223\215\344\275\234", 0));
        label_2->setText(QApplication::translate("SettingDlg", "\345\270\247\347\261\273\345\236\213:", 0));
        canFrameId->setText(QApplication::translate("SettingDlg", "000", 0));
        canDataEdit->setText(QApplication::translate("SettingDlg", "00 00 00 00 00 00 00 00", 0));
        label_4->setText(QApplication::translate("SettingDlg", "\345\270\247ID(HEX):", 0));
        canFrameType->clear();
        canFrameType->insertItems(0, QStringList()
         << QApplication::translate("SettingDlg", "\346\240\207\345\207\206\345\270\247", 0)
         << QApplication::translate("SettingDlg", "\346\213\223\345\261\225\345\270\247", 0)
        );
        canBaseStop->setText(QApplication::translate("SettingDlg", "\345\201\234\346\255\242", 0));
        label_3->setText(QApplication::translate("SettingDlg", "\345\270\247\346\240\274\345\274\217:", 0));
        canSendDelay->setText(QApplication::translate("SettingDlg", "0", 0));
        label_6->setText(QApplication::translate("SettingDlg", "\346\225\260\346\215\256(HEX):", 0));
        canBaseSend->setText(QApplication::translate("SettingDlg", "\345\217\221\351\200\201", 0));
        canFrameFormat->clear();
        canFrameFormat->insertItems(0, QStringList()
         << QApplication::translate("SettingDlg", "\346\225\260\346\215\256\345\270\247", 0)
         << QApplication::translate("SettingDlg", "\350\277\234\347\250\213\345\270\247", 0)
        );
        canSendCount->setText(QApplication::translate("SettingDlg", "1", 0));
        label_5->setText(QApplication::translate("SettingDlg", "\345\217\221\351\200\201\346\254\241\346\225\260:", 0));
        label_7->setText(QApplication::translate("SettingDlg", "\346\257\217\346\254\241\345\217\221\351\200\201\351\227\264\351\232\224(ms):", 0));
        canStartup->setText(QApplication::translate("SettingDlg", "\345\220\257\345\212\250", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("SettingDlg", "\345\237\272\346\234\254\346\223\215\344\275\234", 0));
        groupBox_2->setTitle(QApplication::translate("SettingDlg", "\351\253\230\347\272\247\346\223\215\344\275\234", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QApplication::translate("SettingDlg", "\345\205\250\351\200\211", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QApplication::translate("SettingDlg", "\345\270\247\347\261\273\345\236\213", 0));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem10->setText(QApplication::translate("SettingDlg", "\345\270\247\346\240\274\345\274\217", 0));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem11->setText(QApplication::translate("SettingDlg", "\345\270\247ID", 0));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem12->setText(QApplication::translate("SettingDlg", "\346\225\260\346\215\256(HEX)", 0));
        label_8->setText(QApplication::translate("SettingDlg", "\345\217\221\351\200\201\346\254\241\346\225\260:", 0));
        label_9->setText(QApplication::translate("SettingDlg", "\346\257\217\346\254\241\345\217\221\351\200\201\351\227\264\351\232\224(ms):", 0));
        label_10->setText(QApplication::translate("SettingDlg", "\346\257\217\345\270\247\345\217\221\351\200\201\351\227\264\351\232\224(ms):", 0));
        advanceSend->setText(QApplication::translate("SettingDlg", "\345\217\221\351\200\201", 0));
        advanceStop->setText(QApplication::translate("SettingDlg", "\345\201\234\346\255\242", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QApplication::translate("SettingDlg", "\351\253\230\347\272\247\346\223\215\344\275\234", 0));
        groupBox_3->setTitle(QApplication::translate("SettingDlg", "\347\241\254\344\273\266\346\223\215\344\275\234", 0));
        checkBox_6->setText(QApplication::translate("SettingDlg", "\350\277\236\346\216\245CAN", 0));
        checkBox->setText(QApplication::translate("SettingDlg", "\347\224\265\346\272\220\344\270\212\347\224\265", 0));
        checkBox_2->setText(QApplication::translate("SettingDlg", "GND", 0));
        checkBox_3->setText(QApplication::translate("SettingDlg", "ACC", 0));
        checkBox_4->setText(QApplication::translate("SettingDlg", "\347\241\254\346\214\211\351\224\256", 0));
        checkBox_5->setText(QApplication::translate("SettingDlg", "\350\275\254\346\216\245\346\235\277", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QApplication::translate("SettingDlg", "\347\241\254\344\273\266\346\223\215\344\275\234", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("SettingDlg", "CAN", 0));
        groupBox_4->setTitle(QApplication::translate("SettingDlg", "\347\211\210\346\234\254\344\277\241\346\201\257", 0));
        label_11->setText(QApplication::translate("SettingDlg", "\346\241\206\346\236\266\347\211\210\346\234\254:", 0));
        frameVersion->setText(QApplication::translate("SettingDlg", "0.0.0.0", 0));
        label_12->setText(QApplication::translate("SettingDlg", "\346\226\207\344\273\266\347\211\210\346\234\254:", 0));
        fileVersion->setText(QApplication::translate("SettingDlg", "0.0.0.0", 0));
        label_14->setText(QApplication::translate("SettingDlg", "\347\250\213\345\272\217\347\211\210\346\234\254:", 0));
        appVersion->setText(QApplication::translate("SettingDlg", "0.0.0.0", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("SettingDlg", "\345\205\263\344\272\216", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingDlg: public Ui_SettingDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDLG_H
