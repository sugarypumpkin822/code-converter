#include <QtTest/QtTest>
#include "translator.h"

class TestTranslator : public QObject {
    Q_OBJECT
private slots:
    void test_identity() {
        QString code = "print('Hello')";
        QCOMPARE(Translator::translate("Python", "Python", code), code);
    }
    void test_python_to_cpp() {
        QString code = "print('Hello')";
        QString result = Translator::translate("Python", "C++", code);
        QVERIFY(result.contains("std::cout"));
    }
};

QTEST_MAIN(TestTranslator)
#include "test_translator.moc" 
