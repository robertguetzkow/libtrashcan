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
  * @file example.c
  * @author Robert Guetzkow
  * @date 2019-04-22
  * @brief Example implementation calling libtrashcan. First argument should be a file
  * or a directory which is then moved to the trash.
  */

#include "src/trashcan.h"
#include <stdio.h>

#ifdef WIN32
#include <wchar.h>
int wmain(int argc, wchar_t **argv)
{
	int ret = soft_delete_core(argv[1], true);

#else
int main(int argc, char **argv)
{
	int ret = soft_delete(argv[1]);

#endif

	if (ret != 0) 
	{ 
		const char *msg = status_msg(ret);
		printf("%s\n", msg);
	}

	return ret;
}
