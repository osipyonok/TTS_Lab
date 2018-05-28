/********************************************************************************
** Form generated from reading UI file 'TTS_Lab.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TTS_LAB_H
#define UI_TTS_LAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TTS_LabClass
{
public:
    QWidget *centralWidget;
    QTextEdit *textField;
    QSlider *volumeSlider;
    QPushButton *runTTSButton;
    QLabel *volumeLabel;
    QPushButton *stopPlayingButton;
    QLabel *volumeTextLabel;
    QPushButton *exitButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TTS_LabClass)
    {
        if (TTS_LabClass->objectName().isEmpty())
            TTS_LabClass->setObjectName(QStringLiteral("TTS_LabClass"));
        TTS_LabClass->resize(700, 260);
        centralWidget = new QWidget(TTS_LabClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textField = new QTextEdit(centralWidget);
        textField->setObjectName(QStringLiteral("textField"));
        textField->setGeometry(QRect(10, 10, 671, 171));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(12);
        textField->setFont(font);
        volumeSlider = new QSlider(centralWidget);
        volumeSlider->setObjectName(QStringLiteral("volumeSlider"));
        volumeSlider->setGeometry(QRect(116, 201, 160, 22));
        volumeSlider->setMaximum(200);
        volumeSlider->setValue(50);
        volumeSlider->setOrientation(Qt::Horizontal);
        runTTSButton = new QPushButton(centralWidget);
        runTTSButton->setObjectName(QStringLiteral("runTTSButton"));
        runTTSButton->setGeometry(QRect(310, 190, 111, 41));
        QFont font1;
        font1.setPointSize(11);
        runTTSButton->setFont(font1);
        volumeLabel = new QLabel(centralWidget);
        volumeLabel->setObjectName(QStringLiteral("volumeLabel"));
        volumeLabel->setGeometry(QRect(89, 202, 55, 16));
        QFont font2;
        font2.setPointSize(10);
        volumeLabel->setFont(font2);
        stopPlayingButton = new QPushButton(centralWidget);
        stopPlayingButton->setObjectName(QStringLiteral("stopPlayingButton"));
        stopPlayingButton->setGeometry(QRect(440, 190, 111, 41));
        stopPlayingButton->setFont(font1);
        volumeTextLabel = new QLabel(centralWidget);
        volumeTextLabel->setObjectName(QStringLiteral("volumeTextLabel"));
        volumeTextLabel->setGeometry(QRect(10, 200, 71, 21));
        volumeTextLabel->setFont(font2);
        exitButton = new QPushButton(centralWidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(570, 190, 111, 41));
        exitButton->setFont(font1);
        TTS_LabClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TTS_LabClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 700, 26));
        TTS_LabClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TTS_LabClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TTS_LabClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TTS_LabClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TTS_LabClass->setStatusBar(statusBar);

        retranslateUi(TTS_LabClass);

        QMetaObject::connectSlotsByName(TTS_LabClass);
    } // setupUi

    void retranslateUi(QMainWindow *TTS_LabClass)
    {
        TTS_LabClass->setWindowTitle(QApplication::translate("TTS_LabClass", "TTS Lab by Max Osipyonok", nullptr));
        textField->setPlaceholderText(QApplication::translate("TTS_LabClass", "\320\242\320\265\320\272\321\201\321\202", nullptr));
        runTTSButton->setText(QApplication::translate("TTS_LabClass", "\320\236\320\267\320\262\321\203\321\207\320\270\321\202\320\270", nullptr));
        volumeLabel->setText(QApplication::translate("TTS_LabClass", "50", nullptr));
        stopPlayingButton->setText(QApplication::translate("TTS_LabClass", "\320\227\321\203\320\277\320\270\320\275\320\270\321\202\320\270", nullptr));
        volumeTextLabel->setText(QApplication::translate("TTS_LabClass", "\320\223\321\203\321\207\320\275\321\226\321\201\321\202\321\214:", nullptr));
        exitButton->setText(QApplication::translate("TTS_LabClass", "\320\222\320\270\321\205\321\226\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TTS_LabClass: public Ui_TTS_LabClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TTS_LAB_H
