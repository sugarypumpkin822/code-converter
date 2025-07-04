# CodeTranslator - Qt Project File
# Professional code translation and conversion tool
# Version: 2.0.0
# Copyright (c) 2024 CodeTrans Inc.

# Qt Configuration
QT += core gui widgets network sql xml concurrent

# For Qt6 compatibility
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

# Application settings
TARGET = CodeTranslator
TEMPLATE = app
VERSION = 2.0.0

# Build configuration
CONFIG += c++17 warn_on qt thread

# Platform-specific configurations
win32 {
    CONFIG += console
    RC_ICONS = resources/icons/app.ico
    QMAKE_TARGET_COMPANY = "CodeTrans Inc."
    QMAKE_TARGET_PRODUCT = "CodeTranslator"
    QMAKE_TARGET_DESCRIPTION = "Professional Code Translation Tool"
    QMAKE_TARGET_COPYRIGHT = "Copyright (c) 2024 CodeTrans Inc."
}

macx {
    ICON = resources/icons/app.icns
    QMAKE_INFO_PLIST = Info.plist
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.14
}

unix:!macx {
    # Linux configuration
    target.path = /usr/local/bin
    INSTALLS += target
    
    # Desktop integration
    desktop.files = resources/desktop/codetranslator.desktop
    desktop.path = /usr/share/applications
    INSTALLS += desktop
    
    # Application icons
    icon.files = resources/icons/app.png
    icon.path = /usr/share/pixmaps
    INSTALLS += icon
}

# Compiler flags
QMAKE_CXXFLAGS += -std=c++17 -Wall -Wextra -Wpedantic
QMAKE_CXXFLAGS_RELEASE += -O2 -DNDEBUG
QMAKE_CXXFLAGS_DEBUG += -g -O0 -DDEBUG

# Source files
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    translator.cpp \
    languagemanager.cpp \
    syntaxhighlighter.cpp \
    codeparser.cpp \
    outputgenerator.cpp \
    settingsmanager.cpp \
    projectmanager.cpp \
    pluginmanager.cpp \
    historymanager.cpp \
    filemanager.cpp \
    networkmanager.cpp \
    databasemanager.cpp \
    logger.cpp \
    utils.cpp \
    aboutdialog.cpp \
    preferencesdialog.cpp \
    newprojectdialog.cpp \
    findreplacedialog.cpp \
    progressdialog.cpp \
    licensedialog.cpp \
    updatechecker.cpp \
    crashhandler.cpp \
    widgets/codeeditor.cpp \
    widgets/linenumberarea.cpp \
    widgets/outputpanel.cpp \
    widgets/projecttree.cpp \
    widgets/statusbar.cpp \
    widgets/toolbar.cpp \
    widgets/welcomescreen.cpp \
    parsers/cppparser.cpp \
    parsers/javaparser.cpp \
    parsers/pythonparser.cpp \
    parsers/javascriptparser.cpp \
    parsers/csharpparser.cpp \
    parsers/goparser.cpp \
    parsers/rustparser.cpp \
    parsers/swiftparser.cpp \
    parsers/kotlinparser.cpp \
    parsers/phpparser.cpp \
    generators/cppgenerator.cpp \
    generators/javagenerator.cpp \
    generators/pythongenerator.cpp \
    generators/javascriptgenerator.cpp \
    generators/csharpgenerator.cpp \
    generators/gogenerator.cpp \
    generators/rustgenerator.cpp \
    generators/swiftgenerator.cpp \
    generators/kotlingenerator.cpp \
    generators/phpgenerator.cpp \
    plugins/pluginbase.cpp \
    plugins/formatplugin.cpp \
    plugins/validationplugin.cpp \
    plugins/optimizationplugin.cpp

# Header files
HEADERS += \
    mainwindow.h \
    translator.h \
    languagemanager.h \
    syntaxhighlighter.h \
    codeparser.h \
    outputgenerator.h \
    settingsmanager.h \
    projectmanager.h \
    pluginmanager.h \
    historymanager.h \
    filemanager.h \
    networkmanager.h \
    databasemanager.h \
    logger.h \
    utils.h \
    aboutdialog.h \
    preferencesdialog.h \
    newprojectdialog.h \
    findreplacedialog.h \
    progressdialog.h \
    licensedialog.h \
    updatechecker.h \
    crashhandler.h \
    constants.h \
    version.h \
    widgets/codeeditor.h \
    widgets/linenumberarea.h \
    widgets/outputpanel.h \
    widgets/projecttree.h \
    widgets/statusbar.h \
    widgets/toolbar.h \
    widgets/welcomescreen.h \
    parsers/parserbase.h \
    parsers/cppparser.h \
    parsers/javaparser.h \
    parsers/pythonparser.h \
    parsers/javascriptparser.h \
    parsers/csharpparser.h \
    parsers/goparser.h \
    parsers/rustparser.h \
    parsers/swiftparser.h \
    parsers/kotlinparser.h \
    parsers/phpparser.h \
    generators/generatorbase.h \
    generators/cppgenerator.h \
    generators/javagenerator.h \
    generators/pythongenerator.h \
    generators/javascriptgenerator.h \
    generators/csharpgenerator.h \
    generators/gogenerator.h \
    generators/rustgenerator.h \
    generators/swiftgenerator.h \
    generators/kotlingenerator.h \
    generators/phpgenerator.h \
    plugins/pluginbase.h \
    plugins/formatplugin.h \
    plugins/validationplugin.h \
    plugins/optimizationplugin.h \
    interfaces/iplugin.h \
    interfaces/iparser.h \
    interfaces/igenerator.h

# UI forms
FORMS += \
    mainwindow.ui \
    aboutdialog.ui \
    preferencesdialog.ui \
    newprojectdialog.ui \
    findreplacedialog.ui \
    progressdialog.ui \
    licensedialog.ui \
    widgets/welcomescreen.ui

# Resource files
RESOURCES += \
    resources/main.qrc \
    resources/icons.qrc \
    resources/translations.qrc \
    resources/themes.qrc \
    resources/templates.qrc \
    resources/examples.qrc

# Translation files
TRANSLATIONS += \
    translations/codetranslator_en.ts \
    translations/codetranslator_es.ts \
    translations/codetranslator_fr.ts \
    translations/codetranslator_de.ts \
    translations/codetranslator_it.ts \
    translations/codetranslator_pt.ts \
    translations/codetranslator_ru.ts \
    translations/codetranslator_ja.ts \
    translations/codetranslator_ko.ts \
    translations/codetranslator_zh.ts \
    translations/codetranslator_ar.ts \
    translations/codetranslator_hi.ts

# Include paths
INCLUDEPATH += \
    . \
    widgets \
    parsers \
    generators \
    plugins \
    interfaces \
    third_party/include

# Library dependencies
LIBS += -L$$PWD/third_party/lib

# Third-party libraries
win32:LIBS += -lws2_32 -luser32 -lshell32 -lkernel32 -lgdi32 -ladvapi32
unix:LIBS += -ldl -lpthread

# Debug configuration
CONFIG(debug, debug|release) {
    DEFINES += DEBUG_MODE
    TARGET = $$join(TARGET,,,_debug)
    
    # Debug libraries
    LIBS += -L$$PWD/third_party/lib/debug
    
    # Memory debugging
    QMAKE_CXXFLAGS_DEBUG += -fsanitize=address -fno-omit-frame-pointer
    QMAKE_LFLAGS_DEBUG += -fsanitize=address
}

# Release configuration
CONFIG(release, debug|release) {
    DEFINES += RELEASE_MODE QT_NO_DEBUG_OUTPUT
    
    # Release libraries
    LIBS += -L$$PWD/third_party/lib/release
    
    # Optimization
    QMAKE_CXXFLAGS_RELEASE += -flto
    QMAKE_LFLAGS_RELEASE += -flto
}

# Defines
DEFINES += \
    QT_DEPRECATED_WARNINGS \
    QT_DISABLE_DEPRECATED_BEFORE=0x060000 \
    APP_VERSION=\\\"$$VERSION\\\" \
    APP_NAME=\\\"CodeTranslator\\\" \
    ORGANIZATION_NAME=\\\"CodeTrans Inc.\\\" \
    ORGANIZATION_DOMAIN=\\\"codetrans.com\\\"

# Custom build steps
QMAKE_EXTRA_TARGETS += docs tests package

# Documentation generation
docs.commands = doxygen Doxyfile
docs.depends = FORCE

# Unit tests
tests.commands = cd tests && qmake && make && ./test_runner
tests.depends = FORCE

# Package creation
package.commands = scripts/create_package.sh
package.depends = FORCE

# Install configuration
isEmpty(PREFIX) {
    PREFIX = /usr/local
}

target.path = $$PREFIX/bin
INSTALLS += target

# Desktop file installation
unix:!macx {
    desktop.files = resources/desktop/codetranslator.desktop
    desktop.path = $$PREFIX/share/applications
    INSTALLS += desktop
    
    # Icons
    icons.files = resources/icons/app.png
    icons.path = $$PREFIX/share/pixmaps
    INSTALLS += icons
    
    # Manual pages
    man.files = docs/man/codetranslator.1
    man.path = $$PREFIX/share/man/man1
    INSTALLS += man
}

# macOS bundle configuration
macx {
    # Bundle identifier
    QMAKE_TARGET_BUNDLE_PREFIX = com.codetrans
    
    # Framework search paths
    QMAKE_FRAMEWORK_PATH += /System/Library/Frameworks
    
    # Code signing (if certificates are available)
    exists($$PWD/codesign.pri) {
        include($$PWD/codesign.pri)
    }
}

# PCH (Precompiled Headers) support
CONFIG += precompile_header
PRECOMPILED_HEADER = stable.h

# Subdirectories for organized builds
SUBDIRS = \
    src \
    plugins \
    tests \
    docs

# Clean targets
QMAKE_CLEAN += \
    *.core \
    core \
    moc_*.cpp \
    qrc_*.cpp \
    ui_*.h \
    Makefile* \
    *.o \
    *.a \
    *.so \
    *.dylib \
    *.dll \
    *_debug* \
    *_release*

# Distclean targets
QMAKE_DISTCLEAN += \
    .qmake.stash \
    .qmake.cache \
    *.pro.user* \
    Makefile*

# Custom compiler warnings
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter -Wno-unused-variable

# Enable Qt's plugin system
CONFIG += plugin_bundle

# OpenGL support (if needed for advanced features)
# QT += opengl

# Multimedia support (if needed for audio/video processing)
# QT += multimedia

# Print support
# QT += printsupport

# Web engine support (if needed for documentation viewer)
# QT += webenginewidgets

# Charts support (if needed for statistics)
# QT += charts

# End of project file
