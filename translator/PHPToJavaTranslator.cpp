#include <QString>
#include <QRegularExpression>
#include "PHPToJavaTranslator.h"

QString PHPToJavaTranslator::translate(const QString& code) const {
    QString javaCode = code;
    // echo ...; -> System.out.println(...);
    javaCode.replace(QRegularExpression(R"(echo\s+(.*?);)"), "System.out.println(\1);");
    // $x = ...; -> int x = ...; (simple int)
    javaCode.replace(QRegularExpression(R"(\$(\w+)\s*=\s*(\d+);)"), "int \1 = \2;");
    // $x = "..."; -> String x = "...";
    javaCode.replace(QRegularExpression(R"(\$(\w+)\s*=\s*\"(.*?)\";)"), "String \1 = \"\2\";");
    // function func(args) { -> public static void func(args) {
    javaCode.replace(QRegularExpression(R"(function\s+(\w+)\((.*?)\)\s*{)"), "public static void \1(\2) {");
    // for ($i = 0; $i < n; $i++) -> for (int i = 0; i < n; i++)
    javaCode.replace(QRegularExpression(R"(for\s*\(\$(\w+)\s*=\s*(\d+);\s*\$\1\s*<\s*(\d+);\s*\$\1\+\+\)\s*{)"), "for (int \1 = \2; \1 < \3; \1++) {");
    // if/else
    javaCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if (\2) {");
    javaCode.replace(QRegularExpression(R"(else\s*{)"), "} else {");
    // Remove $ from variable usage
    javaCode.replace(QRegularExpression(R"(\$(\w+))"), "\1");
    // Remove closing braces
    javaCode.replace(QRegularExpression(R"(}\s*)"), "");
    // Remove semicolons at end of lines (except after println) - removed problematic regex
    return javaCode;
} 