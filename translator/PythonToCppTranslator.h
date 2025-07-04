#ifndef PYTHONTOCPPTRANSLATOR_H
#define PYTHONTOCPPTRANSLATOR_H

#include "TranslatorBase.h"

class PythonToCppTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "Python"; }
    QString targetLanguage() const override { return "C++"; }
    QString translate(const QString& code) const override;
};

#endif // PYTHONTOCPPTRANSLATOR_H 