/** Exception declarations for file operations
 * @file common/fileio.h
 * @author Krzysztof Findeisen
 * @date Created May 8, 2013
 * @date Last modified July 24, 2013
 */

/* Copyright 2014, California Institute of Technology.
 *
 * This file is licensed under the BSD 3-Clause License. It is subject to the 
 * license terms in the LICENSE file found in the top-level directory of this 
 * distribution and at http://opensource.org/licenses/BSD-3-Clause. 
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
