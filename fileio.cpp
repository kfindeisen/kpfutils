/** Exception definitions for file operations
 * @file common/fileio.cpp
 * @author Krzysztof Findeisen
 * @date Created May 8, 2013
 * @date Last modified May 8, 2013
 */

/* Copyright 2014, California Institute of Technology.
 *
 * This file is licensed under the BSD 3-Clause License. It is subject to the 
 * license terms in the LICENSE file found in the top-level directory of this 
 * distribution and at http://opensource.org/licenses/BSD-3-Clause. 
 */

#include <stdexcept>
#include <string>
#include "fileio.h"

namespace kpfutils { namespace except {

using std::string;

/** Constructs a FileIo object.
 *
 * @param[in] what_arg A string with the same content as the value 
 *	returned by what().
 *
 * @post this->what() = @p what_arg.c_str()
 *
 * @exception std::bad_alloc Thrown if there is not enough memory to 
 *	construct the exception.
 * 
 * @exceptsafe Object construction is atomic.
 */
FileIo::FileIo(const string& what_arg) : runtime_error(what_arg) {
}

}}		// end kpfutils::except
