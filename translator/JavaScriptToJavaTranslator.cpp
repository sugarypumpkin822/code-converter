#include "JavaScriptToJavaTranslator.h"
#include <QRegularExpression>

QString JavaScriptToJavaTranslator::translate(const QString& code) const {
    QString javaCode = code;
    // console.log() -> System.out.println(...);
    javaCode.replace(QRegularExpression(R"(console\.log\((.*?)\);?)"), "System.out.println(\\1);");
    // int assignment
    javaCode.replace(QRegularExpression(R"((let|var|const)\s+(\w+)\s*=\s*(\d+);)"), "int \\2 = \\3;");
    // string assignment
    javaCode.replace(QRegularExpression(R"((let|var|const)\s+(\w+)\s*=\s*['\"](.*?)['\"];)"), "String \\2 = \"\\3\";");
    // function func(args) { -> public static void func(args) {
    javaCode.replace(QRegularExpression(R"(function\s+(\w+)\((.*?)\)\s*{)"), "public static void \\1(\\2) {");
    // for (let i = 0; i < n; i++) -> for (int i = 0; i < n; i++)
    javaCode.replace(QRegularExpression(R"(for\s*\(let\s+(\w+)\s*=\s*(\d+);\s*\\1\s*<\s*(\d+);\s*\\1\+\+\)\s*{)"), "for (int \\1 = \\2; \\1 < \\3; \\1++) {");
    // if/else
    javaCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if (\\1) {");
    javaCode.replace(QRegularExpression(R"(else\s*{)"), "} else {");
    return javaCode;
} 