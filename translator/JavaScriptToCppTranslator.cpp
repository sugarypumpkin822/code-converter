#include "JavaScriptToCppTranslator.h"
#include <QRegularExpression>

QString JavaScriptToCppTranslator::translate(const QString& code) const {
    QString cppCode = code;
    cppCode.replace(QRegularExpression(R"(console\.log\((.*?)\);)"), "std::cout << \1 << std::endl;");
    cppCode.replace(QRegularExpression(R"((var|let|const)\s+(\w+)\s*=\s*(.*?);)"), "auto \2 = \3;");
    cppCode.replace(QRegularExpression(R"(function\s+(\w+)\((.*?)\)\s*{)"), "void \1(\2) {");
    cppCode.replace(QRegularExpression(R"(for\s*\(let\s+(\w+)\s*=\s*0;\s*\1\s*<\s*(\w+);\s*\1\+\+\)\s*{)"), "for (int \1 = 0; \1 < \2; \1++) {");
    cppCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if (\1) {");
    cppCode.replace(QRegularExpression(R"(else\s*{)"), "} else {");
    return cppCode;
} 