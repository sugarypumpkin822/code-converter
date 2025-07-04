#ifndef CPPTOPYTHONTRANSLATOR_H
#define CPPTOPYTHONTRANSLATOR_H

#include "TranslatorBase.h"

class CppToPythonTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "C++"; }
    QString targetLanguage() const override { return "Python"; }
    QString translate(const QString& code) const override;
};

#endif // CPPTOPYTHONTRANSLATOR_H 