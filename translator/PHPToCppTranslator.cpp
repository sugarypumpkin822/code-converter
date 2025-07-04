#include <QString>
#include <QRegularExpression>
#include "PHPToCppTranslator.h"

QString PHPToCppTranslator::translate(const QString& code) const {
    QString cppCode = code;
    // echo ...; -> std::cout << ... << std::endl;
    cppCode.replace(QRegularExpression(R"(echo\s+(.*?);)"), "std::cout << \\1 << std::endl;");
    // $x = ...; -> int x = ...; (simple int)
    cppCode.replace(QRegularExpression(R"(\$(\w+)\s*=\s*(\d+);)"), "int \\1 = \\2;");
    // $x = "..."; -> std::string x = "...";
    cppCode.replace(QRegularExpression(R"(\$(\w+)\s*=\s*\"(.*?)\";)"), "std::string \\1 = \"\\2\";");
    // function func(args) { -> void func(args) {
    cppCode.replace(QRegularExpression(R"(function\s+(\w+)\((.*?)\)\s*{)"), "void \\1(\\2) {");
    // for ($i = 0; $i < n; $i++) -> for (int i = 0; i < n; ++i)
    cppCode.replace(QRegularExpression(R"(for\s*\(\$(\w+)\s*=\s*0;\s*\$\1\s*<\s*(\w+);\s*\$\1\+\+\)\s*{)"), "for (int \\1 = 0; \\1 < \\2; ++\\1) {");
    // if/else
    cppCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if (\\1) {");
    cppCode.replace(QRegularExpression(R"(else\s*{)"), "} else {");
    // Remove $ from variable usage
    cppCode.replace(QRegularExpression(R"(\$(\w+))"), "\\1");
    // Remove closing braces
    cppCode.replace(QRegularExpression(R"(}\s*)"), "");
    // Remove semicolons at end of lines (except after std::endl)
    cppCode.replace(QRegularExpression(R"([^l]endl;[^\n]*;)"), "\\1");
    return cppCode;
} 