#include <QString>
#include <QRegularExpression>
#include "CSharpToPHPTranslator.h"

QString CSharpToPHPTranslator::translate(const QString& code) const {
    QString phpCode = code;
    // Console.WriteLine(...) -> echo ...;
    phpCode.replace(QRegularExpression(R"(Console\.WriteLine\((.*?)\);)"), "echo \1;\n");
    // int assignment
    phpCode.replace(QRegularExpression(R"(int\s+(\w+)\s*=\s*(\d+);)"), "$\2 = $\3;");
    // string assignment
    phpCode.replace(QRegularExpression(R"(string\s+(\w+)\s*=\s*\"(.*?)\";)"), "$\2 = \"$\3\";");
    // static void func(args) { -> function func(args) {
    phpCode.replace(QRegularExpression(R"(static\s+void\s+(\w+)\((.*?)\)\s*{)"), "function $2($3) {");
    // for (int i = 0; i < n; i++) -> for ($i = 0; $i < n; $i++)
    phpCode.replace(QRegularExpression(R"(for\s*\(int\s+(\w+)\s*=\s*(\d+);\s*\2\s*<\s*(\d+);\s*\2\+\+\)\s*{)"), "for ($$2 = $3; $$2 < $4; $$2++) {");
    // if/else
    phpCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if ($2) {");
    phpCode.replace(QRegularExpression(R"(else\s*{)"), "} else {");
    // Convert C# variable usage to PHP ($var)
    phpCode.replace(QRegularExpression(R"(\b(\w+)\b)"), "$$1");
    // Remove semicolons at end of lines (except after echo)
    phpCode.replace(QRegularExpression(R"([^e]cho [^;]+);"), "\1");
    // Remove closing braces
    phpCode.replace(QRegularExpression(R"(}\s*)"), "");
    // Add PHP tags if not present
    if (!phpCode.trimmed().startsWith("<?php")) {
        phpCode = "<?php\n" + phpCode;
    }
    if (!phpCode.trimmed().endsWith("?>")) {
        phpCode += "\n?>";
    }
    return phpCode;
} 