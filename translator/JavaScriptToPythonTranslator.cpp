#include "JavaScriptToPythonTranslator.h"
#include <QRegularExpression>

QString JavaScriptToPythonTranslator::translate(const QString& code) const {
    QString pyCode = code;
    // console.log() -> print(...)
    pyCode.replace(QRegularExpression(R"(console\.log\((.*?)\);?)"), "print(\\1)");
    // let/var/const assignment
    pyCode.replace(QRegularExpression(R"((let|var|const)\s+(\w+)\s*=\s*(\d+);)"), "\\2 = \\3");
    // string assignment
    pyCode.replace(QRegularExpression(R"((let|var|const)\s+(\w+)\s*=\s*['\"](.*?)['\"];)"), "\\2 = \"\\3\"");
    // function func(args) { -> def func(args):
    pyCode.replace(QRegularExpression(R"(function\s+(\w+)\((.*?)\)\s*{)"), "def \\1(\\2):");
    // for (let i = 0; i < n; i++) -> for i in range(0, n):
    pyCode.replace(QRegularExpression(R"(for\s*\(let\s+(\w+)\s*=\s*(\d+);\s*\\2\s*<\s*(\d+);\s*\\2\+\+\)\s*{)"), "for \\1 in range(\\2, \\3):");
    // if/else
    pyCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if \\1:");
    pyCode.replace(QRegularExpression(R"(else\s*{)"), "else:");
    // Remove braces and semicolons
    pyCode.replace(QRegularExpression(R"(}|{)"), "");
    pyCode.replace(";", "");
    return pyCode;
} 