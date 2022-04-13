# libtrashcan
libtrashcan is a cross-platform C library for moving files and directories to the trashcan. 

## Supported Operating Systems
- Linux
- FreeBSD, OpenBSD, NetBSD
- Windows Vista, Windows Server 2008 and later versions
- macOS

## Why is libtrashcan useful?
When you are developing a software in C that allows to view, edit and save files, you may also want to provide the functionality to delete files. Implementing file deletion with the function specified by POSIX allows cross-platform development. However, `remove()` and `rmdir()` happen to permanently delete files and directories. If your software is only supposed to move the files to the system's trashcan / recycling bin, then libtrashcan can simplify the cross-platform development, as it implements the soft delete functionality for you.

## How does the library implement a trashcan?
For Linux and *BSD the library partially implements the [FreeDesktop.org trash specification v1.0](https://specifications.freedesktop.org/trash-spec/trashspec-1.0.html). On Windows it uses the `IFileOperation` interface and also handles COM initialization. The `NSFileManager` is utilized on macOS.

## API
The function `int trashcan_soft_delete(const char *path)` is provided on all platforms. It takes a path to a file or directory, tries to move it to the trashcan and returns a status code. Additional platform dependent functions with different signatures are provided, e.g. to control COM initialization on Windows. The complete API is documented in the [trashcan.h](src/trashcan.h) file. An example application that uses libtrashcan is provided with [example.c](example.c).

## Compilation
In order to use libtrashcan you need to include `trashcan.h` in your source code, build and link the library. An example project is provided that demonstrates this with CMake. Note that on macOS it is required to link the Core Foundation and Cocoa framework.

The example project is a CLI application that takes a path to a file or directory as an argument and tries to move it to the trash. It can be build by executing the following commands on your terminal/shell/command line if you have CMake and a compiler is installed:

```
mkdir build
cd ./build
cmake ..
cmake --build . --config Release
```

## License
The project is distributed under the [MIT license](./LICENSE).

## Contribute
The library is in early development and the goal is to reach a mature state. If you'd like to contribute, check the [issue tracker](https://github.com/robertguetzkow/libtrashcan/issues) or submit [pull requests](https://github.com/robertguetzkow/libtrashcan/pulls) for improvements. In particular I would be grateful for contributions regarding:
- Identifying cross-platform issues
- Stability / Reliability
- Security

## Change log

### v1.0.0-alpha - 2022-04-13
**Changes**
-Change of API: All function are prefix with `trashcan` to avoid name collisions
-Contribution by Mark Wagner ([Carnildo](https://github.com/Carnildo)): Add `extern "C"` to permit use in C++
-Bug fix for issue #10: Reference count is now decremented for the `IShellItem *pSI`
-Bug fix for issue #12: Reference count for the `IFileOperation *pfo` is only decremented when `CoCreateInstance` is successful
-Bug fix: Correct path construction when `HOME` or `XDG_DATA_HOME` is set to the root directory

### v0.3.3-alpha - 2019-05-25
**Changes**
-Support for macOS

### v0.2.0-alpha - 2019-04-26
**Changes**
-Correct multibyte to wide character conversion on Windows, supports UTF-8 encoded strings
-API gives access to the "core" functions on Windows that allow to use `wchar_t*` directly

### v0.1.0-alpha - 2019-04-24
**Changes**
-Initial version
