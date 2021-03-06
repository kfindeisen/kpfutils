/** Base exception class analogous to std::runtime_error and std::logic_error
 * @file common/checkedexception.cpp
 * @author Krzysztof Findeisen
 * @date Created April 22, 2013
 * @date Last modified April 22, 2013
 */

/* Copyright 2014, California Institute of Technology.
 *
 * This file is licensed under the BSD 3-Clause License. It is subject to the 
 * license terms in the LICENSE file found in the top-level directory of this 
 * distribution and at http://opensource.org/licenses/BSD-3-Clause. 
 */

#include <exception>
#include <string>
#include "checkedexception.h"

namespace kpfutils { namespace except {

using std::string;

/** Constructs a CheckedException object.
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
CheckedException::CheckedException(const string& what_arg) 
		: exception(), arg(what_arg) {
}

CheckedException::~CheckedException() throw() {
}

/** Returns a null terminated character sequence that may be used to 
 * identify the exception.
 *
 * The sequence has the same content as the string passed to the 
 * constructor.
 *
 * @return A pointer to a C-string with content related to the 
 * exception. This is guaranteed to be valid at least until the 
 * exception object from which it is obtained is destroyed or until a 
 * non-const member function of the exception object is called.
 *
 * @exceptsafe Does not throw exceptions.
 */
const char* CheckedException::what() const throw() {
	return arg.c_str();
}

}}		// end kpfutils::except
