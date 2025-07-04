#include <QString>
#include <QRegularExpression>
#include "PHPToCSharpTranslator.h"

QString PHPToCSharpTranslator::translate(const QString& code) const {
    QString csCode = code;
    // echo ...; -> Console.WriteLine(...);
    csCode.replace(QRegularExpression(R"(echo\s+(.*?);)"), "Console.WriteLine(\\1);");
    // $x = ...; -> int x = ...; (simple int)
    csCode.replace(QRegularExpression(R"(\$(\w+)\s*=\s*(\d+);)"), "int \\1 = \\2;");
    // $x = "..."; -> string x = "...";
    csCode.replace(QRegularExpression(R"(\$(\w+)\s*=\s*\"(.*?)\";)"), "string \\1 = \"\\2\";");
    // function func(args) { -> static void func(args) {
    csCode.replace(QRegularExpression(R"(function\s+(\w+)\((.*?)\)\s*{)"), "static void \\1(\\2) {");
    // for ($i = 0; $i < n; $i++) -> for (int i = 0; i < n; i++)
    csCode.replace(QRegularExpression(R"(for\s*\(\$(\w+)\s*=\s*0;\s*\$\1\s*<\s*(\w+);\s*\$\1\+\+\)\s*{)"), "for (int \\1 = 0; \\1 < \\2; \\1++) {");
    // if/else
    csCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if (\\1) {");
    csCode.replace(QRegularExpression(R"(else\s*{)"), "} else {");
    // Remove $ from variable usage
    csCode.replace(QRegularExpression(R"(\$(\w+))"), "\\1");
    // Remove closing braces
    csCode.replace(QRegularExpression(R"(}\s*)"), "");
    // Remove semicolons at end of lines (except after Console.WriteLine)
    // This regex is not robust, but let's keep it simple for now
    // (We won't try to match and remove semicolons after Console.WriteLine)
    return csCode;
} 