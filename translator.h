#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QList>
#include <QVariant>
#include <QDateTime>
#include <QByteArray>
#include <QUrl>
#include <QTimer>
#include <QJsonObject>
#include <QJsonArray>
#include <QSet>
#include <QPair>
#include <memory>

/**
 * @brief The Translator class provides static and extensible methods for translating code between languages.
 * It is designed for advanced, modular, and future-proof code translation systems.
 * Features include plugins, analysis, metrics, version control, security, batch operations, scheduling, networking, and more.
 */
class Translator {
public:
    /** Translation modes */
    enum class Mode {
        Fast,
        Accurate,
        Custom,
        Default
    };
    /** Error types */
    enum class ErrorType {
        Warning,
        Error,
        Critical,
        Info
    };
    /** Optimization levels */
    enum class OptimizationLevel {
        None,
        Basic,
        Aggressive
    };
    /** Scheduling types */
    enum class ScheduleType {
        Once,
        Recurring,
        OnChange
    };
    /** Authentication roles */
    enum class UserRole {
        Guest,
        User,
        Admin
    };
    /** External tool types */
    enum class ExternalTool {
        IDE,
        CICD,
        Linter,
        Formatter
    };
    /** Translation report struct */
    struct TranslationReport {
        QString sourceLang;
        QString targetLang;
        QDateTime timestamp;
        QStringList warnings;
        QStringList errors;
        int linesTranslated = 0;
        int filesTranslated = 0;
        double durationSeconds = 0.0;
        QString summary;
    };
    /** User profile struct */
    struct UserProfile {
        QString username;
        UserRole role = UserRole::Guest;
        QString email;
        QDateTime lastLogin;
        QStringList permissions;
    };
    /** Plugin metadata struct */
    struct PluginMetadata {
        QString name;
        QString version;
        QString author;
        QString description;
        QDateTime installDate;
    };
    /** Event callback type */
    typedef void (*EventCallback)(const QString& event, const QVariant& data);

    // Main translation entry point
    static QString translate(const QString& sourceLang, const QString& targetLang, const QString& code, Mode mode = Mode::Default);

    // Helper functions for more advanced translation
    static QString translateVariables(const QString& sourceLang, const QString& code);
    static QString translateFunctions(const QString& sourceLang, const QString& code);
    static QString translateLoops(const QString& sourceLang, const QString& code);
    static QString translateConditionals(const QString& sourceLang, const QString& code);
    static QString translateClasses(const QString& sourceLang, const QString& code);
    static QString translateImports(const QString& sourceLang, const QString& code);
    static QString translateComments(const QString& sourceLang, const QString& code, const QString& targetHumanLang = "en");
    static QString handleErrors(const QString& code);

    // Utility functions for extensibility
    static QString detectLanguage(const QString& code);
    static QStringList supportedLanguages();

    // Advanced extensibility: translation settings
    struct TranslationSettings {
        bool formatOutput = true;
        bool addComments = true;
        QMap<QString, QString> customMappings;
        QString profileName;
        QString outputStyle;
        QStringList enabledPlugins;
        OptimizationLevel optimization = OptimizationLevel::Basic;
        Mode mode = Mode::Accurate;
        QString watermark;
        QString license;
        QMap<QString, QVariant> customSettings;
    };
    static void setSettings(const TranslationSettings& settings);
    static TranslationSettings getSettings();
    static bool exportProfile(const QString& filePath);
    static bool importProfile(const QString& filePath);

    // Plugin-based extensibility
    class TranslatorPlugin {
    public:
        virtual ~TranslatorPlugin() {}
        virtual QString pluginName() const = 0;
        virtual QStringList supportedSourceLanguages() const = 0;
        virtual QStringList supportedTargetLanguages() const = 0;
        virtual QString translate(const QString& sourceLang, const QString& targetLang, const QString& code) = 0;
        virtual PluginMetadata metadata() const = 0;
    };
    static void registerPlugin(TranslatorPlugin* plugin);
    static void unregisterPlugin(TranslatorPlugin* plugin);
    static QList<PluginMetadata> listPlugins();

    // Code analysis and linting
    static QString lintCode(const QString& lang, const QString& code);
    static QString analyzeCode(const QString& lang, const QString& code);
    static QString staticAnalysis(const QString& lang, const QString& code);
    static QString dynamicAnalysis(const QString& lang, const QString& code);

    // Code optimization
    static QString optimizeCode(const QString& lang, const QString& code);
    static QString refactorCode(const QString& lang, const QString& code, const QString& refactorType);
    static QString minifyCode(const QString& lang, const QString& code);
    static QString beautifyCode(const QString& lang, const QString& code);

    // Syntax highlighting
    static QString highlightSyntax(const QString& lang, const QString& code);

    // Code metrics/statistics
    struct CodeMetrics {
        int lineCount = 0;
        int functionCount = 0;
        int classCount = 0;
        int variableCount = 0;
        int commentCount = 0;
        int importCount = 0;
        int fileCount = 0;
        int warningCount = 0;
        int errorCount = 0;
        // Add more metrics as needed
    };
    static CodeMetrics getCodeMetrics(const QString& lang, const QString& code);

    // Dependency analysis
    static QStringList getDependencies(const QString& lang, const QString& code);
    static QMap<QString, QStringList> dependencyTree(const QString& lang, const QString& code);

    // Version control integration
    static QString getGitDiff(const QString& filePath1, const QString& filePath2);
    static QString commitTranslation(const QString& repoPath, const QString& message);
    static QString getGitHistory(const QString& repoPath, int maxEntries = 100);

    // User-defined translation rules
    static void addCustomRule(const QString& ruleName, const QVariant& ruleDef);
    static void removeCustomRule(const QString& ruleName);
    static QVariant getCustomRule(const QString& ruleName);
    static QString applyCustomRules(const QString& code);
    static QStringList listCustomRules();

    // Batch translation support
    static QStringList batchTranslate(const QString& sourceLang, const QString& targetLang, const QStringList& codeList);
    static TranslationReport batchTranslateReport(const QString& sourceLang, const QString& targetLang, const QStringList& codeList);

    // Undo/redo translation history
    static void undo();
    static void redo();
    static QStringList getTranslationHistory();
    static void clearTranslationHistory();

    // Logging and diagnostics
    static void logEvent(const QString& event);
    static QStringList getLogs();
    static void clearLogs();
    static void setLogLevel(ErrorType level);

    // Security/safety checks
    static bool isCodeSafe(const QString& lang, const QString& code);
    static QStringList getSecurityWarnings(const QString& lang, const QString& code);
    static bool checkForMalware(const QString& code);

    // Macro/preprocessor support
    static QString processMacros(const QString& lang, const QString& code);
    static QStringList extractMacros(const QString& lang, const QString& code);

    // Code similarity/diff tools
    static double codeSimilarity(const QString& code1, const QString& code2);
    static QString codeDiff(const QString& code1, const QString& code2);

    // Custom error/warning reporting
    struct TranslationError {
        QString message;
        int line = -1;
        int column = -1;
        ErrorType severity = ErrorType::Warning;
        QDateTime timestamp;
        QString fileName;
    };
    static QList<TranslationError> getTranslationErrors();
    static void clearTranslationErrors();
    static void reportError(const TranslationError& error);

    // Internationalization (i18n) for translation messages
    static QString translateMessage(const QString& message, const QString& locale);
    static QStringList supportedLocales();

    // Scheduling/automation
    struct ScheduledTask {
        QString taskName;
        ScheduleType type = ScheduleType::Once;
        QDateTime scheduledTime;
        QStringList codeFiles;
        QString sourceLang;
        QString targetLang;
        bool enabled = true;
    };
    static void scheduleTask(const ScheduledTask& task);
    static void cancelTask(const QString& taskName);
    static QList<ScheduledTask> listScheduledTasks();

    // Network/cloud translation support (for future use)
    static bool enableCloudTranslation(bool enable);
    static bool isCloudTranslationEnabled();
    static QString cloudTranslate(const QString& sourceLang, const QString& targetLang, const QString& code);
    static QStringList listCloudProviders();

    // User authentication and permissions
    static bool login(const QString& username, const QString& password);
    static void logout();
    static UserProfile currentUser();
    static bool hasPermission(const QString& permission);

    // External tool integration
    static bool integrateWithTool(ExternalTool tool, const QVariant& config);
    static QStringList listIntegratedTools();

    // Templates and presets
    static QString applyTemplate(const QString& templateName, const QString& code);
    static QStringList listTemplates();
    static void addTemplate(const QString& templateName, const QString& templateCode);
    static void removeTemplate(const QString& templateName);

    // Event/callback system
    static void registerEventCallback(const QString& event, EventCallback callback);
    static void unregisterEventCallback(const QString& event, EventCallback callback);
    static void triggerEvent(const QString& event, const QVariant& data);

    // Watermarking and digital signatures
    static QString addWatermark(const QString& code, const QString& watermark);
    static bool verifyWatermark(const QString& code, const QString& watermark);
    static QString signCode(const QString& code, const QString& privateKey);
    static bool verifySignature(const QString& code, const QString& publicKey);

    // Benchmarking and performance statistics
    struct BenchmarkResult {
        double translationTimeMs = 0.0;
        double memoryUsageMb = 0.0;
        int linesProcessed = 0;
        QString summary;
    };
    static BenchmarkResult benchmarkTranslation(const QString& sourceLang, const QString& targetLang, const QString& code);

    // Preview and step-by-step walkthroughs
    static QStringList previewTranslationSteps(const QString& sourceLang, const QString& targetLang, const QString& code);
    static QString getTranslationStepDetail(int stepIndex);

    // Rollback and snapshotting
    static void createSnapshot(const QString& name);
    static void rollbackToSnapshot(const QString& name);
    static QStringList listSnapshots();

    // Multi-file/project translation context
    static QString translateProject(const QString& projectPath, const QString& targetLang);
    static QStringList listProjectFiles(const QString& projectPath);
    static void addProjectFile(const QString& projectPath, const QString& filePath);
    static void removeProjectFile(const QString& projectPath, const QString& filePath);

    // Feedback and user ratings
    static void submitFeedback(const QString& feedback, int rating);
    static QList<QPair<QString, int>> getFeedbackHistory();

    // Licensing and copyright management
    static QString getLicenseInfo();
    static void setLicenseInfo(const QString& licenseText);
    static bool isLicenseValid();

    // Reserved for future AI/ML and hardware acceleration
    // static QString aiSuggestTranslation(const QString& sourceLang, const QString& targetLang, const QString& code);
    // static QString gpuAcceleratedTranslate(const QString& sourceLang, const QString& targetLang, const QString& code);

    // Documentation and help
    static QString getDocumentation(const QString& lang, const QString& topic);
    static QStringList listHelpTopics();

private:
    static TranslationSettings currentSettings;
    static QList<TranslatorPlugin*> plugins;
    static QStringList translationHistory;
    static QList<TranslationError> translationErrors;
    static QStringList logs;
    static UserProfile userProfile;
    static QList<ScheduledTask> scheduledTasks;
    static QMap<QString, EventCallback> eventCallbacks;
    static QList<BenchmarkResult> benchmarkResults;
    static QMap<QString, QString> templates;
    static QMap<QString, QByteArray> snapshots;
    static QList<QPair<QString, int>> feedbackHistory;
    static QString licenseInfo;
};

#endif // TRANSLATOR_H 