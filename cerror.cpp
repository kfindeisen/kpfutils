/** Functions converting C-style error codes to exceptions
 * @file common/cerror.cpp
 * @author Krzysztof Findeisen
 * @date Created May 26, 2013
 * @date Last modified June 18, 2013
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
 * @post @c errno = 0
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
