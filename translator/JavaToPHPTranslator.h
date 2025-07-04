#ifndef JAVATOPHPTRANSLATOR_H
#define JAVATOPHPTRANSLATOR_H
#include <QString>
#include "TranslatorBase.h"
class JavaToPHPTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "Java"; }
    QString targetLanguage() const override { return "PHP"; }
    QString translate(const QString& code) const override;
};
#endif // JAVATOPHPTRANSLATOR_H 