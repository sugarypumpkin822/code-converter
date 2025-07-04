#include "JavaToPythonTranslator.h"
#include <QRegularExpression>

QString JavaToPythonTranslator::translate(const QString& code) const {
    QString pyCode = code;
    // System.out.println(...) -> print(...)
    pyCode.replace(QRegularExpression(R"(System\.out\.println\((.*?)\);)"), "print(\1)");
    // int assignment
    pyCode.replace(QRegularExpression(R"(int\s+(\w+)\s*=\s*(\d+);)"), "\1 = \2");
    // String assignment
    pyCode.replace(QRegularExpression(R"(String\s+(\w+)\s*=\s*\"(.*?)\";)"), "\1 = '\2'");
    // public static void func(args) { -> def func(args):
    pyCode.replace(QRegularExpression(R"(public\s+static\s+void\s+(\w+)\((.*?)\)\s*{)"), "def \1(\2):");
    // for (int i = 0; i < n; i++) { -> for i in range(n):
    pyCode.replace(QRegularExpression(R"(for\s*\(int\s+(\w+)\s*=\s*0;\s*\1\s*<\s*(\w+);\s*\1\+\+\)\s*{)"), "for \1 in range(\2):");
    // if/else
    pyCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if \1:");
    pyCode.replace(QRegularExpression(R"(else\s*{)"), "else:");
    // Remove closing braces
    pyCode.replace(QRegularExpression(R"(}\s*)"), "");
    return pyCode;
} 