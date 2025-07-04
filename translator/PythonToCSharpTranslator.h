#ifndef PYTHONTOCSHARPTRANSLATOR_H
#define PYTHONTOCSHARPTRANSLATOR_H
#include <QString>
#include "TranslatorBase.h"
class PythonToCSharpTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "Python"; }
    QString targetLanguage() const override { return "C#"; }
    QString translate(const QString& code) const override;
};
#endif // PYTHONTOCSHARPTRANSLATOR_H 