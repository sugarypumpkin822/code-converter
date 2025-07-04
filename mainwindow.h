#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QList>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class provides the main GUI for CodeTranslator.
 * It includes advanced features such as translation history, settings, feedback, plugin management, and more.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /// Triggered when the Translate button is clicked
    void on_translateButton_clicked();
    /// Save output code to file
    void saveOutput();
    /// Load input code from file
    void loadInput();
    /// Copy output code to clipboard
    void copyOutput();
    /// Clear all input/output fields
    void clearAll();
    /// Show translation history dialog
    void showHistory();
    /// Send feedback dialog
    void sendFeedback();
    /// Manage plugins dialog
    void managePlugins();
    /// Show about dialog
    void showAbout();
    /// Show help dialog
    void showHelp();
    /// Save settings on close
    void saveSettings();
    /// Load settings on startup
    void loadSettings();

private:
    Ui::MainWindow *ui;

    /// Struct for translation history entries
    struct TranslationEntry {
        QString sourceLang;
        QString targetLang;
        QString input;
        QString output;
        QDateTime timestamp;
    };
    /// List of translation history entries
    static QList<TranslationEntry> translationHistory;
};

#endif // MAINWINDOW_H 