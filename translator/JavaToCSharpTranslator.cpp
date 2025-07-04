#include "JavaToCSharpTranslator.h"
#include <QRegularExpression>

QString JavaToCSharpTranslator::translate(const QString& code) const {
    QString csCode = code;
    // System.out.println(...) -> Console.WriteLine(...);
    csCode.replace(QRegularExpression(R"(System\.out\.println\((.*?)\);)"), "Console.WriteLine(\\1);");
    // int assignment
    csCode.replace(QRegularExpression(R"(int\s+(\w+)\s*=\s*(\d+);)"), "int \\1 = \\2;");
    // String assignment
    csCode.replace(QRegularExpression(R"(String\s+(\w+)\s*=\s*\"(.*?)\";)"), "string \\1 = \"\\2\";");
    // public static void func(args) { -> static void func(args) {
    csCode.replace(QRegularExpression(R"(public\s+static\s+void\s+(\w+)\((.*?)\)\s*{)"), "static void \\1(\\2) {");
    // for (int i = 0; i < n; i++)
    // (no change needed, but included for completeness)
    // if/else
    csCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if (\\1) {");
    csCode.replace(QRegularExpression(R"(else\s*{)"), "} else {");
    return csCode;
} 