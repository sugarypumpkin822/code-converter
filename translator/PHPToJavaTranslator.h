#ifndef PHPTOVAJATRANSLATOR_H
#define PHPTOVAJATRANSLATOR_H
#include <QString>
#include "TranslatorBase.h"
class PHPToJavaTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "PHP"; }
    QString targetLanguage() const override { return "Java"; }
    QString translate(const QString& code) const override;
};
#endif // PHPTOVAJATRANSLATOR_H 