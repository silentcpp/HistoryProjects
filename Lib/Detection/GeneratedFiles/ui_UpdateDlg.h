/********************************************************************************
** Form generated from reading UI file 'UpdateDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEDLG_H
#define UI_UPDATEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UpdateDlg
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QHBoxLayout *horizontalLayout;
    QProgressBar *progressBar;
    QPushButton *abortButton;

    void setupUi(QDialog *UpdateDlg)
    {
        if (UpdateDlg->objectName().isEmpty())
            UpdateDlg->setObjectName(QStringLiteral("UpdateDlg"));
        UpdateDlg->resize(536, 92);
        verticalLayout = new QVBoxLayout(UpdateDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        titleLabel = new QLabel(UpdateDlg);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));
        QFont font;
        font.setPointSize(30);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        progressBar = new QProgressBar(UpdateDlg);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(progressBar);

        abortButton = new QPushButton(UpdateDlg);
        abortButton->setObjectName(QStringLiteral("abortButton"));

        horizontalLayout->addWidget(abortButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(UpdateDlg);

        QMetaObject::connectSlotsByName(UpdateDlg);
    } // setupUi

    void retranslateUi(QDialog *UpdateDlg)
    {
        UpdateDlg->setWindowTitle(QApplication::translate("UpdateDlg", "UpdateDlg", 0));
        titleLabel->setText(QApplication::translate("UpdateDlg", "\346\255\243\345\234\250\346\233\264\346\226\260\344\270\255", 0));
        abortButton->setText(QApplication::translate("UpdateDlg", "\347\273\210\346\255\242", 0));
    } // retranslateUi

};

namespace Ui {
    class UpdateDlg: public Ui_UpdateDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEDLG_H
