/** Functions managing C file handles
 * @file common/filealloc.cpp
 * @author Krzysztof Findeisen
 * @date Created June 18, 2013
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

#include <string>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <boost/smart_ptr.hpp>
#include "alloc.tmp.h"
#include "fileio.h"

namespace kpfutils {

using boost::shared_ptr;

/** Wrapper that throws @ref kpfutils::except::FileIo "FileIo" if it 
 *	cannot open a file
 *
 * @param[in] fileName The file to open.
 * @param[in] mode The mode to open the file, following the same 
 *	conventions as for @c fopen()
 *
 * @return A handle to the newly opened file. The file will be closed once its 
 *	last reference disappears.
 *
 * @exception kpfutils::except::FileIo Thrown if the file could not be opened.
 * 
 * @exceptsafe The function arguments are unchanged in the event of an exception.
 */
shared_ptr<FILE> fileCheckOpen(const std::string& fileName, const char* mode) {
	FILE* handle = fopen(fileName.c_str(), mode);
	
	if (handle == NULL) {
		// Not all implementations of fopen() set errno on an error
		if (errno) {
			int err = errno;
			errno = 0;
			throw kpfutils::except::FileIo("Could not open " 
				+ fileName + ": " + strerror(err));
		} else {
			throw kpfutils::except::FileIo("Could not open " + fileName);
		}
	}
	
	return shared_ptr<FILE>(handle, &fclose);
}

}	// end kpfutils
