# Plugins Guide: CodeTranslator

## What are Plugins?
Plugins extend the translation engine with new languages, rules, or features.

## Writing a Plugin
- Inherit from `Translator::TranslatorPlugin`.
- Implement required methods: `pluginName`, `supportedSourceLanguages`, `supportedTargetLanguages`, `translate`, `metadata`.
- Build as a shared library (planned: dynamic loading).

## Installing Plugins
- Place plugin libraries in the `plugins/` directory.
- Use the Settings tab or Tools menu to enable/disable plugins.

## Managing Plugins
- View loaded plugins in the Settings tab.
- Use menu actions to reload or unload plugins.

## Example
See `DummyPlugin` in `translator.cpp` for a basic example. 