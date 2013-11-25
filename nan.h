/** Functions for handling data containing NaN values
 * @file common/nan.h
 * @author Krzysztof Findeisen
 * @date Created April 11, 2013
 * @date Last modified October 30, 2013
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
