/** Functions for handling data containing NaN values
 * @file common/nan.h
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
