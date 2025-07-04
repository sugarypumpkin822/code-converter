#include <QString>
#include <QRegularExpression>
#include "CSharpToPHPTranslator.h"

QString CSharpToPHPTranslator::translate(const QString& code) const {
    QString phpCode = code;
    
    // Add PHP opening tag if not present
    if (!phpCode.trimmed().startsWith("<?php")) {
        phpCode = "<?php\n" + phpCode;
    }
    
    // Namespace handling
    phpCode.replace(QRegularExpression(R"(namespace\s+(\w+)\s*{)"), "namespace \\1;\n");
    phpCode.replace(QRegularExpression(R"(using\s+(\w+(?:\.\w+)*);)"), "use \\1;");
    
    // Class declarations
    phpCode.replace(QRegularExpression(R"(public\s+class\s+(\w+)\s*{)"), "class \\1 {");
    phpCode.replace(QRegularExpression(R"(private\s+class\s+(\w+)\s*{)"), "class \\1 {");
    phpCode.replace(QRegularExpression(R"(internal\s+class\s+(\w+)\s*{)"), "class \\1 {");
    phpCode.replace(QRegularExpression(R"(abstract\s+class\s+(\w+)\s*{)"), "abstract class \\1 {");
    phpCode.replace(QRegularExpression(R"(sealed\s+class\s+(\w+)\s*{)"), "final class \\1 {");
    
    // Interface declarations
    phpCode.replace(QRegularExpression(R"(public\s+interface\s+(\w+)\s*{)"), "interface \\1 {");
    phpCode.replace(QRegularExpression(R"(internal\s+interface\s+(\w+)\s*{)"), "interface \\1 {");
    
    // Inheritance
    phpCode.replace(QRegularExpression(R"(:\s*(\w+))"), "extends \\1");
    phpCode.replace(QRegularExpression(R"(:\s*(\w+),\s*(\w+))"), "extends \\1 implements \\2");
    
    // Constructor
    phpCode.replace(QRegularExpression(R"(public\s+(\w+)\((.*?)\)\s*{)"), "public function __construct(\\2) {");
    
    // Method declarations
    phpCode.replace(QRegularExpression(R"(public\s+static\s+void\s+(\w+)\((.*?)\)\s*{)"), "public static function \\1(\\2) {");
    phpCode.replace(QRegularExpression(R"(private\s+static\s+void\s+(\w+)\((.*?)\)\s*{)"), "private static function \\1(\\2) {");
    phpCode.replace(QRegularExpression(R"(public\s+void\s+(\w+)\((.*?)\)\s*{)"), "public function \\1(\\2) {");
    phpCode.replace(QRegularExpression(R"(private\s+void\s+(\w+)\((.*?)\)\s*{)"), "private function \\1(\\2) {");
    phpCode.replace(QRegularExpression(R"(protected\s+void\s+(\w+)\((.*?)\)\s*{)"), "protected function \\1(\\2) {");
    phpCode.replace(QRegularExpression(R"(internal\s+void\s+(\w+)\((.*?)\)\s*{)"), "public function \\1(\\2) {");
    phpCode.replace(QRegularExpression(R"(static\s+void\s+(\w+)\((.*?)\)\s*{)"), "public static function \\1(\\2) {");
    
    // Return type methods
    phpCode.replace(QRegularExpression(R"(public\s+(\w+)\s+(\w+)\((.*?)\)\s*{)"), "public function \\2(\\3) {");
    phpCode.replace(QRegularExpression(R"(private\s+(\w+)\s+(\w+)\((.*?)\)\s*{)"), "private function \\2(\\3) {");
    phpCode.replace(QRegularExpression(R"(protected\s+(\w+)\s+(\w+)\((.*?)\)\s*{)"), "protected function \\2(\\3) {");
    phpCode.replace(QRegularExpression(R"(static\s+(\w+)\s+(\w+)\((.*?)\)\s*{)"), "public static function \\2(\\3) {");
    
    // Properties to getter/setter methods
    phpCode.replace(QRegularExpression(R"(public\s+(\w+)\s+(\w+)\s*{\s*get;\s*set;\s*})"), 
                   "private $\\2;\n    public function get\\2() { return $this->\\2; }\n    public function set\\2($value) { $this->\\2 = $value; }");
    phpCode.replace(QRegularExpression(R"(public\s+(\w+)\s+(\w+)\s*{\s*get;\s*})"), 
                   "private $\\2;\n    public function get\\2() { return $this->\\2; }");
    
    // Variable declarations with type conversion
    phpCode.replace(QRegularExpression(R"(var\s+(\w+)\s*=\s*([^;]+);)"), "$\\1 = \\2;");
    phpCode.replace(QRegularExpression(R"(int\s+(\w+)\s*=\s*(\d+);)"), "$\\1 = \\2;");
    phpCode.replace(QRegularExpression(R"(string\s+(\w+)\s*=\s*\"(.*?)\";)"), "$\\1 = \"\\2\";");
    phpCode.replace(QRegularExpression(R"(bool\s+(\w+)\s*=\s*(true|false);)"), "$\\1 = \\2;");
    phpCode.replace(QRegularExpression(R"(double\s+(\w+)\s*=\s*([0-9.]+);)"), "$\\1 = \\2;");
    phpCode.replace(QRegularExpression(R"(float\s+(\w+)\s*=\s*([0-9.]+)f;)"), "$\\1 = \\2;");
    phpCode.replace(QRegularExpression(R"(decimal\s+(\w+)\s*=\s*([0-9.]+);)"), "$\\1 = \\2;");
    
    // Field declarations
    phpCode.replace(QRegularExpression(R"(public\s+(\w+)\s+(\w+);)"), "public $\\2;");
    phpCode.replace(QRegularExpression(R"(private\s+(\w+)\s+(\w+);)"), "private $\\2;");
    phpCode.replace(QRegularExpression(R"(protected\s+(\w+)\s+(\w+);)"), "protected $\\2;");
    phpCode.replace(QRegularExpression(R"(static\s+(\w+)\s+(\w+);)"), "public static $\\2;");
    
    // Arrays
    phpCode.replace(QRegularExpression(R"((\w+)\[\]\s+(\w+))"), "$\\2"); // array declaration
    phpCode.replace(QRegularExpression(R"(new\s+(\w+)\[(\d+)\])"), "array_fill(0, \\2, null)");
    phpCode.replace(QRegularExpression(R"(new\s+(\w+)\[\])"), "array()");
    
    // Collections
    phpCode.replace(QRegularExpression(R"(List<\w+>)"), "array");
    phpCode.replace(QRegularExpression(R"(Dictionary<\w+,\s*\w+>)"), "array");
    phpCode.replace(QRegularExpression(R"(new\s+List<\w+>\(\))"), "array()");
    phpCode.replace(QRegularExpression(R"(new\s+Dictionary<\w+,\s*\w+>\(\))"), "array()");
    
    // LINQ equivalents
    phpCode.replace(QRegularExpression(R"(\.Where\((\w+)\s*=>\s*([^)]+)\))"), "array_filter(\\1, function($\\1) { return \\2; })");
    phpCode.replace(QRegularExpression(R"(\.Select\((\w+)\s*=>\s*([^)]+)\))"), "array_map(function($\\1) { return \\2; }, \\1)");
    phpCode.replace(QRegularExpression(R"(\.ToList\(\))"), "");
    phpCode.replace(QRegularExpression(R"(\.First\(\))"), "[0]");
    phpCode.replace(QRegularExpression(R"(\.Last\(\))"), "[count($array) - 1]");
    phpCode.replace(QRegularExpression(R"(\.Any\(\))"), "count($array) > 0");
    phpCode.replace(QRegularExpression(R"(\.Count\(\))"), "count($array)");
    phpCode.replace(QRegularExpression(R"(\.Length)"), "count($array)");
    phpCode.replace(QRegularExpression(R"(\.Sum\(\))"), "array_sum($array)");
    phpCode.replace(QRegularExpression(R"(\.Max\(\))"), "max($array)");
    phpCode.replace(QRegularExpression(R"(\.Min\(\))"), "min($array)");
    
    // Console operations
    phpCode.replace(QRegularExpression(R"(Console\.WriteLine\((.*?)\);)"), "echo \\1 . PHP_EOL;");
    phpCode.replace(QRegularExpression(R"(Console\.Write\((.*?)\);)"), "echo \\1;");
    phpCode.replace(QRegularExpression(R"(Console\.ReadLine\(\))"), "trim(fgets(STDIN))");
    
    // String operations
    phpCode.replace(QRegularExpression(R"(\.ToUpper\(\))"), "strtoupper()");
    phpCode.replace(QRegularExpression(R"(\.ToLower\(\))"), "strtolower()");
    phpCode.replace(QRegularExpression(R"(\.Contains\(([^)]+)\))"), "strpos($string, \\1) !== false");
    phpCode.replace(QRegularExpression(R"(\.StartsWith\(([^)]+)\))"), "strpos($string, \\1) === 0");
    phpCode.replace(QRegularExpression(R"(\.EndsWith\(([^)]+)\))"), "substr($string, -strlen(\\1)) === \\1");
    phpCode.replace(QRegularExpression(R"(\.Length)"), "strlen($string)");
    phpCode.replace(QRegularExpression(R"(\.Substring\(([^)]+)\))"), "substr($string, \\1)");
    phpCode.replace(QRegularExpression(R"(\.Replace\(([^,]+),\s*([^)]+)\))"), "str_replace(\\1, \\2, $string)");
    phpCode.replace(QRegularExpression(R"(\.Trim\(\))"), "trim($string)");
    phpCode.replace(QRegularExpression(R"(\.Split\(([^)]+)\))"), "explode(\\1, $string)");
    phpCode.replace(QRegularExpression(R"(\.Join\(([^,]+),\s*([^)]+)\))"), "implode(\\1, \\2)");
    
    // String interpolation
    phpCode.replace(QRegularExpression(R"(\$\"([^\"]*{[^}]+}[^\"]*)\")"), "\"\\1\"");
    phpCode.replace(QRegularExpression(R"({([^}]+)})"), "\" . \\1 . \"");
    
    // Exception handling
    phpCode.replace(QRegularExpression(R"(try\s*{)"), "try {");
    phpCode.replace(QRegularExpression(R"(catch\s*\((\w+)\s+(\w+)\)\s*{)"), "catch (\\1 $\\2) {");
    phpCode.replace(QRegularExpression(R"(catch\s*{)"), "catch (Exception $e) {");
    phpCode.replace(QRegularExpression(R"(finally\s*{)"), "finally {");
    phpCode.replace(QRegularExpression(R"(throw\s+new\s+(\w+)\(([^)]*)\);)"), "throw new \\1(\\2);");
    
    // Literals
    phpCode.replace(QRegularExpression(R"(\btrue\b)"), "true");
    phpCode.replace(QRegularExpression(R"(\bfalse\b)"), "false");
    phpCode.replace(QRegularExpression(R"(\bnull\b)"), "null");
    
    // Control flow
    phpCode.replace(QRegularExpression(R"(if\s*\((.*?)\)\s*{)"), "if (\\1) {");
    phpCode.replace(QRegularExpression(R"(else\s+if\s*\((.*?)\)\s*{)"), "elseif (\\1) {");
    phpCode.replace(QRegularExpression(R"(else\s*{)"), "else {");
    phpCode.replace(QRegularExpression(R"(while\s*\((.*?)\)\s*{)"), "while (\\1) {");
    phpCode.replace(QRegularExpression(R"(for\s*\(int\s+(\w+)\s*=\s*0;\s*\1\s*<\s*(\w+);\s*\1\+\+\)\s*{)"), "for ($\\1 = 0; $\\1 < \\2; $\\1++) {");
    phpCode.replace(QRegularExpression(R"(for\s*\(int\s+(\w+)\s*=\s*(\d+);\s*\1\s*<\s*(\w+);\s*\1\+\+\)\s*{)"), "for ($\\1 = \\2; $\\1 < \\3; $\\1++) {");
    phpCode.replace(QRegularExpression(R"(for\s*\(int\s+(\w+)\s*=\s*(\d+);\s*\1\s*<\s*(\d+);\s*\1\+\+\)\s*{)"), "for ($\\1 = \\2; $\\1 < \\3; $\\1++) {");
    phpCode.replace(QRegularExpression(R"(foreach\s*\((\w+)\s+(\w+)\s+in\s+([^)]+)\)\s*{)"), "foreach (\\3 as $\\2) {");
    phpCode.replace(QRegularExpression(R"(foreach\s*\(var\s+(\w+)\s+in\s+([^)]+)\)\s*{)"), "foreach (\\2 as $\\1) {");
    
    // Switch statements
    phpCode.replace(QRegularExpression(R"(switch\s*\((.*?)\)\s*{)"), "switch (\\1) {");
    phpCode.replace(QRegularExpression(R"(case\s+([^:]+):)"), "case \\1:");
    phpCode.replace(QRegularExpression(R"(default:)"), "default:");
    phpCode.replace(QRegularExpression(R"(break;)"), "break;");
    
    // Operators
    phpCode.replace(QRegularExpression(R"(&&)"), "&&");
    phpCode.replace(QRegularExpression(R"(\|\|)"), "||");
    phpCode.replace(QRegularExpression(R"(!)"), "!");
    phpCode.replace(QRegularExpression(R"(==)"), "==");
    phpCode.replace(QRegularExpression(R"(!=)"), "!=");
    phpCode.replace(QRegularExpression(R"(<=)"), "<=");
    phpCode.replace(QRegularExpression(R"(>=)"), ">=");
    
    // Math operations
    phpCode.replace(QRegularExpression(R"(Math\.Abs\(([^)]+)\))"), "abs(\\1)");
    phpCode.replace(QRegularExpression(R"(Math\.Max\(([^,]+),\s*([^)]+)\))"), "max(\\1, \\2)");
    phpCode.replace(QRegularExpression(R"(Math\.Min\(([^,]+),\s*([^)]+)\))"), "min(\\1, \\2)");
    phpCode.replace(QRegularExpression(R"(Math\.Pow\(([^,]+),\s*([^)]+)\))"), "pow(\\1, \\2)");
    phpCode.replace(QRegularExpression(R"(Math\.Sqrt\(([^)]+)\))"), "sqrt(\\1)");
    phpCode.replace(QRegularExpression(R"(Math\.Floor\(([^)]+)\))"), "floor(\\1)");
    phpCode.replace(QRegularExpression(R"(Math\.Ceiling\(([^)]+)\))"), "ceil(\\1)");
    phpCode.replace(QRegularExpression(R"(Math\.Round\(([^)]+)\))"), "round(\\1)");
    phpCode.replace(QRegularExpression(R"(Math\.Sin\(([^)]+)\))"), "sin(\\1)");
    phpCode.replace(QRegularExpression(R"(Math\.Cos\(([^)]+)\))"), "cos(\\1)");
    phpCode.replace(QRegularExpression(R"(Math\.Tan\(([^)]+)\))"), "tan(\\1)");
    phpCode.replace(QRegularExpression(R"(Math\.PI)"), "M_PI");
    phpCode.replace(QRegularExpression(R"(Math\.E)"), "M_E");
    
    // DateTime operations
    phpCode.replace(QRegularExpression(R"(DateTime\.Now)"), "new DateTime()");
    phpCode.replace(QRegularExpression(R"(DateTime\.Today)"), "new DateTime('today')");
    phpCode.replace(QRegularExpression(R"(DateTime\.Parse\(([^)]+)\))"), "new DateTime(\\1)");
    phpCode.replace(QRegularExpression(R"(\.AddDays\(([^)]+)\))"), "->add(new DateInterval('P' . \\1 . 'D'))");
    phpCode.replace(QRegularExpression(R"(\.AddMonths\(([^)]+)\))"), "->add(new DateInterval('P' . \\1 . 'M'))");
    phpCode.replace(QRegularExpression(R"(\.AddYears\(([^)]+)\))"), "->add(new DateInterval('P' . \\1 . 'Y'))");
    phpCode.replace(QRegularExpression(R"(\.ToString\(\"([^\"]+)\"\))"), "->format('\\1')");
    
    // File operations
    phpCode.replace(QRegularExpression(R"(File\.ReadAllText\(([^)]+)\))"), "file_get_contents(\\1)");
    phpCode.replace(QRegularExpression(R"(File\.WriteAllText\(([^,]+),\s*([^)]+)\))"), "file_put_contents(\\1, \\2)");
    phpCode.replace(QRegularExpression(R"(File\.ReadAllLines\(([^)]+)\))"), "file(\\1, FILE_IGNORE_NEW_LINES)");
    phpCode.replace(QRegularExpression(R"(File\.WriteAllLines\(([^,]+),\s*([^)]+)\))"), "file_put_contents(\\1, implode(PHP_EOL, \\2))");
    phpCode.replace(QRegularExpression(R"(File\.Exists\(([^)]+)\))"), "file_exists(\\1)");
    phpCode.replace(QRegularExpression(R"(File\.Delete\(([^)]+)\))"), "unlink(\\1)");
    phpCode.replace(QRegularExpression(R"(Directory\.Exists\(([^)]+)\))"), "is_dir(\\1)");
    phpCode.replace(QRegularExpression(R"(Directory\.CreateDirectory\(([^)]+)\))"), "mkdir(\\1, 0777, true)");
    phpCode.replace(QRegularExpression(R"(Path\.Combine\(([^,]+),\s*([^)]+)\))"), "\\1 . DIRECTORY_SEPARATOR . \\2");
    
    // Type conversions
    phpCode.replace(QRegularExpression(R"(Convert\.ToInt32\(([^)]+)\))"), "(int)\\1");
    phpCode.replace(QRegularExpression(R"(Convert\.ToDouble\(([^)]+)\))"), "(double)\\1");
    phpCode.replace(QRegularExpression(R"(Convert\.ToString\(([^)]+)\))"), "(string)\\1");
    phpCode.replace(QRegularExpression(R"(Convert\.ToBoolean\(([^)]+)\))"), "(bool)\\1");
    phpCode.replace(QRegularExpression(R"(int\.Parse\(([^)]+)\))"), "(int)\\1");
    phpCode.replace(QRegularExpression(R"(double\.Parse\(([^)]+)\))"), "(double)\\1");
    phpCode.replace(QRegularExpression(R"(bool\.Parse\(([^)]+)\))"), "(bool)\\1");
    phpCode.replace(QRegularExpression(R"(\.ToString\(\))"), "");
    
    // Access modifiers and keywords
    phpCode.replace(QRegularExpression(R"(\bthis\.)"), "$this->");
    phpCode.replace(QRegularExpression(R"(\bbase\.)"), "parent::");
    phpCode.replace(QRegularExpression(R"(\bstatic\s+)"), "static ");
    phpCode.replace(QRegularExpression(R"(\boverride\s+)"), "");
    phpCode.replace(QRegularExpression(R"(\bvirtual\s+)"), "");
    phpCode.replace(QRegularExpression(R"(\babstract\s+)"), "abstract ");
    phpCode.replace(QRegularExpression(R"(\bsealed\s+)"), "final ");
    phpCode.replace(QRegularExpression(R"(\bpartial\s+)"), "");
    phpCode.replace(QRegularExpression(R"(\bconst\s+)"), "const ");
    phpCode.replace(QRegularExpression(R"(\breadonly\s+)"), "");
    
    // Lambda expressions (basic)
    phpCode.replace(QRegularExpression(R"((\w+)\s*=>\s*([^;,)]+))"), "function($\\1) { return \\2; }");
    
    // Generic type cleanup
    phpCode.replace(QRegularExpression(R"(<[^>]+>)"), "");
    
    // Variable references (add $ prefix to variables)
    phpCode.replace(QRegularExpression(R"(\b(?<!->)(?<!\$)(\w+)(?=\s*[=+\-*/%<>!&|]))"), "$\\1");
    phpCode.replace(QRegularExpression(R"(\b(?<!->)(?<!\$)(\w+)(?=\s*\())"), "$\\1");
    
    // Clean up any double $ signs
    phpCode.replace(QRegularExpression(R"(\$\$)"), "$");
    
    // Clean up extra whitespace and normalize formatting
    phpCode.replace(QRegularExpression(R"(\n\s*\n)"), "\n");
    phpCode.replace(QRegularExpression(R"(^\s+)"), "");
    phpCode.replace(QRegularExpression(R"(\s+$)"), "");
    
    return phpCode;
}
