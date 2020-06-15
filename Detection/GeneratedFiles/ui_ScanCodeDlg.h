/********************************************************************************
** Form generated from reading UI file 'ScanCodeDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCANCODEDLG_H
#define UI_SCANCODEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ScanCodeDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLineEdit *codeLine;

    void setupUi(QDialog *ScanCodeDlg)
    {
        if (ScanCodeDlg->objectName().isEmpty())
            ScanCodeDlg->setObjectName(QStringLiteral("ScanCodeDlg"));
        ScanCodeDlg->resize(788, 157);
        ScanCodeDlg->setStyleSheet(QStringLiteral(""));
        verticalLayout_2 = new QVBoxLayout(ScanCodeDlg);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        titleLabel = new QLabel(ScanCodeDlg);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));
        QFont font;
        font.setPointSize(30);
        titleLabel->setFont(font);
        titleLabel->setStyleSheet(QStringLiteral("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255, 0, 0, 255), stop:0.166 rgba(255, 255, 0, 255), stop:0.333 rgba(0, 255, 0, 255), stop:0.5 rgba(0, 255, 255, 255), stop:0.666 rgba(0, 0, 255, 255), stop:0.833 rgba(255, 0, 255, 255), stop:1 rgba(255, 0, 0, 255));"));
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        codeLine = new QLineEdit(ScanCodeDlg);
        codeLine->setObjectName(QStringLiteral("codeLine"));
        codeLine->setMinimumSize(QSize(0, 80));
        QFont font1;
        font1.setPointSize(50);
        codeLine->setFont(font1);
        codeLine->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(codeLine);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ScanCodeDlg);

        QMetaObject::connectSlotsByName(ScanCodeDlg);
    } // setupUi

    void retranslateUi(QDialog *ScanCodeDlg)
    {
        ScanCodeDlg->setWindowTitle(QApplication::translate("ScanCodeDlg", "\346\211\253\347\240\201", 0));
        titleLabel->setText(QApplication::translate("ScanCodeDlg", "\350\257\267\346\211\253\346\235\241\347\240\201", 0));
    } // retranslateUi

};

namespace Ui {
    class ScanCodeDlg: public Ui_ScanCodeDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANCODEDLG_H
