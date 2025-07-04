#include "CSharpToJavaTranslator.h"
#include <QRegularExpression>
#include <QStringList>

QString CSharpToJavaTranslator::translate(const QString& code) const {
    QString javaCode = code;
    
    // Namespace handling
    javaCode.replace(QRegularExpression(R"(namespace\s+(\w+)\s*{)"), "package \\1;\n");
    javaCode.replace(QRegularExpression(R"(using\s+(\w+(?:\.\w+)*);)"), "import \\1.*;");
    javaCode.replace(QRegularExpression(R"(using\s+static\s+(\w+(?:\.\w+)*);)"), "import static \\1.*;");
    
    // Class declarations
    javaCode.replace(QRegularExpression(R"(public\s+class\s+(\w+)\s*{)"), "public class \\1 {");
    javaCode.replace(QRegularExpression(R"(private\s+class\s+(\w+)\s*{)"), "private class \\1 {");
    javaCode.replace(QRegularExpression(R"(internal\s+class\s+(\w+)\s*{)"), "class \\1 {");
    javaCode.replace(QRegularExpression(R"(abstract\s+class\s+(\w+)\s*{)"), "abstract class \\1 {");
    javaCode.replace(QRegularExpression(R"(sealed\s+class\s+(\w+)\s*{)"), "final class \\1 {");
    
    // Interface declarations
    javaCode.replace(QRegularExpression(R"(public\s+interface\s+(\w+)\s*{)"), "public interface \\1 {");
    javaCode.replace(QRegularExpression(R"(internal\s+interface\s+(\w+)\s*{)"), "interface \\1 {");
    
    // Inheritance
    javaCode.replace(QRegularExpression(R"(:\s*(\w+))"), "extends \\1");
    javaCode.replace(QRegularExpression(R"(:\s*(\w+),\s*(\w+))"), "extends \\1 implements \\2");
    
    // Properties
    javaCode.replace(QRegularExpression(R"(public\s+(\w+)\s+(\w+)\s*{\s*get;\s*set;\s*})"), "private \\1 \\2;\n    public \\1 get\\2() { return \\2; }\n    public void set\\2(\\1 value) { this.\\2 = value; }");
    javaCode.replace(QRegularExpression(R"(public\s+(\w+)\s+(\w+)\s*{\s*get;\s*})"), "private \\1 \\2;\n    public \\1 get\\2() { return \\2; }");
    
    // Auto-properties with initializers
    javaCode.replace(QRegularExpression(R"(public\s+(\w+)\s+(\w+)\s*{\s*get;\s*set;\s*}\s*=\s*([^;]+);)"), "private \\1 \\2 = \\3;\n    public \\1 get\\2() { return \\2; }\n    public void set\\2(\\1 value) { this.\\2 = value; }");
    
    // Method declarations
    javaCode.replace(QRegularExpression(R"(public\s+static\s+void\s+(\w+)\((.*?)\)\s*{)"), "public static void \\1(\\2) {");
    javaCode.replace(QRegularExpression(R"(private\s+static\s+void\s+(\w+)\((.*?)\)\s*{)"), "private static void \\1(\\2) {");
    javaCode.replace(QRegularExpression(R"(public\s+void\s+(\w+)\((.*?)\)\s*{)"), "public void \\1(\\2) {");
    javaCode.replace(QRegularExpression(R"(private\s+void\s+(\w+)\((.*?)\)\s*{)"), "private void \\1(\\2) {");
    javaCode.replace(QRegularExpression(R"(protected\s+void\s+(\w+)\((.*?)\)\s*{)"), "protected void \\1(\\2) {");
    javaCode.replace(QRegularExpression(R"(internal\s+void\s+(\w+)\((.*?)\)\s*{)"), "void \\1(\\2) {");
    
    // Return type methods
    javaCode.replace(QRegularExpression(R"(public\s+(\w+)\s+(\w+)\((.*?)\)\s*{)"), "public \\1 \\2(\\3) {");
    javaCode.replace(QRegularExpression(R"(private\s+(\w+)\s+(\w+)\((.*?)\)\s*{)"), "private \\1 \\2(\\3) {");
    javaCode.replace(QRegularExpression(R"(protected\s+(\w+)\s+(\w+)\((.*?)\)\s*{)"), "protected \\1 \\2(\\3) {");
    javaCode.replace(QRegularExpression(R"(static\s+(\w+)\s+(\w+)\((.*?)\)\s*{)"), "public static \\1 \\2(\\3) {");
    
    // Constructor
    javaCode.replace(QRegularExpression(R"(public\s+(\w+)\((.*?)\)\s*{)"), "public \\1(\\2) {");
    
    // Data types
    javaCode.replace(QRegularExpression(R"(\bstring\b)"), "String");
    javaCode.replace(QRegularExpression(R"(\bbool\b)"), "boolean");
    javaCode.replace(QRegularExpression(R"(\bobject\b)"), "Object");
    javaCode.replace(QRegularExpression(R"(\bdecimal\b)"), "BigDecimal");
    javaCode.replace(QRegularExpression(R"(\bDateTime\b)"), "LocalDateTime");
    javaCode.replace(QRegularExpression(R"(\bTimeSpan\b)"), "Duration");
    javaCode.replace(QRegularExpression(R"(\bGuid\b)"), "UUID");
    
    // Nullable types
    javaCode.replace(QRegularExpression(R"((\w+)\?)"), "\\1");
    
    // Arrays
    javaCode.replace(QRegularExpression(R"((\w+)\[\]\s+(\w+))"), "\\1[] \\2");
    javaCode.replace(QRegularExpression(R"(new\s+(\w+)\[(\d+)\])"), "new \\1[\\2]");
    
    // Collections
    javaCode.replace(QRegularExpression(R"(List<(\w+)>)"), "List<\\1>");
    javaCode.replace(QRegularExpression(R"(Dictionary<(\w+),\s*(\w+)>)"), "Map<\\1, \\2>");
    javaCode.replace(QRegularExpression(R"(new\s+List<(\w+)>\(\))"), "new ArrayList<\\1>()");
    javaCode.replace(QRegularExpression(R"(new\s+Dictionary<(\w+),\s*(\w+)>\(\))"), "new HashMap<\\1, \\2>()");
    
    // LINQ to Stream API (basic cases)
    javaCode.replace(QRegularExpression(R"(\.Where\((\w+)\s*=>\s*([^)]+)\))"), ".stream().filter(\\1 -> \\2)");
    javaCode.replace(QRegularExpression(R"(\.Select\((\w+)\s*=>\s*([^)]+)\))"), ".stream().map(\\1 -> \\2)");
    javaCode.replace(QRegularExpression(R"(\.ToList\(\))"), ".collect(Collectors.toList())");
    javaCode.replace(QRegularExpression(R"(\.First\(\))"), ".findFirst().orElse(null)");
    javaCode.replace(QRegularExpression(R"(\.Any\(\))"), ".findAny().isPresent()");
    
    // Console operations
    javaCode.replace(QRegularExpression(R"(Console\.WriteLine\((.*?)\);)"), "System.out.println(\\1);");
    javaCode.replace(QRegularExpression(R"(Console\.Write\((.*?)\);)"), "System.out.print(\\1);");
    javaCode.replace(QRegularExpression(R"(Console\.ReadLine\(\))"), "scanner.nextLine()");
    
    // String operations
    javaCode.replace(QRegularExpression(R"(\.ToUpper\(\))"), ".toUpperCase()");
    javaCode.replace(QRegularExpression(R"(\.ToLower\(\))"), ".toLowerCase()");
    javaCode.replace(QRegularExpression(R"(\.Contains\(([^)]+)\))"), ".contains(\\1)");
    javaCode.replace(QRegularExpression(R"(\.StartsWith\(([^)]+)\))"), ".startsWith(\\1)");
    javaCode.replace(QRegularExpression(R"(\.EndsWith\(([^)]+)\))"), ".endsWith(\\1)");
    javaCode.replace(QRegularExpression(R"(\.Length)"), ".length()");
    javaCode.replace(QRegularExpression(R"(\.Substring\(([^)]+)\))"), ".substring(\\1)");
    javaCode.replace(QRegularExpression(R"(\.Replace\(([^,]+),\s*([^)]+)\))"), ".replace(\\1, \\2)");
    
    // String interpolation
    javaCode.replace(QRegularExpression(R"(\$\"([^\"]*{[^}]+}[^\"]*)\")"), "String.format(\"\\1\")");
    
    // Exception handling
    javaCode.replace(QRegularExpression(R"(try\s*{)"), "try {");
    javaCode.replace(QRegularExpression(R"(catch\s*\((\w+)\s+(\w+)\)\s*{)"), "catch (\\1 \\2) {");
    javaCode.replace(QRegularExpression(R"(catch\s*{)"), "catch (Exception e) {");
    javaCode.replace(QRegularExpression(R"(finally\s*{)"), "finally {");
    javaCode.replace(QRegularExpression(R"(throw\s+new\s+(\w+)\(([^)]*)\);)"), "throw new \\1(\\2);");
    
    // Access modifiers
    javaCode.replace(QRegularExpression(R"(\binternal\b)"), "");
    javaCode.replace(QRegularExpression(R"(\bsealed\b)"), "final");
    javaCode.replace(QRegularExpression(R"(\bvirtual\b)"), "");
    javaCode.replace(QRegularExpression(R"(\boverride\b)"), "@Override");
    javaCode.replace(QRegularExpression(R"(\babstract\b)"), "abstract");
    
    // Literals
    javaCode.replace(QRegularExpression(R"(\btrue\b)"), "true");
    javaCode.replace(QRegularExpression(R"(\bfalse\b)"), "false");
    javaCode.replace(QRegularExpression(R"(\bnull\b)"), "null");
    
    // Variable declarations
    javaCode.replace(QRegularExpression(R"(var\s+(\w+)\s*=\s*([^;]+);)"), "auto \\1 = \\2;");
    javaCode.replace(QRegularExpression(R"(int\s+(\w+)\s*=\s*(\d+);)"), "int \\1 = \\2;");
    javaCode.replace(QRegularExpression(R"(string\s+(\w+)\s*=\s*\"(.*?)\";)"), "String \\1 = \"\\2\";");
    javaCode.replace(QRegularExpression(R"(bool\s+(\w+)\s*=\s*(true|false);)"), "boolean \\1 = \\2;");
    javaCode.replace(QRegularExpression(R"(double\s+(\w+)\s*=\s*([0-9.]+);)"), "double \\1 = \\2;");
    javaCode.replace(QRegularExpression(R"(float\s+(\w+)\s*=\s*([0-9.]+)f;)"), "float \\1 = \\2f;");
    
    // Control flow
    javaCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if (\\1) {");
    javaCode.replace(QRegularExpression(R"(else\s+if\s*\((.*?)\)\s*{)"), "else if (\\1) {");
    javaCode.replace(QRegularExpression(R"(else\s*{)"), "else {");
    javaCode.replace(QRegularExpression(R"(while\s*\((.*?)\)\s*{)"), "while (\\1) {");
    javaCode.replace(QRegularExpression(R"(for\s*\((.*?)\)\s*{)"), "for (\\1) {");
    javaCode.replace(QRegularExpression(R"(foreach\s*\((\w+)\s+(\w+)\s+in\s+([^)]+)\)\s*{)"), "for (\\1 \\2 : \\3) {");
    javaCode.replace(QRegularExpression(R"(switch\s*\((.*?)\)\s*{)"), "switch (\\1) {");
    javaCode.replace(QRegularExpression(R"(case\s+([^:]+):)"), "case \\1:");
    javaCode.replace(QRegularExpression(R"(default:)"), "default:");
    javaCode.replace(QRegularExpression(R"(break;)"), "break;");
    
    // Operators
    javaCode.replace(QRegularExpression(R"(&&)"), "&&");
    javaCode.replace(QRegularExpression(R"(\|\|)"), "||");
    javaCode.replace(QRegularExpression(R"(!)"), "!");
    javaCode.replace(QRegularExpression(R"(==)"), "==");
    javaCode.replace(QRegularExpression(R"(!=)"), "!=");
    javaCode.replace(QRegularExpression(R"(<=)"), "<=");
    javaCode.replace(QRegularExpression(R"(>=)"), ">=");
    
    // Math operations
    javaCode.replace(QRegularExpression(R"(Math\.Abs\(([^)]+)\))"), "Math.abs(\\1)");
    javaCode.replace(QRegularExpression(R"(Math\.Max\(([^,]+),\s*([^)]+)\))"), "Math.max(\\1, \\2)");
    javaCode.replace(QRegularExpression(R"(Math\.Min\(([^,]+),\s*([^)]+)\))"), "Math.min(\\1, \\2)");
    javaCode.replace(QRegularExpression(R"(Math\.Pow\(([^,]+),\s*([^)]+)\))"), "Math.pow(\\1, \\2)");
    javaCode.replace(QRegularExpression(R"(Math\.Sqrt\(([^)]+)\))"), "Math.sqrt(\\1)");
    javaCode.replace(QRegularExpression(R"(Math\.Round\(([^)]+)\))"), "Math.round(\\1)");
    
    // Type casting
    javaCode.replace(QRegularExpression(R"(\((\w+)\)([^;]+))"), "(\\1)\\2");
    
    // Constants
    javaCode.replace(QRegularExpression(R"(const\s+(\w+)\s+(\w+)\s*=\s*([^;]+);)"), "static final \\1 \\2 = \\3;");
    
    // Events (basic conversion)
    javaCode.replace(QRegularExpression(R"(event\s+(\w+)\s+(\w+);)"), "// Event: \\1 \\2 - Convert to Observer pattern");
    
    // Delegates (basic conversion)
    javaCode.replace(QRegularExpression(R"(delegate\s+(\w+)\s+(\w+)\(([^)]*)\);)"), "// Delegate: \\1 \\2(\\3) - Convert to functional interface");
    
    // Lambda expressions (basic)
    javaCode.replace(QRegularExpression(R"((\w+)\s*=>\s*([^;,)]+))"), "\\1 -> \\2");
    
    // Generic methods
    javaCode.replace(QRegularExpression(R"(public\s+(\w+)<(\w+)>\s+(\w+)\(([^)]*)\))"), "public <\\2> \\1 \\3(\\4)");
    
    // Attributes to Annotations
    javaCode.replace(QRegularExpression(R"(\[(\w+)\])"), "@\\1");
    
    // Add necessary imports at the beginning
    if (javaCode.contains("List<") || javaCode.contains("ArrayList<")) {
        javaCode = "import java.util.*;\n" + javaCode;
    }
    if (javaCode.contains("LocalDateTime") || javaCode.contains("Duration")) {
        javaCode = "import java.time.*;\n" + javaCode;
    }
    if (javaCode.contains("UUID")) {
        javaCode = "import java.util.UUID;\n" + javaCode;
    }
    if (javaCode.contains("BigDecimal")) {
        javaCode = "import java.math.BigDecimal;\n" + javaCode;
    }
    if (javaCode.contains("scanner.nextLine()")) {
        javaCode = "import java.util.Scanner;\n" + javaCode;
        javaCode.replace("scanner.nextLine()", "new Scanner(System.in).nextLine()");
    }
    if (javaCode.contains("Collectors.toList()")) {
        javaCode = "import java.util.stream.Collectors;\n" + javaCode;
    }
    
    return javaCode;
}
