# libtrashcan :wastebasket:
libtrashcan is a cross-platform C library for soft deleting files and directories to the trashcan. 

## Supported Operating Systems
- [x] Linux
- [x] FreeBSD, OpenBSD, NetBSD
- [x] Windows Vista, Windows Server 2008 and newer
- [x] MacOS

## Why is this useful?
When you're implementing user interaction for viewing, selecting, loading and creating files you may also want to offer the functionality to delete files. Using POSIX specified functions for cross-platform development may seem sensible, however `remove()` and `rmdir()` happen to permanently delete files and directories. This is likely not the behavior a user of your program would anticipate even more so if there aren't any warnings. In order to ease development of cross-platform C applications this library implements the soft delete functionality for you. It also helps with operating systems where the C interface isn't well documented, like for instance with Windows' `IFileOperation` interface.

## How does the library implement a trashcan?
For Linux and *BSD the library implements the [FreeDesktop.org trash specification v1.0](https://specifications.freedesktop.org/trash-spec/trashspec-1.0.html). On Windows our implementation uses the `IFileOperation` interface and also handles COM initialization. MacOS already provides a simple way to trash files using the `NSFileManager` for which we provide a function as well. 

## API
We provide the function `int soft_delete(const char *path)` on all platforms. It takes a path to a file or directory, tries to move it to the trashcan and returns a status code. Additional platform dependent functions with different signatures are provided, e.g. to control COM initialization on Windows or accessing the `NSError` object on macOS. The complete API is documented in the [trashcan.h](src/trashcan.h) file. For an example application that uses libtrashcan take a look at [example.c](example.c).

All functions for soft deletion return a status code which can be converted into a status message using `const char* status_msg(int status_code)`. Any status code other than zero means that an error occured.

## Compilation
The example project requires CMake. This is *not a requirement* for your project as you can simply include `trashcan.h`, `trashcan.c` and use any build tools you prefer.

```
mkdir build
cd ./build
cmake ..
cmake --build . --config Release
```

The example project is a CLI application that takes a path to a file or directory as argument and tries to move it to the trash.

## License
Libtrashcan is licensed under the [MIT License](LICENSE). This license is compatible with GPL.

## Contribute
The library is in early development and making sure that it reaches a mature state is a core goal. If you'd like to contribute check the [issue tracker](https://github.com/robertguetzkow/libtrashcan/issues) or submit [pull requests](https://github.com/robertguetzkow/libtrashcan/pulls) for improvements. In particular I'd be grateful for contributions regarding:
- Identifying cross-platform issues
- Stability / Reliability
- Security
