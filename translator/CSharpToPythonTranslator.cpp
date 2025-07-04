#include <QString>
#include <QRegularExpression>
#include "CSharpToPythonTranslator.h"

QString CSharpToPythonTranslator::translate(const QString& code) const {
    QString pyCode = code;
    
    // Namespace to module comments
    pyCode.replace(QRegularExpression(R"(namespace\s+(\w+)\s*{)"), "# Module: \\1");
    pyCode.replace(QRegularExpression(R"(using\s+(\w+(?:\.\w+)*);)"), "# import \\1");
    
    // Class declarations
    pyCode.replace(QRegularExpression(R"(public\s+class\s+(\w+)\s*{)"), "class \\1:");
    pyCode.replace(QRegularExpression(R"(private\s+class\s+(\w+)\s*{)"), "class _\\1:");
    pyCode.replace(QRegularExpression(R"(internal\s+class\s+(\w+)\s*{)"), "class \\1:");
    pyCode.replace(QRegularExpression(R"(abstract\s+class\s+(\w+)\s*{)"), "class \\1(ABC):");
    pyCode.replace(QRegularExpression(R"(sealed\s+class\s+(\w+)\s*{)"), "class \\1:");
    
    // Inheritance
    pyCode.replace(QRegularExpression(R"(:\s*(\w+))"), "(\\1)");
    pyCode.replace(QRegularExpression(R"(:\s*(\w+),\s*(\w+))"), "(\\1, \\2)");
    
    // Constructor
    pyCode.replace(QRegularExpression(R"(public\s+(\w+)\((.*?)\)\s*{)"), "def __init__(self, \\2):");
    
    // Method declarations
    pyCode.replace(QRegularExpression(R"(public\s+static\s+void\s+(\w+)\((.*?)\)\s*{)"), "def \\1(\\2):");
    pyCode.replace(QRegularExpression(R"(private\s+static\s+void\s+(\w+)\((.*?)\)\s*{)"), "def _\\1(\\2):");
    pyCode.replace(QRegularExpression(R"(public\s+void\s+(\w+)\((.*?)\)\s*{)"), "def \\1(self, \\2):");
    pyCode.replace(QRegularExpression(R"(private\s+void\s+(\w+)\((.*?)\)\s*{)"), "def _\\1(self, \\2):");
    pyCode.replace(QRegularExpression(R"(protected\s+void\s+(\w+)\((.*?)\)\s*{)"), "def _\\1(self, \\2):");
    pyCode.replace(QRegularExpression(R"(internal\s+void\s+(\w+)\((.*?)\)\s*{)"), "def \\1(self, \\2):");
    pyCode.replace(QRegularExpression(R"(static\s+void\s+(\w+)\((.*?)\)\s*{)"), "def \\1(\\2):");
    
    // Return type methods
    pyCode.replace(QRegularExpression(R"(public\s+(\w+)\s+(\w+)\((.*?)\)\s*{)"), "def \\2(self, \\3):");
    pyCode.replace(QRegularExpression(R"(private\s+(\w+)\s+(\w+)\((.*?)\)\s*{)"), "def _\\2(self, \\3):");
    pyCode.replace(QRegularExpression(R"(protected\s+(\w+)\s+(\w+)\((.*?)\)\s*{)"), "def _\\2(self, \\3):");
    pyCode.replace(QRegularExpression(R"(static\s+(\w+)\s+(\w+)\((.*?)\)\s*{)"), "def \\2(\\3):");
    
    // Properties to property decorators
    pyCode.replace(QRegularExpression(R"(public\s+(\w+)\s+(\w+)\s*{\s*get;\s*set;\s*})"), 
                   "@property\n    def \\2(self):\n        return self._\\2\n    \n    @\\2.setter\n    def \\2(self, value):\n        self._\\2 = value");
    pyCode.replace(QRegularExpression(R"(public\s+(\w+)\s+(\w+)\s*{\s*get;\s*})"), 
                   "@property\n    def \\2(self):\n        return self._\\2");
    
    // Data types (remove explicit typing)
    pyCode.replace(QRegularExpression(R"(\bstring\b)"), "");
    pyCode.replace(QRegularExpression(R"(\bint\b)"), "");
    pyCode.replace(QRegularExpression(R"(\bbool\b)"), "");
    pyCode.replace(QRegularExpression(R"(\bobject\b)"), "");
    pyCode.replace(QRegularExpression(R"(\bdouble\b)"), "");
    pyCode.replace(QRegularExpression(R"(\bfloat\b)"), "");
    pyCode.replace(QRegularExpression(R"(\bdecimal\b)"), "");
    pyCode.replace(QRegularExpression(R"(\bDateTime\b)"), "datetime");
    pyCode.replace(QRegularExpression(R"(\bTimeSpan\b)"), "timedelta");
    pyCode.replace(QRegularExpression(R"(\bGuid\b)"), "uuid");
    
    // Collections
    pyCode.replace(QRegularExpression(R"(List<\w+>)"), "list");
    pyCode.replace(QRegularExpression(R"(Dictionary<\w+,\s*\w+>)"), "dict");
    pyCode.replace(QRegularExpression(R"(new\s+List<\w+>\(\))"), "[]");
    pyCode.replace(QRegularExpression(R"(new\s+Dictionary<\w+,\s*\w+>\(\))"), "{}");
    
    // Arrays
    pyCode.replace(QRegularExpression(R"(\w+\[\]\s+(\w+))"), "\\1");
    pyCode.replace(QRegularExpression(R"(new\s+\w+\[(\d+)\])"), "[None] * \\1");
    
    // LINQ to list comprehensions and built-ins
    pyCode.replace(QRegularExpression(R"(\.Where\((\w+)\s*=>\s*([^)]+)\))"), "[x for x in collection if \\2]");
    pyCode.replace(QRegularExpression(R"(\.Select\((\w+)\s*=>\s*([^)]+)\))"), "[\\2 for \\1 in collection]");
    pyCode.replace(QRegularExpression(R"(\.ToList\(\))"), "");
    pyCode.replace(QRegularExpression(R"(\.First\(\))"), "[0]");
    pyCode.replace(QRegularExpression(R"(\.Last\(\))"), "[-1]");
    pyCode.replace(QRegularExpression(R"(\.Any\(\))"), "len(collection) > 0");
    pyCode.replace(QRegularExpression(R"(\.Count\(\))"), "len(collection)");
    pyCode.replace(QRegularExpression(R"(\.Sum\(\))"), "sum(collection)");
    pyCode.replace(QRegularExpression(R"(\.Max\(\))"), "max(collection)");
    pyCode.replace(QRegularExpression(R"(\.Min\(\))"), "min(collection)");
    
    // Console operations
    pyCode.replace(QRegularExpression(R"(Console\.WriteLine\((.*?)\);)"), "print(\\1)");
    pyCode.replace(QRegularExpression(R"(Console\.Write\((.*?)\);)"), "print(\\1, end='')");
    pyCode.replace(QRegularExpression(R"(Console\.ReadLine\(\))"), "input()");
    
    // String operations
    pyCode.replace(QRegularExpression(R"(\.ToUpper\(\))"), ".upper()");
    pyCode.replace(QRegularExpression(R"(\.ToLower\(\))"), ".lower()");
    pyCode.replace(QRegularExpression(R"(\.Contains\(([^)]+)\))"), " in ");
    pyCode.replace(QRegularExpression(R"(\.StartsWith\(([^)]+)\))"), ".startswith(\\1)");
    pyCode.replace(QRegularExpression(R"(\.EndsWith\(([^)]+)\))"), ".endswith(\\1)");
    pyCode.replace(QRegularExpression(R"(\.Length)"), "len()");
    pyCode.replace(QRegularExpression(R"(\.Substring\(([^)]+)\))"), "[\\1:]");
    pyCode.replace(QRegularExpression(R"(\.Replace\(([^,]+),\s*([^)]+)\))"), ".replace(\\1, \\2)");
    pyCode.replace(QRegularExpression(R"(\.Trim\(\))"), ".strip()");
    pyCode.replace(QRegularExpression(R"(\.Split\(([^)]+)\))"), ".split(\\1)");
    pyCode.replace(QRegularExpression(R"(\.Join\(([^,]+),\s*([^)]+)\))"), "\\1.join(\\2)");
    
    // String interpolation
    pyCode.replace(QRegularExpression(R"(\$\"([^\"]*{[^}]+}[^\"]*)\")"), "f\"\\1\"");
    
    // Exception handling
    pyCode.replace(QRegularExpression(R"(try\s*{)"), "try:");
    pyCode.replace(QRegularExpression(R"(catch\s*\((\w+)\s+(\w+)\)\s*{)"), "except \\1 as \\2:");
    pyCode.replace(QRegularExpression(R"(catch\s*{)"), "except:");
    pyCode.replace(QRegularExpression(R"(finally\s*{)"), "finally:");
    pyCode.replace(QRegularExpression(R"(throw\s+new\s+(\w+)\(([^)]*)\);)"), "raise \\1(\\2)");
    
    // Literals
    pyCode.replace(QRegularExpression(R"(\btrue\b)"), "True");
    pyCode.replace(QRegularExpression(R"(\bfalse\b)"), "False");
    pyCode.replace(QRegularExpression(R"(\bnull\b)"), "None");
    
    // Variable declarations
    pyCode.replace(QRegularExpression(R"(var\s+(\w+)\s*=\s*([^;]+);)"), "\\1 = \\2");
    pyCode.replace(QRegularExpression(R"(\w+\s+(\w+)\s*=\s*([^;]+);)"), "\\1 = \\2");
    pyCode.replace(QRegularExpression(R"(int\s+(\w+)\s*=\s*(\d+);)"), "\\1 = \\2");
    pyCode.replace(QRegularExpression(R"(string\s+(\w+)\s*=\s*\"(.*?)\";)"), "\\1 = \"\\2\"");
    pyCode.replace(QRegularExpression(R"(bool\s+(\w+)\s*=\s*(True|False);)"), "\\1 = \\2");
    pyCode.replace(QRegularExpression(R"(double\s+(\w+)\s*=\s*([0-9.]+);)"), "\\1 = \\2");
    pyCode.replace(QRegularExpression(R"(float\s+(\w+)\s*=\s*([0-9.]+)f;)"), "\\1 = \\2");
    
    // Control flow
    pyCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if \\1:");
    pyCode.replace(QRegularExpression(R"(else\s+if\s*\((.*?)\)\s*{)"), "elif \\1:");
    pyCode.replace(QRegularExpression(R"(else\s*{)"), "else:");
    pyCode.replace(QRegularExpression(R"(while\s*\((.*?)\)\s*{)"), "while \\1:");
    pyCode.replace(QRegularExpression(R"(for\s*\(int\s+(\w+)\s*=\s*0;\s*\1\s*<\s*(\w+);\s*\1\+\+\)\s*{)"), "for \\1 in range(\\2):");
    pyCode.replace(QRegularExpression(R"(for\s*\(int\s+(\w+)\s*=\s*(\d+);\s*\1\s*<\s*(\w+);\s*\1\+\+\)\s*{)"), "for \\1 in range(\\2, \\3):");
    pyCode.replace(QRegularExpression(R"(for\s*\(int\s+(\w+)\s*=\s*(\d+);\s*\1\s*<\s*(\d+);\s*\1\+\+\)\s*{)"), "for \\1 in range(\\2, \\3):");
    pyCode.replace(QRegularExpression(R"(foreach\s*\((\w+)\s+(\w+)\s+in\s+([^)]+)\)\s*{)"), "for \\2 in \\3:");
    pyCode.replace(QRegularExpression(R"(foreach\s*\(var\s+(\w+)\s+in\s+([^)]+)\)\s*{)"), "for \\1 in \\2:");
    
    // Switch statements to if-elif chains
    pyCode.replace(QRegularExpression(R"(switch\s*\((.*?)\)\s*{)"), "# Switch on \\1");
    pyCode.replace(QRegularExpression(R"(case\s+([^:]+):)"), "if \\1 == switch_var:");
    pyCode.replace(QRegularExpression(R"(default:)"), "else:");
    pyCode.replace(QRegularExpression(R"(break;)"), "pass");
    
    // Operators
    pyCode.replace(QRegularExpression(R"(&&)"), " and ");
    pyCode.replace(QRegularExpression(R"(\|\|)"), " or ");
    pyCode.replace(QRegularExpression(R"(!)"), " not ");
    pyCode.replace(QRegularExpression(R"(==)"), " == ");
    pyCode.replace(QRegularExpression(R"(!=)"), " != ");
    pyCode.replace(QRegularExpression(R"(<=)"), " <= ");
    pyCode.replace(QRegularExpression(R"(>=)"), " >= ");
    
    // Math operations
    pyCode.replace(QRegularExpression(R"(Math\.Abs\(([^)]+)\))"), "abs(\\1)");
    pyCode.replace(QRegularExpression(R"(Math\.Max\(([^,]+),\s*([^)]+)\))"), "max(\\1, \\2)");
    pyCode.replace(QRegularExpression(R"(Math\.Min\(([^,]+),\s*([^)]+)\))"), "min(\\1, \\2)");
    pyCode.replace(QRegularExpression(R"(Math\.Pow\(([^,]+),\s*([^)]+)\))"), "pow(\\1, \\2)");
    pyCode.replace(QRegularExpression(R"(Math\.Sqrt\(([^)]+)\))"), "math.sqrt(\\1)");
    pyCode.replace(QRegularExpression(R"(Math\.Round\(([^)]+)\))"), "round(\\1)");
    pyCode.replace(QRegularExpression(R"(Math\.Floor\(([^)]+)\))"), "math.floor(\\1)");
    pyCode.replace(QRegularExpression(R"(Math\.Ceiling\(([^)]+)\))"), "math.ceil(\\1)");
    pyCode.replace(QRegularExpression(R"(Math\.Sin\(([^)]+)\))"), "math.sin(\\1)");
    pyCode.replace(QRegularExpression(R"(Math\.Cos\(([^)]+)\))"), "math.cos(\\1)");
    pyCode.replace(QRegularExpression(R"(Math\.Tan\(([^)]+)\))"), "math.tan(\\1)");
    pyCode.replace(QRegularExpression(R"(Math\.PI)"), "math.pi");
    pyCode.replace(QRegularExpression(R"(Math\.E)"), "math.e");
    
    // Type casting
    pyCode.replace(QRegularExpression(R"(\(int\)([^;]+))"), "int(\\1)");
    pyCode.replace(QRegularExpression(R"(\(string\)([^;]+))"), "str(\\1)");
    pyCode.replace(QRegularExpression(R"(\(bool\)([^;]+))"), "bool(\\1)");
    pyCode.replace(QRegularExpression(R"(\(double\)([^;]+))"), "float(\\1)");
    pyCode.replace(QRegularExpression(R"(\(float\)([^;]+))"), "float(\\1)");
    
    // Constants
    pyCode.replace(QRegularExpression(R"(const\s+\w+\s+(\w+)\s*=\s*([^;]+);)"), "\\1 = \\2  # constant");
    
    // Access modifiers (remove them)
    pyCode.replace(QRegularExpression(R"(\bpublic\s+)"), "");
    pyCode.replace(QRegularExpression(R"(\bprivate\s+)"), "");
    pyCode.replace(QRegularExpression(R"(\bprotected\s+)"), "");
    pyCode.replace(QRegularExpression(R"(\binternal\s+)"), "");
    pyCode.replace(QRegularExpression(R"(\bstatic\s+)"), "");
    pyCode.replace(QRegularExpression(R"(\bsealed\s+)"), "");
    pyCode.replace(QRegularExpression(R"(\bvirtual\s+)"), "");
    pyCode.replace(QRegularExpression(R"(\boverride\s+)"), "");
    pyCode.replace(QRegularExpression(R"(\babstract\s+)"), "");
    
    // Lambda expressions
    pyCode.replace(QRegularExpression(R"((\w+)\s*=>\s*([^;,)]+))"), "lambda \\1: \\2");
    
    // Delegates to function variables
    pyCode.replace(QRegularExpression(R"(delegate\s+\w+\s+(\w+)\(([^)]*)\);)"), "# \\1 = function(\\2)");
    
    // Events (basic conversion)
    pyCode.replace(QRegularExpression(R"(event\s+\w+\s+(\w+);)"), "# Event: \\1 - use callbacks or observer pattern");
    
    // Attributes to decorators
    pyCode.replace(QRegularExpression(R"(\[(\w+)\])"), "@\\1");
    
    // Generic methods (remove type parameters)
    pyCode.replace(QRegularExpression(R"(<\w+>)"), "");
    
    // Nullable types (remove ? operator)
    pyCode.replace(QRegularExpression(R"((\w+)\?)"), "\\1");
    
    // Using statements to with statements
    pyCode.replace(QRegularExpression(R"(using\s*\(([^)]+)\)\s*{)"), "with \\1:");
    
    // File operations
    pyCode.replace(QRegularExpression(R"(File\.ReadAllText\(([^)]+)\))"), "open(\\1, 'r').read()");
    pyCode.replace(QRegularExpression(R"(File\.WriteAllText\(([^,]+),\s*([^)]+)\))"), "open(\\1, 'w').write(\\2)");
    pyCode.replace(QRegularExpression(R"(File\.ReadAllLines\(([^)]+)\))"), "open(\\1, 'r').readlines()");
    pyCode.replace(QRegularExpression(R"(File\.WriteAllLines\(([^,]+),\s*([^)]+)\))"), "open(\\1, 'w').writelines(\\2)");
    
    // DateTime operations
    pyCode.replace(QRegularExpression(R"(DateTime\.Now)"), "datetime.now()");
    pyCode.replace(QRegularExpression(R"(DateTime\.Today)"), "datetime.today()");
    pyCode.replace(QRegularExpression(R"(DateTime\.Parse\(([^)]+)\))"), "datetime.strptime(\\1, '%Y-%m-%d')");
    
    // Regular expressions
    pyCode.replace(QRegularExpression(R"(Regex\.Match\(([^,]+),\s*([^)]+)\))"), "re.search(\\2, \\1)");
    pyCode.replace(QRegularExpression(R"(Regex\.Replace\(([^,]+),\s*([^,]+),\s*([^)]+)\))"), "re.sub(\\2, \\3, \\1)");
    pyCode.replace(QRegularExpression(R"(Regex\.IsMatch\(([^,]+),\s*([^)]+)\))"), "bool(re.search(\\2, \\1))");
    
    // Convert method calls to function calls for static methods
    pyCode.replace(QRegularExpression(R"((\w+)\.(\w+)\()"), "\\1_\\2(");
    
    // Threading
    pyCode.replace(QRegularExpression(R"(Thread\.Sleep\(([^)]+)\))"), "time.sleep(\\1 / 1000)");
    pyCode.replace(QRegularExpression(R"(Task\.Run\(([^)]+)\))"), "threading.Thread(target=\\1).start()");
    
    // Remove closing braces
    pyCode.replace(QRegularExpression(R"(}\s*)"), "");
    
    // Remove semicolons
    pyCode.replace(";", "");
    
    // Clean up extra whitespace and empty lines
    pyCode.replace(QRegularExpression(R"(\n\s*\n)"), "\n");
    pyCode.replace(QRegularExpression(R"(^\s+)"), "");
    
    // Add necessary imports at the beginning
    QStringList imports;
    if (pyCode.contains("math.")) {
        imports << "import math";
    }
    if (pyCode.contains("datetime.") || pyCode.contains("datetime(")) {
        imports << "from datetime import datetime, timedelta";
    }
    if (pyCode.contains("re.")) {
        imports << "import re";
    }
    if (pyCode.contains("time.sleep")) {
        imports << "import time";
    }
    if (pyCode.contains("threading.")) {
        imports << "import threading";
    }
    if (pyCode.contains("uuid.")) {
        imports << "import uuid";
    }
    if (pyCode.contains("ABC")) {
        imports << "from abc import ABC, abstractmethod";
    }
    if (pyCode.contains("open(")) {
        imports << "import os";
    }
    
    if (!imports.isEmpty()) {
        pyCode = imports.join("\n") + "\n\n" + pyCode;
    }
    
    return pyCode;
}
