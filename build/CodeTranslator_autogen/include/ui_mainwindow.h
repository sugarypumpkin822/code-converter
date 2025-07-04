/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainVerticalLayout;
    QTabWidget *mainTabWidget;
    QWidget *tabTranslation;
    QVBoxLayout *translationVerticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelSource;
    QComboBox *sourceLangComboBox;
    QLabel *labelTarget;
    QComboBox *targetLangComboBox;
    QLabel *labelInput;
    QTextEdit *inputTextEdit;
    QPushButton *translateButton;
    QLabel *labelOutput;
    QTextEdit *outputTextEdit;
    QWidget *tabHistory;
    QVBoxLayout *historyVerticalLayout;
    QListWidget *historyListWidget;
    QPushButton *clearHistoryButton;
    QWidget *tabSettings;
    QFormLayout *settingsFormLayout;
    QLabel *labelTheme;
    QComboBox *themeComboBox;
    QLabel *labelLanguage;
    QComboBox *languageComboBox;
    QLabel *labelPlugins;
    QListWidget *pluginListWidget;
    QLabel *labelFeedback;
    QPushButton *feedbackButton;
    QStatusBar *statusbar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainVerticalLayout = new QVBoxLayout(centralwidget);
        mainVerticalLayout->setObjectName("mainVerticalLayout");
        mainTabWidget = new QTabWidget(centralwidget);
        mainTabWidget->setObjectName("mainTabWidget");
        tabTranslation = new QWidget();
        tabTranslation->setObjectName("tabTranslation");
        translationVerticalLayout = new QVBoxLayout(tabTranslation);
        translationVerticalLayout->setObjectName("translationVerticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        labelSource = new QLabel(tabTranslation);
        labelSource->setObjectName("labelSource");

        horizontalLayout->addWidget(labelSource);

        sourceLangComboBox = new QComboBox(tabTranslation);
        sourceLangComboBox->setObjectName("sourceLangComboBox");

        horizontalLayout->addWidget(sourceLangComboBox);

        labelTarget = new QLabel(tabTranslation);
        labelTarget->setObjectName("labelTarget");

        horizontalLayout->addWidget(labelTarget);

        targetLangComboBox = new QComboBox(tabTranslation);
        targetLangComboBox->setObjectName("targetLangComboBox");

        horizontalLayout->addWidget(targetLangComboBox);


        translationVerticalLayout->addLayout(horizontalLayout);

        labelInput = new QLabel(tabTranslation);
        labelInput->setObjectName("labelInput");

        translationVerticalLayout->addWidget(labelInput);

        inputTextEdit = new QTextEdit(tabTranslation);
        inputTextEdit->setObjectName("inputTextEdit");

        translationVerticalLayout->addWidget(inputTextEdit);

        translateButton = new QPushButton(tabTranslation);
        translateButton->setObjectName("translateButton");

        translationVerticalLayout->addWidget(translateButton);

        labelOutput = new QLabel(tabTranslation);
        labelOutput->setObjectName("labelOutput");

        translationVerticalLayout->addWidget(labelOutput);

        outputTextEdit = new QTextEdit(tabTranslation);
        outputTextEdit->setObjectName("outputTextEdit");

        translationVerticalLayout->addWidget(outputTextEdit);

        mainTabWidget->addTab(tabTranslation, QString());
        tabHistory = new QWidget();
        tabHistory->setObjectName("tabHistory");
        historyVerticalLayout = new QVBoxLayout(tabHistory);
        historyVerticalLayout->setObjectName("historyVerticalLayout");
        historyListWidget = new QListWidget(tabHistory);
        historyListWidget->setObjectName("historyListWidget");

        historyVerticalLayout->addWidget(historyListWidget);

        clearHistoryButton = new QPushButton(tabHistory);
        clearHistoryButton->setObjectName("clearHistoryButton");

        historyVerticalLayout->addWidget(clearHistoryButton);

        mainTabWidget->addTab(tabHistory, QString());
        tabSettings = new QWidget();
        tabSettings->setObjectName("tabSettings");
        settingsFormLayout = new QFormLayout(tabSettings);
        settingsFormLayout->setObjectName("settingsFormLayout");
        labelTheme = new QLabel(tabSettings);
        labelTheme->setObjectName("labelTheme");

        settingsFormLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelTheme);

        themeComboBox = new QComboBox(tabSettings);
        themeComboBox->setObjectName("themeComboBox");

        settingsFormLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, themeComboBox);

        labelLanguage = new QLabel(tabSettings);
        labelLanguage->setObjectName("labelLanguage");

        settingsFormLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelLanguage);

        languageComboBox = new QComboBox(tabSettings);
        languageComboBox->setObjectName("languageComboBox");

        settingsFormLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, languageComboBox);

        labelPlugins = new QLabel(tabSettings);
        labelPlugins->setObjectName("labelPlugins");

        settingsFormLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, labelPlugins);

        pluginListWidget = new QListWidget(tabSettings);
        pluginListWidget->setObjectName("pluginListWidget");

        settingsFormLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, pluginListWidget);

        labelFeedback = new QLabel(tabSettings);
        labelFeedback->setObjectName("labelFeedback");

        settingsFormLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, labelFeedback);

        feedbackButton = new QPushButton(tabSettings);
        feedbackButton->setObjectName("feedbackButton");

        settingsFormLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, feedbackButton);

        mainTabWidget->addTab(tabSettings, QString());

        mainVerticalLayout->addWidget(mainTabWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(mainToolBar);

        retranslateUi(MainWindow);

        mainTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Code Translator", nullptr));
        labelSource->setText(QCoreApplication::translate("MainWindow", "Source Language:", nullptr));
        labelTarget->setText(QCoreApplication::translate("MainWindow", "Target Language:", nullptr));
        labelInput->setText(QCoreApplication::translate("MainWindow", "Input Code:", nullptr));
        translateButton->setText(QCoreApplication::translate("MainWindow", "Translate", nullptr));
        labelOutput->setText(QCoreApplication::translate("MainWindow", "Output Code:", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(tabTranslation), QCoreApplication::translate("MainWindow", "Translation", nullptr));
        clearHistoryButton->setText(QCoreApplication::translate("MainWindow", "Clear History", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(tabHistory), QCoreApplication::translate("MainWindow", "History", nullptr));
        labelTheme->setText(QCoreApplication::translate("MainWindow", "Theme:", nullptr));
        labelLanguage->setText(QCoreApplication::translate("MainWindow", "Language:", nullptr));
        labelPlugins->setText(QCoreApplication::translate("MainWindow", "Plugins:", nullptr));
        labelFeedback->setText(QCoreApplication::translate("MainWindow", "Feedback:", nullptr));
        feedbackButton->setText(QCoreApplication::translate("MainWindow", "Send Feedback", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(tabSettings), QCoreApplication::translate("MainWindow", "Settings", nullptr));
        mainToolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "Toolbar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
