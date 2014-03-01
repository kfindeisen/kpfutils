/** Exception declarations for light curve operations
 * @file common/lcexcept.cpp
 * @author Krzysztof Findeisen
 * @date Created July 24, 2013
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

#include <string>
#include "checkedexception.h"
#include "lcexcept.h"

namespace kpfutils { namespace except {

using std::string;

/** Constructs a NoValidTimes object.
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
NoValidTimes::NoValidTimes(const string& what_arg) : CheckedException(what_arg) {
}

}}		// end kpfutils::except
