#include "CppToJavaScriptTranslator.h"
#include <QRegularExpression>
#include <QString>

QString CppToJavaScriptTranslator::translate(const QString& code) const {
    QString jsCode = code;
    // std::cout << ... << std::endl; -> console.log(...);
    jsCode.replace(QRegularExpression(R"(std::cout\s*<<\s*(.*?)\s*<<\s*std::endl;)") , "console.log(\1);");
    // int/auto x = ...; -> let x = ...;
    jsCode.replace(QRegularExpression(R"((int|auto)\s+(\w+)\s*=\s*(.*?);)"), "let \2 = \3;");
    // void func(args) { -> function func(args) {
    jsCode.replace(QRegularExpression(R"(void\s+(\w+)\((.*?)\)\s*{)"), "function \1(\2) {");
    // for (int i = 0; i < n; i++) { -> for (let i = 0; i < n; i++) {
    jsCode.replace(QRegularExpression(R"(for\s*\(int\s+(\w+)\s*=\s*0;\s*\1\s*<\s*(\w+);\s*\1\+\+\)\s*{)"), "for (let \1 = 0; \1 < \2; \1++) {");
    // if/else
    jsCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if (\1) {");
    jsCode.replace(QRegularExpression(R"(else\s*{)"), "} else {");
    // Remove closing braces (for single-line blocks)
    // (In real use, would need block analysis)
    return jsCode;
} 