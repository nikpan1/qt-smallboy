/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QSplitter *splitter;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QSpinBox *PlayerAmountW;
    QComboBox *PlayerTypeW;
    QLabel *log;
    QLabel *label;
    QPushButton *AddNewPlayerW;
    QLabel *label_2;
    QRadioButton *isHost;
    QLineEdit *IPaddressW;
    QLineEdit *PortW;
    QLabel *label_5;
    QLabel *label_6;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QFrame *line_2;
    QPushButton *StartGameW;
    QLabel *roundNumLabelW;
    QLabel *label_3;
    QPushButton *PlayRoundW;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_5;
    QScrollArea *playerList;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(820, 870);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setEnabled(true);
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        gridLayoutWidget = new QWidget(splitter);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        PlayerAmountW = new QSpinBox(gridLayoutWidget);
        PlayerAmountW->setObjectName(QString::fromUtf8("PlayerAmountW"));
        PlayerAmountW->setMinimum(1);

        gridLayout->addWidget(PlayerAmountW, 1, 0, 1, 1);

        PlayerTypeW = new QComboBox(gridLayoutWidget);
        PlayerTypeW->setObjectName(QString::fromUtf8("PlayerTypeW"));

        gridLayout->addWidget(PlayerTypeW, 1, 1, 1, 1);

        log = new QLabel(gridLayoutWidget);
        log->setObjectName(QString::fromUtf8("log"));

        gridLayout->addWidget(log, 0, 2, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setLineWidth(1);
        label->setTextFormat(Qt::PlainText);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        AddNewPlayerW = new QPushButton(gridLayoutWidget);
        AddNewPlayerW->setObjectName(QString::fromUtf8("AddNewPlayerW"));

        gridLayout->addWidget(AddNewPlayerW, 1, 2, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        isHost = new QRadioButton(gridLayoutWidget);
        isHost->setObjectName(QString::fromUtf8("isHost"));

        gridLayout->addWidget(isHost, 3, 0, 1, 1);

        IPaddressW = new QLineEdit(gridLayoutWidget);
        IPaddressW->setObjectName(QString::fromUtf8("IPaddressW"));
        sizePolicy.setHeightForWidth(IPaddressW->sizePolicy().hasHeightForWidth());
        IPaddressW->setSizePolicy(sizePolicy);

        gridLayout->addWidget(IPaddressW, 3, 1, 1, 1);

        PortW = new QLineEdit(gridLayoutWidget);
        PortW->setObjectName(QString::fromUtf8("PortW"));
        sizePolicy.setHeightForWidth(PortW->sizePolicy().hasHeightForWidth());
        PortW->setSizePolicy(sizePolicy);

        gridLayout->addWidget(PortW, 3, 2, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 1, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 2, 2, 1, 1);

        splitter->addWidget(gridLayoutWidget);
        gridLayoutWidget_2 = new QWidget(splitter);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        line_2 = new QFrame(gridLayoutWidget_2);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_2, 10, 0, 1, 1);

        StartGameW = new QPushButton(gridLayoutWidget_2);
        StartGameW->setObjectName(QString::fromUtf8("StartGameW"));

        gridLayout_2->addWidget(StartGameW, 5, 0, 1, 1);

        roundNumLabelW = new QLabel(gridLayoutWidget_2);
        roundNumLabelW->setObjectName(QString::fromUtf8("roundNumLabelW"));
        sizePolicy.setHeightForWidth(roundNumLabelW->sizePolicy().hasHeightForWidth());
        roundNumLabelW->setSizePolicy(sizePolicy);
        roundNumLabelW->setAutoFillBackground(false);
        roundNumLabelW->setTextFormat(Qt::PlainText);
        roundNumLabelW->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        gridLayout_2->addWidget(roundNumLabelW, 8, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout_2->addWidget(label_3, 9, 0, 1, 1);

        PlayRoundW = new QPushButton(gridLayoutWidget_2);
        PlayRoundW->setObjectName(QString::fromUtf8("PlayRoundW"));

        gridLayout_2->addWidget(PlayRoundW, 6, 0, 1, 1);

        splitter->addWidget(gridLayoutWidget_2);
        verticalLayoutWidget = new QWidget(splitter);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        playerList = new QScrollArea(verticalLayoutWidget);
        playerList->setObjectName(QString::fromUtf8("playerList"));
        playerList->setMinimumSize(QSize(0, 450));
        playerList->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 798, 18));
        sizePolicy.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        playerList->setWidget(scrollAreaWidgetContents);

        verticalLayout_5->addWidget(playerList);

        splitter->addWidget(verticalLayoutWidget);

        gridLayout_3->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setProperty("maly-dresiarz", QVariant(QCoreApplication::translate("MainWindow", "Hello, World!", nullptr)));
        actionExit->setText(QCoreApplication::translate("MainWindow", "E&xit", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Server Settings", nullptr));
        log->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Add new Players", nullptr));
        AddNewPlayerW->setText(QCoreApplication::translate("MainWindow", "Add New Player", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "LOG:", nullptr));
        isHost->setText(QCoreApplication::translate("MainWindow", "isHost", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Server IP address:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Server Port:", nullptr));
        StartGameW->setText(QCoreApplication::translate("MainWindow", "Start Game", nullptr));
        roundNumLabelW->setText(QCoreApplication::translate("MainWindow", "ROUND: 1", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Players", nullptr));
        PlayRoundW->setText(QCoreApplication::translate("MainWindow", "Play Round", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
