/** Functions converting C-style error codes to exceptions
 * @file common/cerror.h
 * @author Krzysztof Findeisen
 * @date Created May 27, 2013
 * @date Last modified June 18, 2013
 */

#ifndef CERRORH
#define CERRORH

#include <string>
#include <cstdio>

namespace kpfutils {

/* Wrapper that throws @c std::runtime_error in response to a GSL error
 */
//void gslCheck(int status, std::string msg);

/** Wrapper that throws @c std::runtime_error in response to a C library error
 */
void cError(std::string msg);

/** Wrapper that throws @ref kpfutils::except::FileIo "FileIo" in response to 
 *	a C I/O library error
 */
void fileError(FILE* const stream, std::string msg);

}	// end kpfutils

#endif	// CERRORH
