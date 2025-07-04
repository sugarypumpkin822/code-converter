#include <QString>
#include <QRegularExpression>
#include "CppToPHPTranslator.h"

QString CppToPHPTranslator::translate(const QString& code) const {
    QString phpCode = code;
    // std::cout << ... << std::endl; -> echo ...;
    phpCode.replace(QRegularExpression(R"(std::cout\s*<<\s*(.*?)\s*<<\s*std::endl;)"), "echo \\1;\n");
    // int assignment
    phpCode.replace(QRegularExpression(R"(int\s+(\w+)\s*=\s*(\d+);)"), "$\\1 = \\2;");
    // string assignment
    phpCode.replace(QRegularExpression(R"(std::string\s+(\w+)\s*=\s*\"(.*?)\";)"), "$\\1 = \"\\2\";");
    // void func(args) { -> function func(args) {
    phpCode.replace(QRegularExpression(R"(void\s+(\w+)\((.*?)\)\s*{)"), "function \\1(\\2) {");
    // for (int i = 0; i < n; ++i) -> for ($i = 0; $i < n; $i++)
    phpCode.replace(QRegularExpression(R"(for\s*\(int\s+(\w+)\s*=\s*(\d+);\s*\1\s*<\s*(\d+);\s*\+\+\1\)\s*{)"), "for ($\\1 = \\2; $\\1 < \\3; $\\1++) {");
    // if/else
    phpCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if (\\1) {");
    phpCode.replace(QRegularExpression(R"(else\s*{)"), "} else {");
    // Remove closing braces
    phpCode.replace(QRegularExpression(R"(}\s*)"), "");
    // Remove semicolons at end of lines (except after echo)
    // This regex is problematic, so let's comment it out for now
    // phpCode.replace(QRegularExpression(R"([^e]cho [^;]+);"), "\\1");
    // Add PHP tags if not present
    if (!phpCode.trimmed().startsWith("<?php")) {
        phpCode = "<?php\n" + phpCode;
    }
    if (!phpCode.trimmed().endsWith("?>")) {
        phpCode += "\n?>";
    }
    return phpCode;
} 
