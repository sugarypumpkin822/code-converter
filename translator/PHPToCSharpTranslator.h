#ifndef PHPTOCSHARPTRANSLATOR_H
#define PHPTOCSHARPTRANSLATOR_H
#include <QString>
#include "TranslatorBase.h"
class PHPToCSharpTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "PHP"; }
    QString targetLanguage() const override { return "C#"; }
    QString translate(const QString& code) const override;
};
#endif // PHPTOCSHARPTRANSLATOR_H 