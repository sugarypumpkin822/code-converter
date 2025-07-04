#ifndef PYTHONTOJAVATRANSLATOR_H
#define PYTHONTOJAVATRANSLATOR_H
#include <QString>
#include "TranslatorBase.h"
class PythonToJavaTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "Python"; }
    QString targetLanguage() const override { return "Java"; }
    QString translate(const QString& code) const override;
};
#endif // PYTHONTOJAVATRANSLATOR_H 