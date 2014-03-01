/** Exception declarations for statistics functions
 * @file common/stats_except.h
 * @author Krzysztof Findeisen
 * @date Created May 5, 2013
 * @date Last modified September 18, 2013
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

#ifndef KPFSTATEXCEPTH
#define KPFSTATEXCEPTH

#include <stdexcept>
#include <string>

namespace kpfutils { namespace except {

using std::string;

/** @addtogroup stats
 *
 *  @{
 */

/** This exception is thrown if a range does not contain enough data to 
 *	calculate the desired statistic
 */
class NotEnoughData : public std::invalid_argument {
public:
	/** Constructs a NotEnoughData object.
	 */
	explicit NotEnoughData(const string& what_arg);
};

/** This exception is thrown if a function argument is not sorted.
 */
class NotSorted : public std::invalid_argument {
public:
	/** Constructs a NotSorted object.
	 */
	explicit NotSorted(const string& what_arg);
};

/** @} */	// end stats

}}		// end kpfutils::except

#endif		// end ifndef KPFSTATEXCEPTH
