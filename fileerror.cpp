/** Functions converting C-style error codes to exceptions
 * @file common/fileerror.cpp
 * @author Krzysztof Findeisen
 * @date Created June 18, 2013
 * @date Last modified July 24, 2013
 */

/* Copyright 2014 Krzysztof Findeisen
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include "cerror.h"
#include "fileio.h"

namespace kpfutils {

/** Wrapper that throws @ref kpfutils::except::FileIo "FileIo" in response to 
 *	a C I/O library error
 *
 * @param[in] stream The stream to test for errors
 * @param[in] msg A string prepended to the error message.
 *
 * @exception kpfutils::except::FileIo Thrown if @c ferror(@p stream)
 * 
 * @exceptsafe The function arguments are unchanged in the event of an 
 *	exception. The global variable @c errno is reset to 0. All error 
 *	indicators for @p stream are reset.
 */
void fileError(FILE* const stream, std::string msg) {
	if (ferror(stream) || feof(stream)) {
		int err = errno;
		clearerr(stream);
		errno = 0;
		throw kpfutils::except::FileIo(msg + strerror(err));
	}
}

}	// end kpfutils
