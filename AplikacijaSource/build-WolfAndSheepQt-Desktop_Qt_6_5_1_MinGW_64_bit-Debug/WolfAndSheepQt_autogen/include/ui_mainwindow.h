/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action1600x900;
    QAction *action800x600;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_6;
    QLabel *label_4;
    QLabel *label_7;
    QSpacerItem *verticalSpacer;
    QProgressBar *progressBar;
    QVBoxLayout *optLayout;
    QCheckBox *AlphaBeta;
    QComboBox *comboBox;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton_1;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_7;
    QPushButton *computerVscomputer;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *playAsWolfButton;
    QPushButton *playAsSheepButton;
    QPushButton *ResetGame;
    QMenuBar *menubar;
    QMenu *menuResolution;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(1300, 821);
        MainWindow->setMinimumSize(QSize(1300, 800));
        MainWindow->setMaximumSize(QSize(1300, 821));
        action1600x900 = new QAction(MainWindow);
        action1600x900->setObjectName("action1600x900");
        action1600x900->setCheckable(false);
        action800x600 = new QAction(MainWindow);
        action800x600->setObjectName("action800x600");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(760, 760));
        label->setMaximumSize(QSize(760, 760));
        label->setMouseTracking(true);
        label->setAutoFillBackground(false);
        label->setPixmap(QPixmap(QString::fromUtf8("../../Desktop/board.png")));
        label->setScaledContents(true);

        horizontalLayout->addWidget(label);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        QFont font;
        font.setPointSize(18);
        label_5->setFont(font);

        verticalLayout->addWidget(label_5);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setFont(font);

        verticalLayout->addWidget(label_3);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setFont(font);

        verticalLayout->addWidget(label_6);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setFont(font);

        verticalLayout->addWidget(label_4);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setFont(font);

        verticalLayout->addWidget(label_7);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_4->addLayout(verticalLayout);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setEnabled(true);
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        verticalLayout_4->addWidget(progressBar);

        optLayout = new QVBoxLayout();
        optLayout->setObjectName("optLayout");
        AlphaBeta = new QCheckBox(centralwidget);
        AlphaBeta->setObjectName("AlphaBeta");
        AlphaBeta->setEnabled(true);
        AlphaBeta->setChecked(true);

        optLayout->addWidget(AlphaBeta);

        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName("comboBox");
        comboBox->setEditable(false);

        optLayout->addWidget(comboBox);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        groupBox->setMinimumSize(QSize(0, 100));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        radioButton_1 = new QRadioButton(groupBox);
        radioButton_1->setObjectName("radioButton_1");

        horizontalLayout_2->addWidget(radioButton_1);

        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName("radioButton_2");
        radioButton_2->setChecked(true);

        horizontalLayout_2->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName("radioButton_3");
        radioButton_3->setChecked(false);

        horizontalLayout_2->addWidget(radioButton_3);


        optLayout->addWidget(groupBox);


        verticalLayout_4->addLayout(optLayout);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        computerVscomputer = new QPushButton(centralwidget);
        computerVscomputer->setObjectName("computerVscomputer");

        verticalLayout_7->addWidget(computerVscomputer);


        verticalLayout_6->addLayout(verticalLayout_7);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        playAsWolfButton = new QPushButton(centralwidget);
        playAsWolfButton->setObjectName("playAsWolfButton");
        playAsWolfButton->setEnabled(true);

        horizontalLayout_4->addWidget(playAsWolfButton);

        playAsSheepButton = new QPushButton(centralwidget);
        playAsSheepButton->setObjectName("playAsSheepButton");
        playAsSheepButton->setEnabled(true);

        horizontalLayout_4->addWidget(playAsSheepButton);


        verticalLayout_6->addLayout(horizontalLayout_4);


        verticalLayout_4->addLayout(verticalLayout_6);

        ResetGame = new QPushButton(centralwidget);
        ResetGame->setObjectName("ResetGame");

        verticalLayout_4->addWidget(ResetGame);


        horizontalLayout->addLayout(verticalLayout_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1300, 22));
        menuResolution = new QMenu(menubar);
        menuResolution->setObjectName("menuResolution");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuResolution->menuAction());
        menuResolution->addAction(action1600x900);
        menuResolution->addAction(action800x600);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Wolf and Sheep", nullptr));
        action1600x900->setText(QCoreApplication::translate("MainWindow", "1600x800", nullptr));
        action800x600->setText(QCoreApplication::translate("MainWindow", "800x600", nullptr));
        label->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "Player :", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Time : 0", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Evaluations : 0", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Evaluations per second : 0 ", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Depth : 0", nullptr));
        AlphaBeta->setText(QCoreApplication::translate("MainWindow", "AlphaBeta", nullptr));
        comboBox->setCurrentText(QString());
        comboBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "Depth", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Select Evaluation", nullptr));
        radioButton_1->setText(QCoreApplication::translate("MainWindow", "Simple", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "Fast", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "Smart", nullptr));
        computerVscomputer->setText(QCoreApplication::translate("MainWindow", "ComputerVsComputer", nullptr));
        playAsWolfButton->setText(QCoreApplication::translate("MainWindow", "Play as wolf", nullptr));
        playAsSheepButton->setText(QCoreApplication::translate("MainWindow", "Play as sheep", nullptr));
        ResetGame->setText(QCoreApplication::translate("MainWindow", "Reset game", nullptr));
        menuResolution->setTitle(QCoreApplication::translate("MainWindow", "Resolution", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
