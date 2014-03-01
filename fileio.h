/** Exception declarations for file operations
 * @file common/fileio.h
 * @author Krzysztof Findeisen
 * @date Created May 8, 2013
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

#ifndef KPFUTILSFILEEXCEPTH
#define KPFUTILSFILEEXCEPTH

#include <stdexcept>
#include <string>

namespace kpfutils { namespace except {

using std::string;

/** @addtogroup exceptions
 *
 * General-purpose exceptions.
 * 
 * Include fileio.h to inherit from FileIo.
 * 
 *  @{
 */

/** Exception thrown when a file could not be read or written to.
 */
class FileIo: public std::runtime_error {
public:
	/** Constructs a FileIo object.
	 */
	FileIo(const std::string& what_arg);
};

/** @} */	// end exceptions

}}		// end kpfutils::except

#endif		// end ifndef KPFUTILSFILEEXCEPTH
