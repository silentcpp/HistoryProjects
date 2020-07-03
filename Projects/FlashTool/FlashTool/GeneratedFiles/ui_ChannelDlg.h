/********************************************************************************
** Form generated from reading UI file 'ChannelDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANNELDLG_H
#define UI_CHANNELDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChannelDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *progress;
    QProgressBar *progressBar;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QLabel *currentStatus;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_3;
    QLabel *burnStatus;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLabel *burnTime;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *ChannelDlg)
    {
        if (ChannelDlg->objectName().isEmpty())
            ChannelDlg->setObjectName(QStringLiteral("ChannelDlg"));
        ChannelDlg->resize(791, 91);
        horizontalLayout = new QHBoxLayout(ChannelDlg);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(ChannelDlg);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(10);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        groupBox->setFont(font);
        groupBox->setStyleSheet(QStringLiteral(""));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(25, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        progress = new QLabel(groupBox);
        progress->setObjectName(QStringLiteral("progress"));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        progress->setFont(font1);
        progress->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(progress);

        progressBar = new QProgressBar(groupBox);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy1);
        progressBar->setMinimumSize(QSize(250, 0));
        progressBar->setContextMenuPolicy(Qt::DefaultContextMenu);
        progressBar->setLayoutDirection(Qt::LeftToRight);
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setOrientation(Qt::Horizontal);
        progressBar->setTextDirection(QProgressBar::TopToBottom);

        horizontalLayout_2->addWidget(progressBar);

        horizontalSpacer_2 = new QSpacerItem(25, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        currentStatus = new QLabel(groupBox);
        currentStatus->setObjectName(QStringLiteral("currentStatus"));
        currentStatus->setFont(font1);
        currentStatus->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(currentStatus);

        horizontalSpacer_3 = new QSpacerItem(25, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        burnStatus = new QLabel(groupBox);
        burnStatus->setObjectName(QStringLiteral("burnStatus"));
        sizePolicy1.setHeightForWidth(burnStatus->sizePolicy().hasHeightForWidth());
        burnStatus->setSizePolicy(sizePolicy1);
        burnStatus->setMinimumSize(QSize(40, 40));
        burnStatus->setMaximumSize(QSize(16777215, 40));
        QFont font2;
        font2.setPointSize(20);
        burnStatus->setFont(font2);
        burnStatus->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
""));
        burnStatus->setTextFormat(Qt::RichText);
        burnStatus->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(burnStatus);

        horizontalSpacer = new QSpacerItem(25, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        burnTime = new QLabel(groupBox);
        burnTime->setObjectName(QStringLiteral("burnTime"));

        horizontalLayout_2->addWidget(burnTime);

        horizontalSpacer_6 = new QSpacerItem(25, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        horizontalLayout->addWidget(groupBox);


        retranslateUi(ChannelDlg);

        QMetaObject::connectSlotsByName(ChannelDlg);
    } // setupUi

    void retranslateUi(QWidget *ChannelDlg)
    {
        ChannelDlg->setWindowTitle(QApplication::translate("ChannelDlg", "ChannelDlg", 0));
        groupBox->setTitle(QApplication::translate("ChannelDlg", "\351\200\232\351\201\2231", 0));
        progress->setText(QApplication::translate("ChannelDlg", "\350\277\233\345\272\246:", 0));
        label->setText(QApplication::translate("ChannelDlg", "\345\275\223\345\211\215\347\212\266\346\200\201:", 0));
        currentStatus->setText(QApplication::translate("ChannelDlg", "\345\207\206\345\244\207\346\211\253\347\240\201    ", 0));
        label_3->setText(QApplication::translate("ChannelDlg", "\347\203\247\345\275\225\347\212\266\346\200\201:", 0));
        burnStatus->setText(QApplication::translate("ChannelDlg", "NO", 0));
        label_2->setText(QApplication::translate("ChannelDlg", "\347\224\250\346\227\266:", 0));
        burnTime->setText(QApplication::translate("ChannelDlg", "0 \347\247\222   ", 0));
    } // retranslateUi

};

namespace Ui {
    class ChannelDlg: public Ui_ChannelDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANNELDLG_H
