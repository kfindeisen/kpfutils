/** Functions converting C-style error codes to exceptions
 * @file common/cerror.h
 * @author Krzysztof Findeisen
 * @date Created May 27, 2013
 * @date Last modified July 24, 2013
 */

/* Copyright 2014, California Institute of Technology.
 *
 * This file is licensed under the BSD 3-Clause License. It is subject to the 
 * license terms in the LICENSE file found in the top-level directory of this 
 * distribution and at http://opensource.org/licenses/BSD-3-Clause. 
 */

#ifndef KPFUTILSCERRORH
#define KPFUTILSCERRORH

#include <string>
#include <cstdio>

namespace kpfutils {

/** @addtogroup cstyle
 *
 * These functions wrap C++ conventions around C-style code.
 *
 * Include cerror.h to parse integer error codes.
 *
 * @{
 */

/** Wrapper that throws @c std::runtime_error in response to a C library error
 */
void cError(std::string msg);

/** Wrapper that throws @ref kpfutils::except::FileIo "FileIo" in response to 
 *	a C I/O library error
 */
void fileError(FILE* const stream, std::string msg);

/** @} */ 	// End alloc

}	// end kpfutils

#endif	// KPFUTILSCERRORH
