cmake_minimum_required(VERSION 3.10)
project(CodeTranslator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.ui
    translator.cpp
    translator/TranslatorFactory.cpp
    translator/CppToJavaScriptTranslator.cpp
    translator/CppToJavaTranslator.cpp
    translator/CppToPythonTranslator.cpp
    translator/CSharpToJavaTranslator.cpp
    translator/JavaScriptToCppTranslator.cpp
    translator/JavaScriptToJavaTranslator.cpp
    translator/JavaScriptToPythonTranslator.cpp
    translator/JavaToCppTranslator.cpp
    translator/JavaToCSharpTranslator.cpp
    translator/JavaToPythonTranslator.cpp
    translator/PythonToCppTranslator.cpp
    translator/PythonToCSharpTranslator.cpp
    translator/PythonToJavaScriptTranslator.cpp
    translator/PythonToJavaTranslator.cpp
    translator/JavaToPHPTranslator.cpp
    translator/PHPToJavaTranslator.cpp
    translator/PHPToPythonTranslator.cpp
    translator/PHPToCppTranslator.cpp
    translator/PHPToCSharpTranslator.cpp
    translator/CSharpToPHPTranslator.cpp
    translator/CSharpToPythonTranslator.cpp
    translator/CppToPHPTranslator.cpp
)

set(HEADERS
    mainwindow.h
    translator.h
    translator/TranslatorBase.h
    translator/TranslatorFactory.h
    translator/CppToJavaTranslator.h
    translator/CppToPythonTranslator.h
    translator/CSharpToJavaTranslator.h
    translator/JavaScriptToCppTranslator.h
    translator/JavaScriptToJavaTranslator.h
    translator/JavaScriptToPythonTranslator.h
    translator/JavaToCppTranslator.h
    translator/JavaToCSharpTranslator.h
    translator/JavaToPythonTranslator.h
    translator/JavaToPHPTranslator.h
    translator/PythonToCppTranslator.h
    translator/PythonToCSharpTranslator.h
    translator/PythonToJavaScriptTranslator.h
    translator/PythonToJavaTranslator.h
    translator/PHPToJavaTranslator.h
    translator/PHPToPythonTranslator.h
    translator/PHPToCppTranslator.h
    translator/PHPToCSharpTranslator.h
    translator/CSharpToPHPTranslator.h
    translator/CSharpToPythonTranslator.h
    translator/CppToPHPTranslator.h
)

# set(UIS
#     mainwindow.ui
# )

# qt6_wrap_ui(UI_HEADERS ${UIS})

add_executable(CodeTranslator ${SOURCES} ${HEADERS})
target_link_libraries(CodeTranslator Qt6::Widgets) 