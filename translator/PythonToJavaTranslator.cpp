#include "PythonToJavaTranslator.h"
#include <QRegularExpression>

QString PythonToJavaTranslator::translate(const QString& code) const {
    QString javaCode = code;
    // print(...) -> System.out.println(...);
    javaCode.replace(QRegularExpression(R"(print\((.*?)\))"), "System.out.println(\1);");
    // Variable assignment (int)
    javaCode.replace(QRegularExpression(R"(^(w+)\s*=\s*(\d+)$)"), "int \1 = \2;");
    // Variable assignment (string)
    javaCode.replace(QRegularExpression(R"(^(w+)\s*=\s*'(.*?)'$)"), "String \1 = \2;");
    // def func(args): -> public static void func(args) {
    javaCode.replace(QRegularExpression(R"(def\s+(\w+)\((.*?)\):)"), "public static void \1(\2) {");
    // for i in range(n): -> for (int i = 0; i < n; i++) {
    javaCode.replace(QRegularExpression(R"(for\s+(\w+)\s+in\s+range\((\w+)\):)"), "for (int \1 = 0; \1 < \2; \1++) {");
    // if/else
    javaCode.replace(QRegularExpression(R"(if\s+(.*):)"), "if (\1) {");
    javaCode.replace(QRegularExpression(R"(else:)"), "} else {");
    // Add closing braces for blocks (not perfect, but stub)
    // (In real use, would need indentation analysis)
    return javaCode;
} 