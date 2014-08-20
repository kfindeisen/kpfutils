/** Exception definitions for statistics functions
 * @file common/stats_except.cpp
 * @author Krzysztof Findeisen
 * @date Created May 5, 2013
 * @date Last modified September 18, 2013
 */

/* Copyright 2014, California Institute of Technology.
 *
 * This file is licensed under the BSD 3-Clause License. It is subject to the 
 * license terms in the LICENSE file found in the top-level directory of this 
 * distribution and at http://opensource.org/licenses/BSD-3-Clause. 
 */

#include <stdexcept>
#include <string>
#include "stats_except.h"

namespace kpfutils { namespace except {

using std::string;

/** Constructs a NotEnoughData object.
 *
 * @param[in] what_arg A string with the same content as the value 
 *	returned by what().
 *
 * @post @p this->what() = @p what_arg.c_str()
 *
 * @exception std::bad_alloc Thrown if there is not enough memory to 
 *	construct the exception.
 * 
 * @exceptsafe Object construction is atomic.
 */
NotEnoughData::NotEnoughData(const string& what_arg) : invalid_argument(what_arg) {
}

/** Constructs a NotSorted object.
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
NotSorted::NotSorted(const string& what_arg) : invalid_argument(what_arg) {
}

}}		// end kpfutils::except
