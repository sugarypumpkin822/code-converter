#ifndef CSHARPTOPHPTRANSLATOR_H
#define CSHARPTOPHPTRANSLATOR_H
#include <QString>
#include "TranslatorBase.h"
class CSharpToPHPTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "C#"; }
    QString targetLanguage() const override { return "PHP"; }
    QString translate(const QString& code) const override;
};
#endif // CSHARPTOPHPTRANSLATOR_H 