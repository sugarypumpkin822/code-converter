[⚠️ Suspicious Content] #ifndef CSHARPTOJAVATRANSLATOR_H
#define CSHARPTOJAVATRANSLATOR_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QRegularExpression>
#include <QSet>
#include "TranslatorBase.h"

/**
 * @class CSharpToJavaTranslator
 * @brief Translates C# code to Java with comprehensive syntax and semantic mapping
 * 
 * This translator handles various C# language constructs and converts them to
 * their Java equivalents, including:
 * - Type mappings (string -> String, int -> int, etc.)
 * - Access modifiers and visibility
 * - Property syntax conversion
 * - LINQ to Java Streams
 * - Exception handling differences
 * - Namespace to package conversion
 * - Generic type parameter constraints
 */
class CSharpToJavaTranslator : public TranslatorBase {
public:
    /**
     * @brief Default constructor
     */
    CSharpToJavaTranslator();
    
    /**
     * @brief Virtual destructor
     */
    virtual ~CSharpToJavaTranslator() = default;

    /**
     * @brief Returns the source language identifier
     * @return QString "C#"
     */
    QString sourceLanguage() const override { return "C#"; }
    
    /**
     * @brief Returns the target language identifier
     * @return QString "Java"
     */
    QString targetLanguage() const override { return "Java"; }
    
    /**
     * @brief Main translation method
     * @param code The C# code to translate
     * @return QString The translated Java code
     */
    QString translate(const QString& code) const override;

    /**
     * @brief Set translation options
     * @param options Map of option key-value pairs
     */
    void setTranslationOptions(const QMap<QString, QString>& options);
    
    /**
     * @brief Get current translation options
     * @return QMap<QString, QString> Current options
     */
    QMap<QString, QString> getTranslationOptions() const;

private:
    // Translation helper methods
    QString translateTypes(const QString& code) const;
    QString translateProperties(const QString& code) const;
    QString translateMethods(const QString& code) const;
    QString translateClasses(const QString& code) const;
    QString translateNamespaces(const QString& code) const;
    QString translateUsings(const QString& code) const;
    QString translateLinq(const QString& code) const;
    QString translateExceptionHandling(const QString& code) const;
    QString translateGenerics(const QString& code) const;
    QString translateAccessModifiers(const QString& code) const;
    QString translateEvents(const QString& code) const;
    QString translateDelegates(const QString& code) const;
    QString translateAttributes(const QString& code) const;
    QString translateStringInterpolation(const QString& code) const;
    QString translateNullableTypes(const QString& code) const;
    QString translateVarKeyword(const QString& code) const;
    QString translateAutoProperties(const QString& code) const;
    QString translateCollectionInitializers(const QString& code) const;
    QString translateObjectInitializers(const QString& code) const;
    QString translateLambdaExpressions(const QString& code) const;
    QString translateAsyncAwait(const QString& code) const;
    
    // Utility methods
    QString extractClassDefinition(const QString& code, int startPos) const;
    QString extractMethodDefinition(const QString& code, int startPos) const;
    QString extractPropertyDefinition(const QString& code, int startPos) const;
    QString generateJavaPackageDeclaration(const QString& csharpNamespace) const;
    QString generateJavaImports(const QStringList& csharpUsings) const;
    QString convertCSharpTypeToJava(const QString& csharpType) const;
    QString convertAccessModifier(const QString& csharpModifier) const;
    QString generateGetterSetter(const QString& propertyName, const QString& propertyType) const;
    
    // Validation methods
    bool isValidCSharpCode(const QString& code) const;
    bool hasUnsupportedFeatures(const QString& code) const;
    QStringList getUnsupportedFeatures(const QString& code) const;
    
    // Pattern matching
    QRegularExpression createRegexForPattern(const QString& pattern) const;
    QString applyRegexReplacement(const QString& code, const QRegularExpression& regex, const QString& replacement) const;
    
    // Data members
    QMap<QString, QString> m_typeMapping;          ///< C# to Java type mappings
    QMap<QString, QString> m_keywordMapping;       ///< C# to Java keyword mappings
    QMap<QString, QString> m_namespaceMapping;     ///< Common namespace mappings
    QMap<QString, QString> m_translationOptions;   ///< Translation configuration options
    QSet<QString> m_unsupportedFeatures;          ///< Set of unsupported C# features
    
    // Static data
    static const QMap<QString, QString> s_primitiveTypes;
    static const QMap<QString, QString> s_collectionTypes;
    static const QMap<QString, QString> s_frameworkTypes;
    static const QStringList s_reservedJavaKeywords;
    
    // Configuration constants
    static const int MAX_CODE_LENGTH = 1000000;     ///< Maximum supported code length
    static const int MAX_NESTING_LEVEL = 50;        ///< Maximum supported nesting level
    
    // Translation flags
    mutable bool m_preserveComments;                ///< Whether to preserve comments
    mutable bool m_generateJavaDoc;                 ///< Whether to generate JavaDoc
    mutable bool m_strictTypeChecking;              ///< Whether to enforce strict type checking
    mutable bool m_optimizeImports;                 ///< Whether to optimize import statements
    mutable bool m_convertLinqToStreams;            ///< Whether to convert LINQ to Java Streams
    mutable bool m_handleAsyncAwait;                ///< Whether to handle async/await patterns
    
    // Error handling
    mutable QStringList m_translationWarnings;     ///< List of translation warnings
    mutable QStringList m_translationErrors;       ///< List of translation errors
    
    // Helper methods for complex translations
    QString translateComplexExpression(const QString& expression) const;
    QString translateMethodChain(const QString& chain) const;
    QString translateConditionalExpression(const QString& expression) const;
    QString translateSwitchExpression(const QString& expression) const;
    QString translatePatternMatching(const QString& pattern) const;
    
    // Code analysis methods
    int calculateNestingLevel(const QString& code) const;
    QStringList extractDependencies(const QString& code) const;
    QStringList extractClassNames(const QString& code) const;
    QStringList extractMethodNames(const QString& code) const;
    
    // Code formatting methods
    QString formatJavaCode(const QString& code) const;
    QString addIndentation(const QString& code, int level) const;
    QString normalizeWhitespace(const QString& code) const;
    
public slots:
    /**
     * @brief Slot for handling translation progress updates
     * @param percentage Progress percentage (0-100)
     */
    void onTranslationProgress(int percentage);
    
signals:
    /**
     * @brief Signal emitted when translation progress changes
     * @param percentage Progress percentage (0-100)
     */
    void translationProgressChanged(int percentage);
    
    /**
     * @brief Signal emitted when translation is completed
     * @param success Whether translation was successful
     * @param result The translated code or error message
     */
    void translationCompleted(bool success, const QString& result);
    
    /**
     * @brief Signal emitted when a translation warning occurs
     * @param warning The warning message
     */
    void translationWarning(const QString& warning);
    
    /**
     * @brief Signal emitted when a translation error occurs
     * @param error The error message
     */
    void translationError(const QString& error);
};

#endif // CSHARPTOJAVATRANSLATOR_H
