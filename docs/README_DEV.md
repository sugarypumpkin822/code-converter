# Developer README: CodeTranslator

This document is for developers working on CodeTranslator.

## Quick Build
- Use Qt Creator or run `qmake`/`cmake` and `make`.
- See `scripts/build.sh` for a build script.

## Debugging
- Use Qt Creator's debugger or gdb/lldb.
- Enable debug symbols in your build settings.
- Use `qDebug()` for logging.

## Architecture
- MainWindow: GUI logic and user interaction
- Translator: Core translation engine and plugin system
- Plugins: Extend translation logic
- Settings: QSettings for persistent config
- History: In-memory and file-based translation history

## Adding Features
- Add new slots and UI elements in `mainwindow.*` and `mainwindow.ui`
- Extend `Translator` for new language support
- Add plugins in the `plugins/` directory (planned)

## Testing
- Add tests to `tests/` and run with `scripts/run_tests.sh`

## Documentation
- See `docs/` for API, user, and developer docs

## Questions?
Open an issue or join Discussions on GitHub. 