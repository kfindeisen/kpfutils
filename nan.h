/** Functions for handling data containing NaN values
 * @file common/nan.h
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

#ifndef KPFNANH
#define KPFNANH

namespace kpfutils {

/** isNan() tests whether a floating-point number is undefined
 */
bool isNan(double x);

/** isNanOrInf() tests whether a floating-point number is non-finite
 */
bool isNanOrInf(double x);

/** Default-constructible predicate for testing whether something is not NaN
 */
class NotNan {
public: 
	/** Returns true iff the argument is not NaN.
	 */
	bool operator() (double x);
};

}	// end kpfutils

#endif	// ifndef KPFNANH
