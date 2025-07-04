#ifndef JAVASCRIPTTOJAVATRANSLATOR_H
#define JAVASCRIPTTOJAVATRANSLATOR_H
#include "TranslatorBase.h"
class JavaScriptToJavaTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "JavaScript"; }
    QString targetLanguage() const override { return "Java"; }
    QString translate(const QString& code) const override;
};
#endif // JAVASCRIPTTOJAVATRANSLATOR_H 