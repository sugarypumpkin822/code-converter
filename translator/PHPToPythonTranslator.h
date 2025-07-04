#ifndef PHPTOPYTHONTRANSLATOR_H
#define PHPTOPYTHONTRANSLATOR_H
#include <QString>
#include "TranslatorBase.h"
class PHPToPythonTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "PHP"; }
    QString targetLanguage() const override { return "Python"; }
    QString translate(const QString& code) const override;
};
#endif // PHPTOPYTHONTRANSLATOR_H 