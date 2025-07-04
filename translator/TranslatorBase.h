#ifndef TRANSLATORBASE_H
#define TRANSLATORBASE_H

#include <QString>

class TranslatorBase {
public:
    virtual ~TranslatorBase() {}
    virtual QString sourceLanguage() const = 0;
    virtual QString targetLanguage() const = 0;
    virtual QString translate(const QString& code) const = 0;
};

#endif // TRANSLATORBASE_H 