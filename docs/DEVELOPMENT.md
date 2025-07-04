# Developer Guide: CodeTranslator

## Architecture Overview
- Modular C++/Qt codebase
- Main components: GUI (mainwindow), translation engine, plugins, settings, history

## Adding a New Language or Feature
1. Extend the `Translator` class with new translation logic.
2. Add new UI elements if needed (e.g., new language in dropdowns).
3. Update tests and documentation.

## Writing a Plugin
- Inherit from `Translator::TranslatorPlugin`.
- Implement required methods: `pluginName`, `supportedSourceLanguages`, `supportedTargetLanguages`, `translate`, `metadata`.
- Register your plugin in the app or via plugin loader.

## Directory Structure
- `mainwindow.*` - Main GUI window
- `translator.*` - Translation logic and engine
- `docs/` - Documentation and screenshots
- `tests/` - Unit and integration tests

## Testing
- Add tests to the `tests/` directory
- Use Qt Test or your preferred C++ testing framework

## Coding Standards
- Follow Qt/C++ best practices
- Write clear, maintainable, and well-documented code

## Questions?
Open an issue or join the Discussions on GitHub. 