/** Functions converting C-style error codes to exceptions
 * @file common/fileerror.cpp
 * @author Krzysztof Findeisen
 * @date Created June 18, 2013
 * @date Last modified June 18, 2013
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
 *	exception. The global variable @c errno is reset to 0.
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
