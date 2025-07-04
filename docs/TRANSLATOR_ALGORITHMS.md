# Translator Algorithms

This document describes the algorithms and strategies used by CodeTranslator for code translation.

## General Strategy
- Parse input code using regular expressions and language-specific rules.
- Build an intermediate representation (planned: AST).
- Apply translation rules for variables, functions, loops, etc.
- Generate output code in the target language.

## Language-Specific Notes
- **Python to C++:** Maps print to std::cout, def to void, etc.
- **JavaScript to C++:** Maps console.log to std::cout, function to void, etc.
- **C++ to Python:** Maps std::cout to print, int to variable assignment, etc.

## Planned Improvements
- Use full parsers and ASTs for more robust translation.
- Add error handling and code formatting.
- Support for more complex constructs (classes, templates, etc.).

## References
- See `translator.cpp` and `translator.h` for implementation details. 