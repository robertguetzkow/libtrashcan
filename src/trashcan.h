/* MIT License
 *
 * Copyright (c) 2019 Robert Guetzkow
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file trashcan.h
 * @author Robert Guetzkow
 * @version 0.1-alpha
 * @date 2019-04-18
 * @brief Header file defining libtrashcan's API
 *
 * This header defines the function signatures for the supported operating systems.
 * Platform dependent functions are defined within preprocessor directives.
 * 
 * @warning This is an alpha version and not considered stable. Severe bugs will likely
 * exist and it is not recommended to be used in production.
 */

#ifndef TRASHCAN_H
#define TRASHCAN_H

#ifdef WIN32
#include <stdbool.h>
/**
 * @brief Moves a file or a directory (and its content) to the recycling bin.
 *
 * @param path Path to the file or directory that shall be moved to the recycling bin.
 * @param code_page The code page to use when interpreting path as multibyte sequence.
 * @param init_com If true, initializes the COM library at the beginning using `CoUninitialize()`
 * and uninitializes it at the end with `CoUninitialize()`. If init_com is false the COM library
 * isn't loaded and has to be initialized by the code calling this function. This option is useful
 * to avoid initializing the COM library multiple times.
 * @return 0 when successful, negative otherwise.
 */
int soft_delete_com(const char *path, unsigned int code_page, bool init_com);

#elif __APPLE__
/**
 * @brief Moves a file or a directory (and its content) to the trash.
 *
 * @param path Path to the file or directory that shall be moved to the trash.
 * @param error Address where pointer to NSError object shall be stored.
 * @return 0 when successful, negative otherwise.
 */
int soft_delete_with_error(const char *path, NSError **error);

#elif __linux__ || __FreeBSD__ || __NetBSD__ || __OpenBSD__
#else
#error Platform not supported
#endif

/**
 * @brief Moves a file or a directory (and its content) to the trash.
 *
 * @warning This function expects an UTF-8 encoded string!
 *
 * On Linux and *BSD this function implements the FreeDesktop.org trash specification v1.0.
 * @see https://specifications.freedesktop.org/trash-spec/trashspec-1.0.html
 *
 * On Windows the `IFileOperation` interfaces is used. 
 * @note The COM library is initialized and uninitialized during this function call. If your
 * application already loads the COM library you should use `soft_delete_com()` with 
 * `init_com` set to `false`.
 *
 * On macOS the implementations is based on the `NSFileManager`.
 * @note If you wish to access the NSError object you should use `soft_delete_with_error()`.
 *
 * @warning 
 *
 * @param path Path to the file or directory that shall be moved to the trash. This path has 
 * to be UTF-8 encoded or use a compatible encoding.
 * @return 0 when successful, negative otherwise.
 */
int soft_delete(const char *path);

/**
 * @brief Returns a textual representation of the status code.
 *
 * @param error_code The return value of an API function
 * @return String literal that contains the status message
 */
const char* status_msg(int status_code);

#endif