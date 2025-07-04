#include <QString>
#include <QRegularExpression>
#include "PHPToPythonTranslator.h"

QString PHPToPythonTranslator::translate(const QString& code) const {
    QString pyCode = code;
    // echo ...; -> print(...)
    pyCode.replace(QRegularExpression(R"(echo\s+(.*?);)"), "print(\1)");
    // $x = ...; -> x = ... (simple int)
    pyCode.replace(QRegularExpression(R"(\$(\w+)\s*=\s*(\d+);)"), "\1 = \2");
    // $x = "..."; -> x = "..."
    pyCode.replace(QRegularExpression(R"(\$(\w+)\s*=\s*\"(.*?)\";)"), "\1 = '\2'");
    // function func(args) { -> def func(args):
    pyCode.replace(QRegularExpression(R"(function\s+(\w+)\((.*?)\)\s*{)"), "def \1(\2):");
    // for ($i = 0; $i < n; $i++) -> for i in range(n):
    pyCode.replace(QRegularExpression(R"(for\s*\(\$(\w+)\s*=\s*0;\s*\$\2\s*<\s*(\w+);\s*\$\2\+\+\)\s*{)"), "for \2 in range(\3):");
    // if/else
    pyCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if \2:");
    pyCode.replace(QRegularExpression(R"(else\s*{)"), "else:");
    // Remove $ from variable usage
    pyCode.replace(QRegularExpression(R"(\$(\w+))"), "\1");
    // Remove closing braces
    pyCode.replace(QRegularExpression(R"(}\s*)"), "");
    // Remove semicolons
    pyCode.replace(";", "");
    return pyCode;
} 