#ifndef PHPTOPCPTRANSLATOR_H
#define PHPTOPCPTRANSLATOR_H
#include <QString>
#include "TranslatorBase.h"
class PHPToCppTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "PHP"; }
    QString targetLanguage() const override { return "C++"; }
    QString translate(const QString& code) const override;
};
#endif // PHPTOPCPTRANSLATOR_H 