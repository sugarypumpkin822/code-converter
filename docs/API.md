# API Documentation: CodeTranslator

## Translator Class
- `translate(sourceLang, targetLang, code)`: Translate code from one language to another.
- `translateVariables`, `translateFunctions`, ...: Helper functions for code constructs.
- `registerPlugin(plugin)`, `listPlugins()`: Plugin management.
- `getCodeMetrics(code)`: Get code statistics.
- `batchTranslate(...)`: Batch translation support.
- See `translator.h` for the full API.

## MainWindow Class
- Slots for translation, file I/O, history, feedback, plugins, etc.
- See `mainwindow.h` for details.

## Plugins
- Inherit from `Translator::TranslatorPlugin`.
- Implement required methods: `pluginName`, `supportedSourceLanguages`, etc.

## Settings
- Use `QSettings` for persistent configuration.

## More
- See `docs/DEVELOPMENT.md` for developer and extension info. 