/** Functions for handling data containing NaN values
 * @file common/nan.cpp
 * @author Krzysztof Findeisen
 * @date Created April 11, 2013
 * @date Last modified October 30, 2013
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

#include <limits>
#include "nan.h"

namespace kpfutils {

using std::numeric_limits;

/** isNan() tests whether a floating-point number is undefined
 *
 * @param[in] x The number to test
 * 
 * @return true if and only if @p x equals signaling or quiet not-a-number
 *
 * @exceptsafe Does not throw exceptions.
 */
bool isNan(const double x) {
	return (x != x);
}

/** isNanOrInf() tests whether a floating-point number is non-finite
 *
 * @param[in] x The number to test
 * 
 * @return true if and only if @p x equals signaling or quiet not-a-number, 
 *	or @p x is infinite
 *
 * @exceptsafe Does not throw exceptions.
 */
bool isNanOrInf(const double x) {
	return ( isNan(x) || (x ==  numeric_limits<double>::infinity()) 
			  || (x == -numeric_limits<double>::infinity()) );
}

/** Returns true iff the argument is not NaN.
 *
 * @param[in] x
 *
 * @return @p x &ne; NaN
 *
 * @exceptsafe Does not throw exceptions.
 */
bool NotNan::operator() (double x) {
	return !isNan(x);
}

}	// end kpfutils
