/** Functions converting C-style allocations to C++-style ones
 * @file common/alloc.tmp.h
 * @author Krzysztof Findeisen
 * @date Created May 27, 2013
 * @date Last modified January 14, 2014
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

#ifndef KPFUTILSALLOCH
#define KPFUTILSALLOCH

#include <string>
#include <cstdio>
#include <boost/smart_ptr.hpp>

namespace kpfutils {

/** @defgroup cstyle C-style Wrappers
 *
 * These functions wrap C++ conventions around C-style code.
 * 
 * Include alloc.tmp.h to wrap resource allocations.
 *
 * @{
 */

/** Wrapper that throws @ref kpfutils::except::FileIo "FileIo" if it cannot open a file
 */
boost::shared_ptr<FILE> fileCheckOpen(const std::string& fileName, const char* mode);

/** Wrapper that throws @c std::bad_alloc if an object was not allocated and 
 *	has no effect otherwise.
 *
 * @tparam T The type of the allocated object.
 *
 * @param[in] p A pointer that is expected to point to a newly allocated 
 *	object of type @p T.
 *
 * @return The pointer @p p, unchanged.
 *
 * @exception std::bad_alloc Thrown if @p p is null.
 *
 * @exceptsafe The function arguments are unchanged in the event of 
 *	an exception.
 */
template <typename T>
T* checkAlloc(T* const p) {
	if (p == NULL) {
		throw std::bad_alloc();
	}
	return p;
}

/** @} */ 	// End alloc

}	// end kpfutils

#endif	// KPFUTILSALLOCH
