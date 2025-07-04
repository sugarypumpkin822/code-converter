#ifndef TRANSLATORFACTORY_H
#define TRANSLATORFACTORY_H

#include "TranslatorBase.h"
#include <memory>

class TranslatorFactory {
public:
    static std::unique_ptr<TranslatorBase> create(const QString& sourceLang, const QString& targetLang);
};

#endif // TRANSLATORFACTORY_H 