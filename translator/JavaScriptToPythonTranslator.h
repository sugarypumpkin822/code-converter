#ifndef JAVASCRIPTTOPYTHONTRANSLATOR_H
#define JAVASCRIPTTOPYTHONTRANSLATOR_H
#include "TranslatorBase.h"
class JavaScriptToPythonTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "JavaScript"; }
    QString targetLanguage() const override { return "Python"; }
    QString translate(const QString& code) const override;
};
#endif // JAVASCRIPTTOPYTHONTRANSLATOR_H 