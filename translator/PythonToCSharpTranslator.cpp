#include <QString>
#include <QRegularExpression>
#include "PythonToCSharpTranslator.h"

QString PythonToCSharpTranslator::translate(const QString& code) const {
    QString csCode = code;
    // print(...) -> Console.WriteLine(...);
    csCode.replace(QRegularExpression(R"(print\((.*?)\))"), "Console.WriteLine($2);");
    // int assignment
    csCode.replace(QRegularExpression(R"((\w+)\s*=\s*(\d+))"), "int $1 = $2;");
    // string assignment
    csCode.replace(QRegularExpression(R"((\w+)\s*=\s*['\"](.*?)['\"])"), "string $1 = \"$2\";");
    // def func(args): -> static void func(args) {
    csCode.replace(QRegularExpression(R"(def\s+(\w+)\((.*?)\):)"), "static void $1($2) {");
    // for i in range(n): -> for (int i = 0; i < n; i++)
    csCode.replace(QRegularExpression(R"(for\s+(\w+)\s+in\s+range\((.*?)\):)"), "for (int $2 = 0; $2 < $3; $2++) {");
    // if/elif/else
    csCode.replace(QRegularExpression(R"(if\s+(.*?):)"), "if ($2) {");
    csCode.replace(QRegularExpression(R"(elif\s+(.*?):)"), "} else if ($2) {");
    csCode.replace(QRegularExpression(R"(else:)"), "} else {");
    // Add closing braces for blocks (not perfect, would need indentation analysis)
    // Remove Python indentation (replace leading spaces with nothing)
    csCode.replace(QRegularExpression(R"(^[ ]+)"), "");
    return csCode;
} 