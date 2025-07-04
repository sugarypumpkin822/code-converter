#include "JavaToCppTranslator.h"
#include <QRegularExpression>

QString JavaToCppTranslator::translate(const QString& code) const {
    QString cppCode = code;
    // System.out.println(...) -> std::cout << ... << std::endl;
    cppCode.replace(QRegularExpression(R"(System\.out\.println\((.*?)\);)"), "std::cout << \\1 << std::endl;");
    // int assignment
    cppCode.replace(QRegularExpression(R"(int\s+(\w+)\s*=\s*(\d+);)"), "int \\1 = \\2;");
    // String assignment
    cppCode.replace(QRegularExpression(R"(String\s+(\w+)\s*=\s*\"(.*?)\";)"), "std::string \\1 = \"\\2\";");
    // public static void func(args) { -> void func(args) {
    cppCode.replace(QRegularExpression(R"(public\s+static\s+void\s+(\w+)\((.*?)\)\s*{)"), "void \\1(\\2) {");
    // for (int i = 0; i < n; i++) -> for (int i = 0; i < n; i++)
    // (no change needed, but included for completeness)
    // if/else
    cppCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if (\\1) {");
    cppCode.replace(QRegularExpression(R"(else\s*{)"), "} else {");
    return cppCode;
} 