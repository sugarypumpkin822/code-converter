#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "translator.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include <QDateTime>
#include <QInputDialog>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QClipboard>
#include <QApplication>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Populate language dropdowns
    QStringList languages = {"Python", "JavaScript", "Java", "C#", "PHP", "C", "TypeScript", "Swift", "Kotlin", "Ruby", "C++"};
    ui->sourceLangComboBox->addItems(languages);
    ui->targetLangComboBox->addItems(languages);
    ui->targetLangComboBox->setCurrentText("C++");
    // Connect button
    connect(ui->translateButton, &QPushButton::clicked, this, &MainWindow::on_translateButton_clicked);

    // Status bar
    statusBar()->showMessage("Ready");

    // Menu bar actions
    QMenu *fileMenu = menuBar()->addMenu("&File");
    QAction *saveAction = fileMenu->addAction("Save Output...");
    QAction *loadAction = fileMenu->addAction("Load Input...");
    QAction *exitAction = fileMenu->addAction("Exit");
    QMenu *editMenu = menuBar()->addMenu("&Edit");
    QAction *copyAction = editMenu->addAction("Copy Output");
    QAction *clearAction = editMenu->addAction("Clear All");
    QMenu *toolsMenu = menuBar()->addMenu("&Tools");
    QAction *historyAction = toolsMenu->addAction("Show Translation History");
    QAction *feedbackAction = toolsMenu->addAction("Send Feedback");
    QAction *pluginAction = toolsMenu->addAction("Manage Plugins");
    QMenu *helpMenu = menuBar()->addMenu("&Help");
    QAction *aboutAction = helpMenu->addAction("About");
    QAction *helpAction = helpMenu->addAction("Help");

    // Connect menu actions
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveOutput);
    connect(loadAction, &QAction::triggered, this, &MainWindow::loadInput);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    connect(copyAction, &QAction::triggered, this, &MainWindow::copyOutput);
    connect(clearAction, &QAction::triggered, this, &MainWindow::clearAll);
    connect(historyAction, &QAction::triggered, this, &MainWindow::showHistory);
    connect(feedbackAction, &QAction::triggered, this, &MainWindow::sendFeedback);
    connect(pluginAction, &QAction::triggered, this, &MainWindow::managePlugins);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
    connect(helpAction, &QAction::triggered, this, &MainWindow::showHelp);

    // Load settings
    loadSettings();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::on_translateButton_clicked()
{
    QString sourceLang = ui->sourceLangComboBox->currentText();
    QString targetLang = ui->targetLangComboBox->currentText();
    QString inputCode = ui->inputTextEdit->toPlainText();
    if (inputCode.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Input Required", "Please enter code to translate.");
        return;
    }
    QString outputCode = Translator::translate(sourceLang, targetLang, inputCode);
    ui->outputTextEdit->setPlainText(outputCode);
    statusBar()->showMessage("Translation complete: " + QDateTime::currentDateTime().toString(), 3000);
    // Add to history
    translationHistory.append({sourceLang, targetLang, inputCode, outputCode, QDateTime::currentDateTime()});
}

// Save output code to file
void MainWindow::saveOutput() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Output Code", "output.cpp");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->outputTextEdit->toPlainText();
            file.close();
            statusBar()->showMessage("Output saved to " + fileName, 3000);
        }
    }
}

// Load input code from file
void MainWindow::loadInput() {
    QString fileName = QFileDialog::getOpenFileName(this, "Load Input Code");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            ui->inputTextEdit->setPlainText(in.readAll());
            file.close();
            statusBar()->showMessage("Input loaded from " + fileName, 3000);
        }
    }
}

// Copy output code to clipboard
void MainWindow::copyOutput() {
    QApplication::clipboard()->setText(ui->outputTextEdit->toPlainText());
    statusBar()->showMessage("Output copied to clipboard", 2000);
}

// Clear all fields
void MainWindow::clearAll() {
    ui->inputTextEdit->clear();
    ui->outputTextEdit->clear();
    statusBar()->showMessage("Cleared", 1000);
}

// Show translation history
void MainWindow::showHistory() {
    QString historyText;
    for (const auto& entry : translationHistory) {
        historyText += QString("[%1] %2 → %3\nInput:\n%4\nOutput:\n%5\n\n")
            .arg(entry.timestamp.toString(), entry.sourceLang, entry.targetLang, entry.input, entry.output);
    }
    if (historyText.isEmpty()) historyText = "No translation history.";
    QMessageBox::information(this, "Translation History", historyText);
}

// Send feedback dialog
void MainWindow::sendFeedback() {
    bool ok;
    QString feedback = QInputDialog::getText(this, "Send Feedback", "Your feedback:", QLineEdit::Normal, "", &ok);
    if (ok && !feedback.trimmed().isEmpty()) {
        Translator::submitFeedback(feedback, 5);
        QMessageBox::information(this, "Thank You", "Feedback submitted!");
    }
}

// Manage plugins dialog (simulated)
void MainWindow::managePlugins() {
    QStringList plugins;
    for (const auto& meta : Translator::listPlugins()) {
        plugins << QString("%1 v%2 by %3").arg(meta.name, meta.version, meta.author);
    }
    if (plugins.isEmpty()) plugins << "No plugins loaded.";
    QMessageBox::information(this, "Plugins", plugins.join("\n"));
}

// Show about dialog
void MainWindow::showAbout() {
    QMessageBox::about(this, "About CodeTranslator",
        "<b>CodeTranslator</b><br>Version 2.0.0<br>Advanced code translation toolkit.<br><br>Copyright &copy; 2024 CodeTrans Inc.");
}

// Show help dialog
void MainWindow::showHelp() {
    QMessageBox::information(this, "Help",
        "1. Select source and target languages.<br>"
        "2. Paste or load your code.<br>"
        "3. Click Translate.<br>"
        "4. Save, copy, or review output.<br>"
        "5. Use menu for more features.");
}

// Save settings on close
void MainWindow::saveSettings() {
    QSettings settings("CodeTrans Inc.", "CodeTranslator");
    settings.setValue("sourceLang", ui->sourceLangComboBox->currentText());
    settings.setValue("targetLang", ui->targetLangComboBox->currentText());
}

// Load settings on startup
void MainWindow::loadSettings() {
    QSettings settings("CodeTrans Inc.", "CodeTranslator");
    QString src = settings.value("sourceLang").toString();
    QString tgt = settings.value("targetLang").toString();
    if (!src.isEmpty()) ui->sourceLangComboBox->setCurrentText(src);
    if (!tgt.isEmpty()) ui->targetLangComboBox->setCurrentText(tgt);
}

QList<MainWindow::TranslationEntry> MainWindow::translationHistory; 