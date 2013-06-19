/** Functions converting C-style error codes to exceptions
 * @file common/cerror.cpp
 * @author Krzysztof Findeisen
 * @date Created May 26, 2013
 * @date Last modified June 18, 2013
 */

#include <stdexcept>
#include <string>
#include <cerrno>
#include <cstring>
//#include <gsl/gsl_errno.h>
#include "cerror.h"

namespace kpfutils {

/* Wrapper that throws @c std::runtime_error in response to a GSL error
 *
 * @param[in] status A GSL error code.
 * @param[in] msg A string prepended to the exception's error message.
 *
 * @exception std::runtime_error Thrown if @p status &ne; 0
 * 
 * @exceptsafe The function arguments are unchanged in the event of an exception.
 */
//void gslCheck(int status, std::string msg) {
//	if (status != 0) {
//		throw std::runtime_error(msg + gsl_strerror(status));
//	}
//}

/** Wrapper that throws @c std::runtime_error in response to a C library error
 *
 * @param[in] msg A string prepended to the error message.
 *
 * @exception std::runtime_error Thrown if @c errno &ne; 0
 * 
 * @exceptsafe The function arguments are unchanged in the event of an 
 *	exception. The global variable @c errno is reset to 0.
 */
void cError(std::string msg) {
	if (errno != 0) {
		int err = errno;
		errno = 0;
		throw std::runtime_error(msg + strerror(err));
	}
}

}	// end kpfutils