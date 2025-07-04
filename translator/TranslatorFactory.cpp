#include <QString>
#include "TranslatorFactory.h"
#include "CppToJavaScriptTranslator.h"
#include "CppToJavaTranslator.h"
#include "CppToPythonTranslator.h"
#include "CppToPHPTranslator.h"
#include "CSharpToJavaTranslator.h"
#include "CSharpToPHPTranslator.h"
#include "CSharpToPythonTranslator.h"
#include "JavaScriptToCppTranslator.h"
#include "JavaScriptToJavaTranslator.h"
#include "JavaScriptToPythonTranslator.h"
#include "JavaToCppTranslator.h"
#include "JavaToCSharpTranslator.h"
#include "JavaToPythonTranslator.h"
#include "JavaToPHPTranslator.h"
#include "PHPToJavaTranslator.h"
#include "PHPToPythonTranslator.h"
#include "PHPToCppTranslator.h"
#include "PHPToCSharpTranslator.h"
#include "PythonToCppTranslator.h"
#include "PythonToCSharpTranslator.h"
#include "PythonToJavaScriptTranslator.h"
#include "PythonToJavaTranslator.h"
#include <memory>

std::unique_ptr<TranslatorBase> TranslatorFactory::create(const QString& sourceLang, const QString& targetLang) {
    if (sourceLang == "C++" && targetLang == "JavaScript") return std::make_unique<CppToJavaScriptTranslator>();
    if (sourceLang == "C++" && targetLang == "Java") return std::make_unique<CppToJavaTranslator>();
    if (sourceLang == "C++" && targetLang == "Python") return std::make_unique<CppToPythonTranslator>();
    if (sourceLang == "C++" && targetLang == "PHP") return std::make_unique<CppToPHPTranslator>();
    if (sourceLang == "C#" && targetLang == "Java") return std::make_unique<CSharpToJavaTranslator>();
    if (sourceLang == "C#" && targetLang == "PHP") return std::make_unique<CSharpToPHPTranslator>();
    if (sourceLang == "C#" && targetLang == "Python") return std::make_unique<CSharpToPythonTranslator>();
    if (sourceLang == "JavaScript" && targetLang == "C++") return std::make_unique<JavaScriptToCppTranslator>();
    if (sourceLang == "JavaScript" && targetLang == "Java") return std::make_unique<JavaScriptToJavaTranslator>();
    if (sourceLang == "JavaScript" && targetLang == "Python") return std::make_unique<JavaScriptToPythonTranslator>();
    if (sourceLang == "Java" && targetLang == "C++") return std::make_unique<JavaToCppTranslator>();
    if (sourceLang == "Java" && targetLang == "C#") return std::make_unique<JavaToCSharpTranslator>();
    if (sourceLang == "Java" && targetLang == "Python") return std::make_unique<JavaToPythonTranslator>();
    if (sourceLang == "Java" && targetLang == "PHP") return std::make_unique<JavaToPHPTranslator>();
    if (sourceLang == "PHP" && targetLang == "Java") return std::make_unique<PHPToJavaTranslator>();
    if (sourceLang == "PHP" && targetLang == "Python") return std::make_unique<PHPToPythonTranslator>();
    if (sourceLang == "PHP" && targetLang == "C++") return std::make_unique<PHPToCppTranslator>();
    if (sourceLang == "PHP" && targetLang == "C#") return std::make_unique<PHPToCSharpTranslator>();
    if (sourceLang == "Python" && targetLang == "C++") return std::make_unique<PythonToCppTranslator>();
    if (sourceLang == "Python" && targetLang == "C#") return std::make_unique<PythonToCSharpTranslator>();
    if (sourceLang == "Python" && targetLang == "JavaScript") return std::make_unique<PythonToJavaScriptTranslator>();
    if (sourceLang == "Python" && targetLang == "Java") return std::make_unique<PythonToJavaTranslator>();
    return nullptr;
} 