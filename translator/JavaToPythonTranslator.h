#ifndef JAVATOPYTHONTRANSLATOR_H
#define JAVATOPYTHONTRANSLATOR_H
#include <QString>
#include "TranslatorBase.h"
class JavaToPythonTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "Java"; }
    QString targetLanguage() const override { return "Python"; }
    QString translate(const QString& code) const override;
};
#endif // JAVATOPYTHONTRANSLATOR_H 