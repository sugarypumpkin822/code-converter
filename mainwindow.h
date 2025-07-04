#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QFont>
#include <QColor>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct TranslationEntry {
        QString sourceLang;
        QString targetLang;
        QString input;
        QString output;
        QDateTime timestamp;
    };

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_translateButton_clicked();
    void saveOutput();
    void loadInput();
    void exportHistory();
    void importHistory();
    void copyOutput();
    void clearAll();
    void showHistory();
    void showStats();
    void sendFeedback();
    void managePlugins();
    void showAbout();
    void showHelp();
    void reportBug();
    void setFont();
    void setThemeColor();
    void openOutputDirectory();
    void showRandomTip();
    void saveSettings();
    void loadSettings();
    void autoSave();

protected:
    void closeEvent(QCloseEvent *event) override {
        saveSettings();
        QMainWindow::closeEvent(event);
    }

private:
    Ui::MainWindow *ui;
    QTimer *autoSaveTimer;

    // Static translation history (shared for all instances)
    static QList<TranslationEntry> translationHistory;
};

#endif // MAINWINDOW_H
