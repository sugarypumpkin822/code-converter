#include <QtTest/QtTest>
#include "translator.h"

class TestPlugin : public QObject {
    Q_OBJECT
private slots:
    void test_plugin_registration() {
        class Dummy : public Translator::TranslatorPlugin {
        public:
            QString pluginName() const override { return "TestPlugin"; }
            QStringList supportedSourceLanguages() const override { return {"Python"}; }
            QStringList supportedTargetLanguages() const override { return {"C++"}; }
            QString translate(const QString& s, const QString& t, const QString& c) override { return "plugin"; }
            Translator::PluginMetadata metadata() const override { return {"TestPlugin", "1.0", "Test", "", QDateTime::currentDateTime()}; }
        };
        Dummy* plugin = new Dummy();
        Translator::registerPlugin(plugin);
        auto plugins = Translator::listPlugins();
        bool found = false;
        for (const auto& meta : plugins) {
            if (meta.name == "TestPlugin") found = true;
        }
        QVERIFY(found);
        Translator::unregisterPlugin(plugin);
        delete plugin;
    }
};

QTEST_MAIN(TestPlugin)
#include "test_plugin.moc" 
