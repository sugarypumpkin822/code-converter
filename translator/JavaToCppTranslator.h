#ifndef JAVATOCPPTRANSLATOR_H
#define JAVATOCPPTRANSLATOR_H
#include "TranslatorBase.h"
class JavaToCppTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "Java"; }
    QString targetLanguage() const override { return "C++"; }
    QString translate(const QString& code) const override;
};
#endif // JAVATOCPPTRANSLATOR_H 