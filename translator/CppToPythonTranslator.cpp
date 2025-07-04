#include "CppToPythonTranslator.h"
#include <QRegularExpression>

QString CppToPythonTranslator::translate(const QString& code) const {
    QString pyCode = code;
    pyCode.replace(QRegularExpression(R"(std::cout\s*<<\s*(.*?)\s*<<\s*std::endl;)"), "print(\\1)");
    pyCode.replace(QRegularExpression(R"(int\s+(\w+)\s*=\s*(\d+);)"), "\\1 = \\2");
    pyCode.replace(QRegularExpression(R"(std::string\s+(\w+)\s*=\s*\"(.*?)\";)"), "\\1 = \"\\2\"");
    pyCode.replace(QRegularExpression(R"(void\s+(\w+)\((.*?)\)\s*{)"), "def \\1(\\2):");
    pyCode.replace(QRegularExpression(R"(for\s*\(int\s+(\w+)\s*=\s*(\d+);\s*\\1\s*<\s*(\d+);\s*\+\+\\1\))"), "for \\1 in range(\\2, \\3):");
    pyCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if \\1:");
    pyCode.replace(QRegularExpression(R"(else\s*{)"), "else:");
    pyCode.replace(QRegularExpression(R"(}|{)"), "");
    pyCode.replace(";", "");
    return pyCode;
} 