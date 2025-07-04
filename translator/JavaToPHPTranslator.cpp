#include <QString>
#include <QRegularExpression>
#include "JavaToPHPTranslator.h"

QString JavaToPHPTranslator::translate(const QString& code) const {
    QString phpCode = code;
    // System.out.println(...) -> echo ...;
    phpCode.replace(QRegularExpression(R"(System\.out\.println\((.*?)\);)"), "echo \1;\n");
    // int assignment
    phpCode.replace(QRegularExpression(R"(int\s+(\w+)\s*=\s*(\d+);)"), "$\2 = $\3;");
    // String assignment
    phpCode.replace(QRegularExpression(R"(String\s+(\w+)\s*=\s*\"(.*?)\";)"), "$\2 = \"$\3\";");
    // public static void func(args) { -> function func(args) {
    phpCode.replace(QRegularExpression(R"(public\s+static\s+void\s+(\w+)\((.*?)\)\s*{)"), "function $2($3) {");
    // for (int i = 0; i < n; i++) -> for ($i = 0; $i < n; $i++)
    phpCode.replace(QRegularExpression(R"(for\s*\(int\s+(\w+)\s*=\s*(\d+);\s*\2\s*<\s*(\d+);\s*\2\+\+\)\s*{)"), "for ($$2 = $3; $$2 < $4; $$2++) {");
    // if/else
    phpCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if ($2) {");
    phpCode.replace(QRegularExpression(R"(else\s*{)"), "} else {");
    // Convert Java variable usage to PHP ($var)
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