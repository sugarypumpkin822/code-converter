#ifndef CSHARPTOPYTHONTRANSLATOR_H
#define CSHARPTOPYTHONTRANSLATOR_H
#include <QString>
#include "TranslatorBase.h"
class CSharpToPythonTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "C#"; }
    QString targetLanguage() const override { return "Python"; }
    QString translate(const QString& code) const override;
};
#endif // CSHARPTOPYTHONTRANSLATOR_H 