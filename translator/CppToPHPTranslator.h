#ifndef CPPTOPHPTRANSLATOR_H
#define CPPTOPHPTRANSLATOR_H
#include <QString>
#include "TranslatorBase.h"
class CppToPHPTranslator : public TranslatorBase {
public:
    QString sourceLanguage() const override { return "C++"; }
    QString targetLanguage() const override { return "PHP"; }
    QString translate(const QString& code) const override;
};
#endif // CPPTOPHPTRANSLATOR_H 