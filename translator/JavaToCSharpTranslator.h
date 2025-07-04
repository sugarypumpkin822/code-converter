#ifndef JAVATOCSHARPTRANSLATOR_H
#define JAVATOCSHARPTRANSLATOR_H
#include <QString>
#include "TranslatorBase.h"
class JavaToCSharpTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "Java"; }
    QString targetLanguage() const override { return "C#"; }
    QString translate(const QString& code) const override;
};
#endif // JAVATOCSHARPTRANSLATOR_H 