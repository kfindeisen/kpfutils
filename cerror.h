/** Functions converting C-style error codes to exceptions
 * @file common/cerror.h
 * @author Krzysztof Findeisen
 * @date Created May 27, 2013
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
