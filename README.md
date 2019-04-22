# libtrashcan
The libtrashcan is a cross-platform C library for soft deleting files and directories to the trashcan. 

## Supported Operating Systems
[x] Linux
[x] FreeBSD, OpenBSD, NetBSD
[x] Windows Vista, Windows Server 2008 and newer
[x] MacOS

## Why is this useful?
When you're implementing user interaction for viewing, selecting, loading and creating files you may also want to offer the functionality to delete files. Using POSIX specified functions for cross-platform development may seem sensible, however `remove()` and `rmdir()` happen to permanently delete files and directories. This is likely not the behavior a user of your program would anticipate even more so if there aren't any warnings. In order to ease development of cross-platform C applications this library implements the soft delete functionality for you. It also helps with operating system where the C interface isn't well documented, like for instance with Windows `IFileOperation` interface.

## How does the library implement a trashcan?
We provide a simple API consisting of a single function for each operating system. For Linux and *BSD the library implements the [FreeDesktop.org trash specification v1.0](https://specifications.freedesktop.org/trash-spec/trashspec-1.0.html). On Windows our implementation uses the `IFileOperation` interface and also handles COM initialization. MacOS already provides a simple way to trash files using the `NSFileManager` for which we provide a function as well. 

## License
Libtrashcan is licensed under the [MIT License](LICENSE). This license is compatible with GPL.

## Contribute
The library is in early development and making sure that it reaches a mature state is a core goal. If you'd like to contribute check the issue tracker or submit pull requests for improvements. In particular I'd be grateful for contributions regarding:
- Identifying cross-platform issues
- Stability / Reliability
- Security
