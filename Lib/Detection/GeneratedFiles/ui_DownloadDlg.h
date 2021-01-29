/********************************************************************************
** Form generated from reading UI file 'DownloadDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADDLG_H
#define UI_DOWNLOADDLG_H

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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DownloadDlg
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLabel *sizeLabel;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *urlLabel;
    QLabel *speedLabel;
    QHBoxLayout *horizontalLayout;
    QProgressBar *progressBar;
    QPushButton *abortBtn;

    void setupUi(QDialog *DownloadDlg)
    {
        if (DownloadDlg->objectName().isEmpty())
            DownloadDlg->setObjectName(QStringLiteral("DownloadDlg"));
        DownloadDlg->resize(492, 124);
        verticalLayout = new QVBoxLayout(DownloadDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        titleLabel = new QLabel(DownloadDlg);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font.setPointSize(20);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(DownloadDlg);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        sizeLabel = new QLabel(DownloadDlg);
        sizeLabel->setObjectName(QStringLiteral("sizeLabel"));

        horizontalLayout_3->addWidget(sizeLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        urlLabel = new QLabel(DownloadDlg);
        urlLabel->setObjectName(QStringLiteral("urlLabel"));

        horizontalLayout_2->addWidget(urlLabel);

        speedLabel = new QLabel(DownloadDlg);
        speedLabel->setObjectName(QStringLiteral("speedLabel"));
        speedLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(speedLabel);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        progressBar = new QProgressBar(DownloadDlg);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setTextDirection(QProgressBar::TopToBottom);

        horizontalLayout->addWidget(progressBar);

        abortBtn = new QPushButton(DownloadDlg);
        abortBtn->setObjectName(QStringLiteral("abortBtn"));

        horizontalLayout->addWidget(abortBtn);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DownloadDlg);

        QMetaObject::connectSlotsByName(DownloadDlg);
    } // setupUi

    void retranslateUi(QDialog *DownloadDlg)
    {
        DownloadDlg->setWindowTitle(QApplication::translate("DownloadDlg", "DownloadDlg", 0));
        titleLabel->setText(QApplication::translate("DownloadDlg", "\346\255\243\345\234\250\344\270\213\350\275\275\346\233\264\346\226\260\347\250\213\345\272\217", 0));
        label->setText(QApplication::translate("DownloadDlg", "\346\226\207\344\273\266\345\244\247\345\260\217/\345\267\262\344\270\213\350\275\275:", 0));
        sizeLabel->setText(QApplication::translate("DownloadDlg", "00.00MB/00.00MB", 0));
        urlLabel->setText(QApplication::translate("DownloadDlg", "http://download.osgeo.org/libtiff/old/tiff-3.7.0beta.zip", 0));
        speedLabel->setText(QApplication::translate("DownloadDlg", "0.00Mb/s", 0));
        abortBtn->setText(QApplication::translate("DownloadDlg", "\347\273\210\346\255\242", 0));
    } // retranslateUi

};

namespace Ui {
    class DownloadDlg: public Ui_DownloadDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADDLG_H
