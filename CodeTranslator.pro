QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodeTranslator
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    translator.cpp

HEADERS += \
    mainwindow.h \
    translator.h

FORMS += \
    mainwindow.ui 