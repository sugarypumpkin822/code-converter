#include "PythonToCppTranslator.h"
#include <QRegularExpression>

QString PythonToCppTranslator::translate(const QString& code) const {
    QString cppCode = code;
    cppCode.replace(QRegularExpression(R"(print\((.*?)\))"), "std::cout << \\1 << std::endl;");
    cppCode.replace(QRegularExpression(R"((\w+)\s*=\s*(\d+))"), "int \\1 = \\2;");
    cppCode.replace(QRegularExpression(R"((\w+)\s*=\s*['\"](.*?)['\"])") , "std::string \\1 = \"\\2\";");
    cppCode.replace(QRegularExpression(R"(def\s+(\w+)\((.*?)\):)"), "void \\1(\\2) {");
    cppCode.replace(QRegularExpression(R"(for\s+(\w+)\s+in\s+range\((.*?)\):)"), "for (int \\1 = 0; \\1 < \\2; ++\\1) {");
    cppCode.replace(QRegularExpression(R"(if\s+(.*?):)"), "if (\\1) {");
    cppCode.replace(QRegularExpression(R"(elif\s+(.*?):)"), "} else if (\\1) {");
    cppCode.replace(QRegularExpression(R"(else:)"), "} else {");
    cppCode.replace(QRegularExpression(R"(\n\s*)"), "\n    ");
    return cppCode;
} 