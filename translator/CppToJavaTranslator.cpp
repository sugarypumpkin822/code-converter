#include "CppToJavaTranslator.h"
#include <QRegularExpression>

QString CppToJavaTranslator::translate(const QString& code) const {
    QString javaCode = code;
    // std::cout << ... << std::endl; -> System.out.println(...);
    javaCode.replace(QRegularExpression(R"(std::cout\s*<<\s*(.*?)\s*<<\s*std::endl;)"), "System.out.println(\\1);");
    // int assignment
    javaCode.replace(QRegularExpression(R"(int\s+(\w+)\s*=\s*(\d+);)"), "int \\1 = \\2;");
    // string assignment
    javaCode.replace(QRegularExpression(R"(std::string\s+(\w+)\s*=\s*\"(.*?)\";)"), "String \\1 = \"\\2\";");
    // void func(args) { -> public static void func(args) {
    javaCode.replace(QRegularExpression(R"(void\s+(\w+)\((.*?)\)\s*{)"), "public static void \\1(\\2) {");
    // for (int i = 0; i < n; ++i) -> for (int i = 0; i < n; i++)
    javaCode.replace(QRegularExpression(R"(for\s*\(int\s+(\w+)\s*=\s*(\d+);\s*\\1\s*<\s*(\d+);\s*\+\+\\1\))"), "for (int \\1 = \\2; \\1 < \\3; \\1++)");
    // if/else
    javaCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if (\\1) {");
    javaCode.replace(QRegularExpression(R"(else\s*{)"), "} else {");
    // Remove extra braces/semicolons if needed
    return javaCode;
} 