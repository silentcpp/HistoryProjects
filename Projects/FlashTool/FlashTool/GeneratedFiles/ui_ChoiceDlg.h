/********************************************************************************
** Form generated from reading UI file 'ChoiceDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOICEDLG_H
#define UI_CHOICEDLG_H

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

class Ui_ChoiceDlg
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *title;
    QLineEdit *lineEdit;

    void setupUi(QDialog *ChoiceDlg)
    {
        if (ChoiceDlg->objectName().isEmpty())
            ChoiceDlg->setObjectName(QStringLiteral("ChoiceDlg"));
        ChoiceDlg->resize(789, 156);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ChoiceDlg->sizePolicy().hasHeightForWidth());
        ChoiceDlg->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(ChoiceDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        title = new QLabel(ChoiceDlg);
        title->setObjectName(QStringLiteral("title"));
        QFont font;
        font.setPointSize(30);
        title->setFont(font);
        title->setStyleSheet(QStringLiteral("background-image: url(:/Images/Resources/Images/dongman_changjing-006.jpg);"));
        title->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(title);

        lineEdit = new QLineEdit(ChoiceDlg);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);
        lineEdit->setMinimumSize(QSize(0, 80));
        QFont font1;
        font1.setPointSize(50);
        lineEdit->setFont(font1);

        verticalLayout->addWidget(lineEdit);


        retranslateUi(ChoiceDlg);

        QMetaObject::connectSlotsByName(ChoiceDlg);
    } // setupUi

    void retranslateUi(QDialog *ChoiceDlg)
    {
        ChoiceDlg->setWindowTitle(QApplication::translate("ChoiceDlg", "ChoiceDlg", 0));
        title->setText(QApplication::translate("ChoiceDlg", "\350\257\267\346\211\253\346\217\217\351\200\211\346\213\251\346\234\272\347\247\215", 0));
    } // retranslateUi

};

namespace Ui {
    class ChoiceDlg: public Ui_ChoiceDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOICEDLG_H
