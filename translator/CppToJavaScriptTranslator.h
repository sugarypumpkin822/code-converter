#ifndef CPPTOJAVASCRIPTTRANSLATOR_H
#define CPPTOJAVASCRIPTTRANSLATOR_H
#include <QString>
#include "TranslatorBase.h"
class CppToJavaScriptTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "C++"; }
    QString targetLanguage() const override { return "JavaScript"; }
    QString translate(const QString& code) const override;
};
#endif // CPPTOJAVASCRIPTTRANSLATOR_H 