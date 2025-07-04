#ifndef PYTHONTOJAVASCRIPTTRANSLATOR_H
#define PYTHONTOJAVASCRIPTTRANSLATOR_H
#include "TranslatorBase.h"
class PythonToJavaScriptTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "Python"; }
    QString targetLanguage() const override { return "JavaScript"; }
    QString translate(const QString& code) const override;
};
#endif // PYTHONTOJAVASCRIPTTRANSLATOR_H 