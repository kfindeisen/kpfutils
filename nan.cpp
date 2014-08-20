/** Functions for handling data containing NaN values
 * @file common/nan.cpp
 * @author Krzysztof Findeisen
 * @date Created April 11, 2013
 * @date Last modified October 30, 2013
 */

/* Copyright 2014, California Institute of Technology.
 *
 * This file is licensed under the BSD 3-Clause License. It is subject to the 
 * license terms in the LICENSE file found in the top-level directory of this 
 * distribution and at http://opensource.org/licenses/BSD-3-Clause. 
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
