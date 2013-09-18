/** Exception declarations for statistics functions
 * @file common/stats_except.h
 * @author Krzysztof Findeisen
 * @date Created May 5, 2013
 * @date Last modified September 18, 2013
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
