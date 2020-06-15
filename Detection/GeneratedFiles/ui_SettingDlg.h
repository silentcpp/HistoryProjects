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
    QComboBox *canFrameType;
    QLabel *label_4;
    QLineEdit *canDataEdit;
    QLabel *label_6;
    QLabel *label_3;
    QPushButton *canBaseSend;
    QComboBox *canFrameFormat;
    QLineEdit *canSendDelay;
    QPushButton *canBaseStop;
    QLineEdit *canSendCount;
    QLabel *label_7;
    QLabel *label_5;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
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
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_4;
    QLabelEx *label;

    void setupUi(QWidget *SettingDlg)
    {
        if (SettingDlg->objectName().isEmpty())
            SettingDlg->setObjectName(QStringLiteral("SettingDlg"));
        SettingDlg->resize(895, 648);
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
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setAutoFillBackground(false);
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        canFrameId = new QLineEdit(groupBox);
        canFrameId->setObjectName(QStringLiteral("canFrameId"));

        gridLayout->addWidget(canFrameId, 0, 3, 1, 1);

        canFrameType = new QComboBox(groupBox);
        canFrameType->setObjectName(QStringLiteral("canFrameType"));

        gridLayout->addWidget(canFrameType, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 0, 2, 1, 1);

        canDataEdit = new QLineEdit(groupBox);
        canDataEdit->setObjectName(QStringLiteral("canDataEdit"));

        gridLayout->addWidget(canDataEdit, 0, 5, 1, 2);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 0, 4, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        canBaseSend = new QPushButton(groupBox);
        canBaseSend->setObjectName(QStringLiteral("canBaseSend"));
        canBaseSend->setIcon(icon3);

        gridLayout->addWidget(canBaseSend, 0, 7, 1, 1);

        canFrameFormat = new QComboBox(groupBox);
        canFrameFormat->setObjectName(QStringLiteral("canFrameFormat"));

        gridLayout->addWidget(canFrameFormat, 1, 1, 1, 1);

        canSendDelay = new QLineEdit(groupBox);
        canSendDelay->setObjectName(QStringLiteral("canSendDelay"));

        gridLayout->addWidget(canSendDelay, 1, 6, 1, 1);

        canBaseStop = new QPushButton(groupBox);
        canBaseStop->setObjectName(QStringLiteral("canBaseStop"));
        canBaseStop->setIcon(icon2);

        gridLayout->addWidget(canBaseStop, 1, 7, 1, 1);

        canSendCount = new QLineEdit(groupBox);
        canSendCount->setObjectName(QStringLiteral("canSendCount"));

        gridLayout->addWidget(canSendCount, 1, 3, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 1, 4, 1, 2);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 1, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 2, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 8, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 8, 1, 1);


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
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(100);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy2);

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
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayout_4 = new QVBoxLayout(tab_3);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label = new QLabelEx(tab_3);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);
        label->setMinimumSize(QSize(720, 480));
        label->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));

        verticalLayout_4->addWidget(label);

        tabWidget->addTab(tab_3, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(SettingDlg);

        tabWidget->setCurrentIndex(1);
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
        canFrameType->clear();
        canFrameType->insertItems(0, QStringList()
         << QApplication::translate("SettingDlg", "\346\240\207\345\207\206\345\270\247", 0)
         << QApplication::translate("SettingDlg", "\346\213\223\345\261\225\345\270\247", 0)
        );
        label_4->setText(QApplication::translate("SettingDlg", "\345\270\247ID(HEX):", 0));
        canDataEdit->setText(QApplication::translate("SettingDlg", "00 00 00 00 00 00 00 00", 0));
        label_6->setText(QApplication::translate("SettingDlg", "\346\225\260\346\215\256(HEX):", 0));
        label_3->setText(QApplication::translate("SettingDlg", "\345\270\247\346\240\274\345\274\217:", 0));
        canBaseSend->setText(QApplication::translate("SettingDlg", "\345\217\221\351\200\201", 0));
        canFrameFormat->clear();
        canFrameFormat->insertItems(0, QStringList()
         << QApplication::translate("SettingDlg", "\346\225\260\346\215\256\345\270\247", 0)
         << QApplication::translate("SettingDlg", "\350\277\234\347\250\213\345\270\247", 0)
        );
        canSendDelay->setText(QApplication::translate("SettingDlg", "0", 0));
        canBaseStop->setText(QApplication::translate("SettingDlg", "\345\201\234\346\255\242", 0));
        canSendCount->setText(QApplication::translate("SettingDlg", "1", 0));
        label_7->setText(QApplication::translate("SettingDlg", "\346\257\217\346\254\241\345\217\221\351\200\201\351\227\264\351\232\224(ms):", 0));
        label_5->setText(QApplication::translate("SettingDlg", "\345\217\221\351\200\201\346\254\241\346\225\260:", 0));
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
        label->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("SettingDlg", "\347\224\273\345\233\276", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingDlg: public Ui_SettingDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDLG_H
