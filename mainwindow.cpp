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
#include <QFontDialog>
#include <QColorDialog>
#include <QTimer>
#include <QProgressDialog>
#include <QDir>
#include <QProcess>
#include <QDesktopServices>
#include <QUrl>
#include <QSplitter>
#include <QPlainTextEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QShortcut>
#include <QTabWidget>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QRandomGenerator>
#include <QDockWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , autoSaveTimer(nullptr)
{
    ui->setupUi(this);

    // More languages
    QStringList languages = {
        "Python", "JavaScript", "Java", "C#", "PHP", "C", "TypeScript", "Swift", "Kotlin", "Ruby", "C++",
        "Go", "Rust", "Scala", "Perl", "R", "Haskell", "Lua", "Objective-C", "Dart", "MATLAB", "Visual Basic", "Assembly"
    };
    ui->sourceLangComboBox->addItems(languages);
    ui->targetLangComboBox->addItems(languages);
    ui->targetLangComboBox->setCurrentText("C++");

    // Splitter: allow resizing between input/output
    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(ui->inputTextEdit);
    splitter->addWidget(ui->outputTextEdit);
    setCentralWidget(splitter);

    // Tabs for future expansion (history, stats, plugins, etc)
    QTabWidget *mainTabs = new QTabWidget(this);
    mainTabs->addTab(splitter, "Translate");
    QWidget *historyTab = new QWidget();
    mainTabs->addTab(historyTab, "History");
    QWidget *statsTab = new QWidget();
    mainTabs->addTab(statsTab, "Stats");
    QWidget *pluginTab = new QWidget();
    mainTabs->addTab(pluginTab, "Plugins");
    setCentralWidget(mainTabs);

    // History Table
    QTableWidget *historyTable = new QTableWidget(historyTab);
    historyTable->setColumnCount(5);
    historyTable->setHorizontalHeaderLabels(
        QStringList() << "Source" << "Target" << "Input" << "Output" << "Timestamp"
    );
    QVBoxLayout *historyLayout = new QVBoxLayout(historyTab);
    historyLayout->addWidget(historyTable);

    // Stats area
    QLabel *statsLabel = new QLabel(statsTab);
    QVBoxLayout *statsLayout = new QVBoxLayout(statsTab);
    statsLayout->addWidget(statsLabel);

    // Plugins area
    QListWidget *pluginList = new QListWidget(pluginTab);
    QVBoxLayout *pluginLayout = new QVBoxLayout(pluginTab);
    pluginLayout->addWidget(pluginList);

    // Status bar
    statusBar()->showMessage("Ready");

    // Menu bar
    QMenu *fileMenu = menuBar()->addMenu("&File");
    QAction *saveAction = fileMenu->addAction("Save Output...");
    QAction *loadAction = fileMenu->addAction("Load Input...");
    QAction *exportHistoryAction = fileMenu->addAction("Export History...");
    QAction *importHistoryAction = fileMenu->addAction("Import History...");
    QAction *exitAction = fileMenu->addAction("Exit");
    QMenu *editMenu = menuBar()->addMenu("&Edit");
    QAction *copyAction = editMenu->addAction("Copy Output");
    QAction *clearAction = editMenu->addAction("Clear All");
    QAction *fontAction = editMenu->addAction("Set Font...");
    QAction *colorAction = editMenu->addAction("Set Theme Color...");
    QMenu *toolsMenu = menuBar()->addMenu("&Tools");
    QAction *historyAction = toolsMenu->addAction("Show Translation History");
    QAction *feedbackAction = toolsMenu->addAction("Send Feedback");
    QAction *pluginAction = toolsMenu->addAction("Manage Plugins");
    QAction *statsAction = toolsMenu->addAction("Show Stats");
    QAction *openOutputDirAction = toolsMenu->addAction("Open Output Directory");
    QAction *randomTipAction = toolsMenu->addAction("Show Random Tip");
    QMenu *helpMenu = menuBar()->addMenu("&Help");
    QAction *aboutAction = helpMenu->addAction("About");
    QAction *helpAction = helpMenu->addAction("Help");
    QAction *reportBugAction = helpMenu->addAction("Report Bug");

    // Connect menu actions
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveOutput);
    connect(loadAction, &QAction::triggered, this, &MainWindow::loadInput);
    connect(exportHistoryAction, &QAction::triggered, this, &MainWindow::exportHistory);
    connect(importHistoryAction, &QAction::triggered, this, &MainWindow::importHistory);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    connect(copyAction, &QAction::triggered, this, &MainWindow::copyOutput);
    connect(clearAction, &QAction::triggered, this, &MainWindow::clearAll);
    connect(fontAction, &QAction::triggered, this, &MainWindow::setFont);
    connect(colorAction, &QAction::triggered, this, &MainWindow::setThemeColor);
    connect(historyAction, &QAction::triggered, this, &MainWindow::showHistory);
    connect(feedbackAction, &QAction::triggered, this, &MainWindow::sendFeedback);
    connect(pluginAction, &QAction::triggered, this, &MainWindow::managePlugins);
    connect(statsAction, &QAction::triggered, this, &MainWindow::showStats);
    connect(openOutputDirAction, &QAction::triggered, this, &MainWindow::openOutputDirectory);
    connect(randomTipAction, &QAction::triggered, this, &MainWindow::showRandomTip);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
    connect(helpAction, &QAction::triggered, this, &MainWindow::showHelp);
    connect(reportBugAction, &QAction::triggered, this, &MainWindow::reportBug);

    // Connect translate button
    connect(ui->translateButton, &QPushButton::clicked, this, &MainWindow::on_translateButton_clicked);

    // Keyboard shortcuts
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(saveOutput()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_C), this, SLOT(copyOutput()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_L), this, SLOT(loadInput()));

    // Timer for auto-save
    autoSaveTimer = new QTimer(this);
    connect(autoSaveTimer, &QTimer::timeout, this, &MainWindow::autoSave);
    autoSaveTimer->start(60000); // Every 60 seconds

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
    QProgressDialog dlg("Translating...", "Cancel", 0, 0, this);
    dlg.setWindowModality(Qt::WindowModal);
    dlg.show();
    QApplication::processEvents();

    QString outputCode = Translator::translate(sourceLang, targetLang, inputCode);

    dlg.close();
    ui->outputTextEdit->setPlainText(outputCode);
    statusBar()->showMessage("Translation complete: " + QDateTime::currentDateTime().toString(), 3000);
    translationHistory.append({sourceLang, targetLang, inputCode, outputCode, QDateTime::currentDateTime()});
}

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

void MainWindow::exportHistory() {
    QString fileName = QFileDialog::getSaveFileName(this, "Export Translation History", "translation_history.txt");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (const auto& entry : translationHistory) {
                out << "[" << entry.timestamp.toString() << "] " << entry.sourceLang << " → " << entry.targetLang << "\n";
                out << "Input:\n" << entry.input << "\n";
                out << "Output:\n" << entry.output << "\n\n";
            }
            file.close();
            statusBar()->showMessage("History exported to " + fileName, 3000);
        }
    }
}

void MainWindow::importHistory() {
    QString fileName = QFileDialog::getOpenFileName(this, "Import Translation History");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString content = in.readAll();
            translationHistory.append({"Imported", "Imported", content, "", QDateTime::currentDateTime()});
            file.close();
            statusBar()->showMessage("History imported from " + fileName, 3000);
        }
    }
}

void MainWindow::copyOutput() {
    QApplication::clipboard()->setText(ui->outputTextEdit->toPlainText());
    statusBar()->showMessage("Output copied to clipboard", 2000);
}

void MainWindow::clearAll() {
    ui->inputTextEdit->clear();
    ui->outputTextEdit->clear();
    statusBar()->showMessage("Cleared", 1000);
}

void MainWindow::showHistory() {
    QString historyText;
    for (const auto& entry : translationHistory) {
        historyText += QString("[%1] %2 → %3\nInput:\n%4\nOutput:\n%5\n\n")
            .arg(entry.timestamp.toString(), entry.sourceLang, entry.targetLang, entry.input, entry.output);
    }
    if (historyText.isEmpty()) historyText = "No translation history.";
    QMessageBox::information(this, "Translation History", historyText);
}

void MainWindow::showStats() {
    int total = translationHistory.size();
    QMap<QString, int> srcCount, tgtCount;
    for (const auto& entry : translationHistory) {
        srcCount[entry.sourceLang]++;
        tgtCount[entry.targetLang]++;
    }
    QString stats = QString("Total translations: %1\n\n").arg(total);
    stats += "Source Language Usage:\n";
    for (auto it = srcCount.begin(); it != srcCount.end(); ++it)
        stats += QString("%1: %2\n").arg(it.key()).arg(it.value());
    stats += "\nTarget Language Usage:\n";
    for (auto it = tgtCount.begin(); it != tgtCount.end(); ++it)
        stats += QString("%1: %2\n").arg(it.key()).arg(it.value());
    QMessageBox::information(this, "Translation Stats", stats);
}

void MainWindow::sendFeedback() {
    bool ok;
    QString feedback = QInputDialog::getText(this, "Send Feedback", "Your feedback:", QLineEdit::Normal, "", &ok);
    if (ok && !feedback.trimmed().isEmpty()) {
        Translator::submitFeedback(feedback, 5);
        QMessageBox::information(this, "Thank You", "Feedback submitted!");
    }
}

void MainWindow::managePlugins() {
    QStringList plugins;
    for (const auto& meta : Translator::listPlugins()) {
        plugins << QString("%1 v%2 by %3").arg(meta.name, meta.version, meta.author);
    }
    if (plugins.isEmpty()) plugins << "No plugins loaded.";
    QMessageBox::information(this, "Plugins", plugins.join("\n"));
}

void MainWindow::showAbout() {
    QMessageBox::about(this, "About CodeTranslator",
        "<b>CodeTranslator</b><br>Version 2.0.0<br>Advanced code translation toolkit.<br><br>Copyright &copy; 2024 CodeTrans Inc.");
}

void MainWindow::showHelp() {
    QMessageBox::information(this, "Help",
        "1. Select source and target languages.<br>"
        "2. Paste or load your code.<br>"
        "3. Click Translate.<br>"
        "4. Save, copy, or review output.<br>"
        "5. Use menu for more features.<br>"
        "6. Use Edit menu to change font or theme.<br>"
        "7. Use Tools for history, plugins, and stats.<br>"
        "8. Use the new tabs for organized navigation.");
}

void MainWindow::reportBug() {
    QDesktopServices::openUrl(QUrl("https://github.com/sugarypumpkin822/code-converter/issues/new?labels=bug"));
}

void MainWindow::setFont() {
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->inputTextEdit->setFont(font);
        ui->outputTextEdit->setFont(font);
        statusBar()->showMessage("Font changed", 1000);
    }
}

void MainWindow::setThemeColor() {
    QColor color = QColorDialog::getColor(Qt::white, this, "Select Theme Color");
    if (color.isValid()) {
        QPalette pal = this->palette();
        pal.setColor(QPalette::Window, color);
        this->setPalette(pal);
        statusBar()->showMessage("Theme color changed", 1000);
    }
}

void MainWindow::openOutputDirectory() {
    QDir dir = QDir::current();
    QDesktopServices::openUrl(QUrl::fromLocalFile(dir.absolutePath()));
}

void MainWindow::showRandomTip() {
    QStringList tips = {
        "Tip: You can use Ctrl+S to save output quickly!",
        "Tip: Double-click a tab to rename it.",
        "Tip: Use the Edit menu to customize font and colors.",
        "Tip: Import/export your translation history via File menu.",
        "Tip: Check out the Plugins tab for extra features.",
        "Tip: You can drag to resize input and output panels."
    };
    int idx = QRandomGenerator::global()->bounded(tips.size());
    QMessageBox::information(this, "Random Tip", tips[idx]);
}

void MainWindow::saveSettings() {
    QSettings settings("CodeTrans Inc.", "CodeTranslator");
    settings.setValue("sourceLang", ui->sourceLangComboBox->currentText());
    settings.setValue("targetLang", ui->targetLangComboBox->currentText());
    settings.setValue("font", ui->inputTextEdit->font());
    settings.setValue("themeColor", this->palette().color(QPalette::Window));
}

void MainWindow::loadSettings() {
    QSettings settings("CodeTrans Inc.", "CodeTranslator");
    QString src = settings.value("sourceLang").toString();
    QString tgt = settings.value("targetLang").toString();
    if (!src.isEmpty()) ui->sourceLangComboBox->setCurrentText(src);
    if (!tgt.isEmpty()) ui->targetLangComboBox->setCurrentText(tgt);
    QFont font = settings.value("font").value<QFont>();
    if (font != QFont())
        ui->inputTextEdit->setFont(font), ui->outputTextEdit->setFont(font);
    QColor color = settings.value("themeColor").value<QColor>();
    if (color.isValid()) {
        QPalette pal = this->palette();
        pal.setColor(QPalette::Window, color);
        this->setPalette(pal);
    }
}

void MainWindow::autoSave() {
    QString tempPath = QDir::temp().filePath("codetranslator_autosave.cpp");
    QFile file(tempPath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << ui->outputTextEdit->toPlainText();
        file.close();
        statusBar()->showMessage("Auto-saved output", 1000);
    }
}

QList<MainWindow::TranslationEntry> MainWindow::translationHistory;
