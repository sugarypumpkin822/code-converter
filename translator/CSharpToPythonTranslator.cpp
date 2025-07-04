#include <QString>
#include <QRegularExpression>
#include "CSharpToPythonTranslator.h"

QString CSharpToPythonTranslator::translate(const QString& code) const {
    QString pyCode = code;
    // Console.WriteLine(...) -> print(...)
    pyCode.replace(QRegularExpression(R"(Console\.WriteLine\((.*?)\);)"), "print(\1)");
    // int assignment
    pyCode.replace(QRegularExpression(R"(int\s+(\w+)\s*=\s*(\d+);)"), "\2 = \3");
    // string assignment
    pyCode.replace(QRegularExpression(R"(string\s+(\w+)\s*=\s*\"(.*?)\";)"), "\1 = '\2'");
    // static void func(args) { -> def func(args):
    pyCode.replace(QRegularExpression(R"(static\s+void\s+(\w+)\((.*?)\)\s*{)"), "def \1(\2):");
    // for (int i = 0; i < n; i++) -> for i in range(n):
    pyCode.replace(QRegularExpression(R"(for\s*\(int\s+(\w+)\s*=\s*0;\s*\2\s*<\s*(\w+);\s*\2\+\+\)\s*{)"), "for \2 in range(\3):");
    // if/else
    pyCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if \2:");
    pyCode.replace(QRegularExpression(R"(else\s*{)"), "else:");
    // Remove closing braces
    pyCode.replace(QRegularExpression(R"(}\s*)"), "");
    // Remove semicolons
    pyCode.replace(";", "");
    return pyCode;
} 