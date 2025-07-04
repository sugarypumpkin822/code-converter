#ifndef JAVASCRIPTTOCPPTRANSLATOR_H
#define JAVASCRIPTTOCPPTRANSLATOR_H

#include "TranslatorBase.h"

class JavaScriptToCppTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "JavaScript"; }
    QString targetLanguage() const override { return "C++"; }
    QString translate(const QString& code) const override;
};

#endif // JAVASCRIPTTOCPPTRANSLATOR_H 