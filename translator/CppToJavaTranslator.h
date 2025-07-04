#ifndef CPPTOJAVATRANSLATOR_H
#define CPPTOJAVATRANSLATOR_H
#include "TranslatorBase.h"
class CppToJavaTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "C++"; }
    QString targetLanguage() const override { return "Java"; }
    QString translate(const QString& code) const override;
};
#endif // CPPTOJAVATRANSLATOR_H 