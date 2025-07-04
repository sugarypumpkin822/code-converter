#ifndef CSHARPTOJAVATRANSLATOR_H
#define CSHARPTOJAVATRANSLATOR_H
#include <QString>
#include "TranslatorBase.h"
class CSharpToJavaTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "C#"; }
    QString targetLanguage() const override { return "Java"; }
    QString translate(const QString& code) const override;
};
#endif // CSHARPTOJAVATRANSLATOR_H 