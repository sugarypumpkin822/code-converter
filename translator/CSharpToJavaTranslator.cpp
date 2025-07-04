#include "CSharpToJavaTranslator.h"
#include <QRegularExpression>

QString CSharpToJavaTranslator::translate(const QString& code) const {
    QString javaCode = code;
    // Console.WriteLine(...) -> System.out.println(...);
    javaCode.replace(QRegularExpression(R"(Console\.WriteLine\((.*?)\);)"), "System.out.println(\\1);");
    // int assignment
    javaCode.replace(QRegularExpression(R"(int\s+(\w+)\s*=\s*(\d+);)"), "int \\1 = \\2;");
    // string assignment
    javaCode.replace(QRegularExpression(R"(string\s+(\w+)\s*=\s*\"(.*?)\";)"), "String \\1 = \"\\2\";");
    // static void func(args) { -> public static void func(args) {
    javaCode.replace(QRegularExpression(R"(static\s+void\s+(\w+)\((.*?)\)\s*{)"), "public static void \\1(\\2) {");
    // for (int i = 0; i < n; i++)
    // (no change needed, but included for completeness)
    // if/else
    javaCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if (\\1) {");
    javaCode.replace(QRegularExpression(R"(else\s*{)"), "} else {");
    return javaCode;
} 