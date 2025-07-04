#include "PythonToJavaScriptTranslator.h"
#include <QRegularExpression>

QString PythonToJavaScriptTranslator::translate(const QString& code) const {
    QString jsCode = code;
    // print() -> console.log(...);
    jsCode.replace(QRegularExpression(R"(print\((.*?)\))"), "console.log(\\1);");
    // let assignment
    jsCode.replace(QRegularExpression(R"((\w+)\s*=\s*(\d+))"), "let \\1 = \\2;");
    // string assignment
    jsCode.replace(QRegularExpression(R"((\w+)\s*=\s*['\"](.*?)['\"])") , "let \\1 = \"\\2\";");
    // def func(args): -> function func(args) {
    jsCode.replace(QRegularExpression(R"(def\s+(\w+)\((.*?)\):)"), "function \\1(\\2) {");
    // for i in range(n): -> for (let i = 0; i < n; i++) {
    jsCode.replace(QRegularExpression(R"(for\s+(\w+)\s+in\s+range\((.*?)\):)"), "for (let \\1 = 0; \\1 < \\2; \\1++) {");
    // if/elif/else
    jsCode.replace(QRegularExpression(R"(if\s+(.*?):)"), "if (\\1) {");
    jsCode.replace(QRegularExpression(R"(elif\s+(.*?):)"), "} else if (\\1) {");
    jsCode.replace(QRegularExpression(R"(else:)"), "} else {");
    return jsCode;
} 