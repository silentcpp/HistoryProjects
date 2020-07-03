/********************************************************************************
** Form generated from reading UI file 'SettingDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDLG_H
#define UI_SETTINGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingDlg
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *expandAll;
    QPushButton *addNode;
    QPushButton *deleteNode;
    QPushButton *saveData;
    QPushButton *exit;

    void setupUi(QWidget *SettingDlg)
    {
        if (SettingDlg->objectName().isEmpty())
            SettingDlg->setObjectName(QStringLiteral("SettingDlg"));
        SettingDlg->resize(786, 538);
        verticalLayout_3 = new QVBoxLayout(SettingDlg);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox = new QGroupBox(SettingDlg);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        treeWidget = new QTreeWidget(groupBox);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("\351\224\256"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        verticalLayout_2->addWidget(treeWidget);


        verticalLayout_3->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        expandAll = new QPushButton(SettingDlg);
        expandAll->setObjectName(QStringLiteral("expandAll"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Images/Resources/Images/expand.ico"), QSize(), QIcon::Normal, QIcon::Off);
        expandAll->setIcon(icon);

        horizontalLayout->addWidget(expandAll);

        addNode = new QPushButton(SettingDlg);
        addNode->setObjectName(QStringLiteral("addNode"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Images/Resources/Images/add.ico"), QSize(), QIcon::Normal, QIcon::Off);
        addNode->setIcon(icon1);

        horizontalLayout->addWidget(addNode);

        deleteNode = new QPushButton(SettingDlg);
        deleteNode->setObjectName(QStringLiteral("deleteNode"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Images/Resources/Images/del.ico"), QSize(), QIcon::Normal, QIcon::Off);
        deleteNode->setIcon(icon2);

        horizontalLayout->addWidget(deleteNode);

        saveData = new QPushButton(SettingDlg);
        saveData->setObjectName(QStringLiteral("saveData"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Images/Resources/Images/save.ico"), QSize(), QIcon::Normal, QIcon::Off);
        saveData->setIcon(icon3);

        horizontalLayout->addWidget(saveData);

        exit = new QPushButton(SettingDlg);
        exit->setObjectName(QStringLiteral("exit"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Images/Resources/Images/treeExit.ico"), QSize(), QIcon::Normal, QIcon::Off);
        exit->setIcon(icon4);

        horizontalLayout->addWidget(exit);


        verticalLayout_3->addLayout(horizontalLayout);


        retranslateUi(SettingDlg);

        QMetaObject::connectSlotsByName(SettingDlg);
    } // setupUi

    void retranslateUi(QWidget *SettingDlg)
    {
        SettingDlg->setWindowTitle(QApplication::translate("SettingDlg", "\351\205\215\347\275\256\344\277\241\346\201\257", 0));
        groupBox->setTitle(QApplication::translate("SettingDlg", "\345\275\223\345\211\215\351\205\215\347\275\256", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("SettingDlg", "\350\257\264\346\230\216", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("SettingDlg", "\345\200\274", 0));
        expandAll->setText(QApplication::translate("SettingDlg", "\345\205\250\351\203\250\345\261\225\345\274\200", 0));
        addNode->setText(QApplication::translate("SettingDlg", "\346\267\273\345\212\240\346\226\207\344\273\266\350\212\202\347\202\271", 0));
        deleteNode->setText(QApplication::translate("SettingDlg", "\345\210\240\351\231\244\346\226\207\344\273\266\350\212\202\347\202\271", 0));
        saveData->setText(QApplication::translate("SettingDlg", "\344\277\235\345\255\230\346\225\260\346\215\256", 0));
        exit->setText(QApplication::translate("SettingDlg", "\351\200\200\345\207\272", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingDlg: public Ui_SettingDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDLG_H
