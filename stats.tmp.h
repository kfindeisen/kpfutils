/** Generic statistics for data sets in containers
 * @file common/stats.tmp.h
 * @author Krzysztof Findeisen
 * @date Created July 21, 2011
 * @date Last modified July 24, 2013
 */

/* Copyright 2014, California Institute of Technology.
 *
 * This file is licensed under the BSD 3-Clause License. It is subject to the 
 * license terms in the LICENSE file found in the top-level directory of this 
 * distribution and at http://opensource.org/licenses/BSD-3-Clause. 
 */

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstdio>
#include <boost/concept/requires.hpp>
#include <boost/iterator/iterator_concepts.hpp>
#include <boost/lexical_cast.hpp>
#include "stats_except.h"

namespace kpfutils {

using namespace boost;
using boost_concepts::ReadableIteratorConcept;
using boost_concepts::ForwardTraversalConcept;
using boost_concepts::RandomAccessTraversalConcept;
 
/** @defgroup stats Statistics Functions
 *
 * Speed-optimized statistics functions
 *
 * These functions calculate basic sample statistics. Unlike the equivalent 
 * GSL functions, they work on any container and do not require the overhead 
 * of converting to C-array format. Use them by including stats.tmp.h.
 * Include stats_except.h to catch exceptions thrown by these functions.
 *
 *  @{
 */

/*----------------------------------------------------------
 * Speed-optimized Statistics Functions
 * I already had these written, so it was simpler than writing a wrapper to 
 *	convert vectors to C arrays just so GSL can understand them
 */

/** Finds the mean of the values in a generic container object. The container 
 *	class is accessed using first and last iterators, and the mean is 
 *	computed over the interval [first, last).
 * 
 * @tparam ConstInputIterator The iterator type for the container over which the 
 *	mean is to be calculated. Must be <a href="http://www.boost.org/doc/libs/release/libs/iterator/doc/ReadableIterator.html">readable</a> and support <a href="http://www.boost.org/doc/libs/release/libs/iterator/doc/ForwardTraversal.html">forward traversal</a>.
 * @param[in] first Input iterator marking the first element in the container.
 * @param[in] last Input iterator marking the position after the last 
 *	element in the container.
 *
 * @return The arithmetic mean of the elements between @p first, inclusive, and 
 *	@p last, exclusive. The return type is that of the elements pointed to by 
 *	the @p first and @p last iterators.
 *
 * @pre [@p first, @p last) is a valid range
 * @pre There is at least one element in the range [@p first, @p last)
 * @pre No value in [@p first, @p last) is NaN
 *
 * @post The return value is not NaN
 *
 * @perform O(D), where D = std::distance(@p first, @p last).
 *
 * @exception kpfutils::except::NotEnoughData Thrown if there are not enough 
 *	elements to define a mean.
 * 
 * @exceptsafe The range [@p first, @p last) is unchanged in the event of an exception.
 *
 * @test List of ints, length 0. Expected behavior: throw invalid_argument.
 * @test List of ints, length 1. Expected behavior: return list[0]
 * @test List of ints, length 100, randomly generated. Expected behavior: 
 *	agrees with gsl_stats_mean in 10 out of 10 trials.
 * @test List of doubles, length 100, randomly generated. Expected behavior: 
 *	agrees with gsl_stats_mean to within 1e-10 in 10 out of 10 trials.
 * @test Vector of doubles, length 100, randomly generated. Expected behavior: 
 *	agrees with gsl_stats_mean to within 1e-10 in 10 out of 10 trials.
 * @test Array of doubles, length 100, randomly generated. Expected behavior: 
 *	agrees with gsl_stats_mean to within 1e-10 in 10 out of 10 trials.
 *
 * @todo Apply concept checking to the return type
 */
template <typename ConstInputIterator> 				// Iterator to use
BOOST_CONCEPT_REQUIRES(
	((ReadableIteratorConcept<ConstInputIterator>)) 
	((ForwardTraversalConcept<ConstInputIterator>)),	// Iterator semantics
	(typename std::iterator_traits<ConstInputIterator>::value_type)) // Return type
mean(ConstInputIterator first, ConstInputIterator last) {
	typedef typename std::iterator_traits<ConstInputIterator>::value_type Value;

	Value  sum = 0;
	long count = 0;

	// Since iterators are passed by value, incrementing first does not 
	//	violate exception guarantee
	for(; first != last; first++) {
		sum += (*first);
		count++;
	}
	if (count <= 0) {
		throw except::NotEnoughData("Not enough data to compute mean");
	}

	// Force floating-point arithmetic to avoid inconsistencies in 
	//	integer division rounding conventions
	// Delayed conversion because ++ operator is inaccurate for large doubles
	double dcount = static_cast<double>(count);

	return static_cast<Value>(sum / dcount);
}

/** Finds the variance of the values in a generic container object. The 
 *	container class is accessed using first and last iterators, and 
 *	the variance is computed over the interval [first, last).
 * 
 * @tparam ConstInputIterator The iterator type for the container over which the 
 *	variance is to be calculated. Must be <a href="http://www.boost.org/doc/libs/release/libs/iterator/doc/ReadableIterator.html">readable</a> and support <a href="http://www.boost.org/doc/libs/release/libs/iterator/doc/ForwardTraversal.html">forward traversal</a>.
 * @param[in] first Input iterator marking the first element in the container.
 * @param[in] last Input iterator marking the position after the last element in the container.
 *
 * @return The (unbiased) sample variance of the elements between @p first, 
 *	inclusive, and @p last, exclusive. The return type is that of the 
 *	elements pointed to by the @p first and @p last iterators.
 *
 * @pre [@p first, @p last) is a valid range
 * @pre There are at least two elements in the range [@p first, @p last)
 * @pre No value in [@p first, @p last) is NaN
 *
 * @post The return value is not NaN
 *
 * @perform O(D), where D = std::distance(@p first, @p last).
 *
 * @exception kpfutils::except::NotEnoughData Thrown if there are not enough 
 *	elements to define a variance.
 * 
 * @exceptsafe The range [@p first, @p last) is unchanged in the event of an exception.
 *
 * @test List of ints, length 0. Expected behavior: throw invalid_argument.
 * @test List of ints, length 1. Expected behavior: throw invalid_argument.
 * @test List of ints, length 2. Expected behavior: return (%list::back()-%list::front())^2/2
 * @test List of ints, length 100, randomly generated. Expected behavior: 
 *	agrees with gsl_stats_variance in 10 out of 10 trials.
 * @test List of doubles, length 100, randomly generated. Expected behavior: 
 *	agrees with gsl_stats_variance to within 1e-10 in 10 out of 10 trials.
 * @test Vector of doubles, length 100, randomly generated. Expected behavior: 
 *	agrees with gsl_stats_variance to within 1e-10 in 10 out of 10 trials.
 * @test Array of doubles, length 100, randomly generated. Expected behavior: 
 *	agrees with gsl_stats_variance to within 1e-10 in 10 out of 10 trials.
 *
 * @todo Apply concept checking to the return type
 */
template <typename ConstInputIterator> 				// Iterator to use
BOOST_CONCEPT_REQUIRES(
	((ReadableIteratorConcept<ConstInputIterator>)) 
	((ForwardTraversalConcept<ConstInputIterator>)),	// Iterator semantics
	(typename std::iterator_traits<ConstInputIterator>::value_type)) // Return type
variance(ConstInputIterator first, ConstInputIterator last) {
	typedef typename std::iterator_traits<ConstInputIterator>::value_type Value;

	Value  sum = 0, sumsq = 0;
	long count = 0;

	// Since iterators are passed by value, incrementing first does not 
	//	violate exception guarantee
	for(; first != last; first++) {
		sum   += (*first);
		sumsq += (*first)*(*first);
		count++;
	}
	if (count <= 1) {
		throw except::NotEnoughData("Not enough data to compute variance");
	}

	// Force floating-point arithmetic to avoid inconsistencies in 
	//	integer division rounding conventions
	// Delayed conversion because ++ operator is inaccurate for large doubles
	double dcount = static_cast<double>(count);

	// Minimize number of divisions and maximize dividend in case value_type is integral
	return static_cast<Value>((sumsq - sum*sum/dcount)/(dcount-1));
}

/** Finds the (uninterpolated) quantile of the values in a generic container 
 *	object. The container class is accessed using first and last 
 *	iterators, and the quantile is computed over the interval 
 *	[first, last). Data is assumed unsorted.
 * 
 * @tparam ConstRandomAccessIterator The iterator type for the container over which the 
 *	variance is to be calculated. Must be <a href="http://www.boost.org/doc/libs/release/libs/iterator/doc/ReadableIterator.html">readable</a> and support <a href="http://www.boost.org/doc/libs/release/libs/iterator/doc/RandomAccessTraversal.html">random access</a>
 * @param[in] first Input iterator marking the first element in the 
 *	container.
 * @param[in] last Input iterator marking the position after the last 
 *	element in the container.
 * @param[in] quantile The percentile to recover.
 *
 * @return The largest value whose quantile is less than or equal to 
 *	@p quantile.
 *
 * @pre [@p first, @p last) is a valid range
 * @pre There are at least two elements in the range [@p first, @p last)
 * @pre 0 <= @p quantile <= 1
 * @pre No value in [@p first, @p last) is NaN
 *
 * @post The return value is not NaN
 *
 * @perform O(D log D), where D = std::distance(@p first, @p last).
 * 
 * @exception std::invalid_argument Thrown if @p quantile is not 
 *	in the interval [0, 1].
 *
 * @exception kpfutils::except::NotEnoughData Thrown if there are not enough 
 *	elements to define a quantile.
 * 
 * @exceptsafe The range [@p first, @p last) is unchanged in the event of an exception.
 *
 * @test List of ints, length 0. Expected behavior: throw invalid_argument.
 * @test List of ints, length 1, quantile=0.00. Expected behavior: return %list::front()
 * @test List of ints, length 1, quantile=0.42. Expected behavior: return %list::front()
 * @test List of ints, length 1, quantile=1.00. Expected behavior: return %list::front()
 * @test List of ints, length 100, randomly generated, quantile=-0.01 or 1.01. 
 *	Expected behavior: throw domain_error
 * @test List of ints, length 100, randomly generated, quantile=0.00, 0.42, or 1.00. 
 *	Expected behavior: TBD
 * @test List of doubles, length 100, randomly generated, quantile=0.00, 0.42, or 1.00. 
 *	Expected behavior: TBD
 * @test Vector of doubles, length 100, randomly generated, quantile=0.00, 0.42, or 1.00. 
 *	Expected behavior: TBD
 * @test Array of doubles, length 100, randomly generated, quantile=0.00, 0.42, or 1.00. 
 *	Expected behavior: TBD
 *
 * @todo Pick a specific convention for quantiles and use it consistently
 *
 * @todo Finish designing test cases. Can't use gsl_stats_quantile_from_sorted_data 
 *	as an oracle because it interpolates
 * @todo Apply concept checking to the return type
 */
template <typename ConstRandomAccessIterator> 				// Iterator to use
BOOST_CONCEPT_REQUIRES(
	((ReadableIteratorConcept<ConstRandomAccessIterator>)) 
	((RandomAccessTraversalConcept<ConstRandomAccessIterator>)),	// Iterator semantics
	(typename std::iterator_traits<ConstRandomAccessIterator>::value_type)) // Return type
quantile(ConstRandomAccessIterator first, ConstRandomAccessIterator last, double quantile) {
	typedef typename std::iterator_traits<ConstRandomAccessIterator>::value_type Value;
	
	if (quantile < 0.0 || quantile > 1.0) {
		try {
			throw std::invalid_argument("Invalid quantile of " + lexical_cast<std::string>(quantile) + " passed to quantile()");
		} catch (const bad_lexical_cast& e) {
			throw std::invalid_argument("Invalid quantile passed to quantile()");
		}
	}

	// We don't want to alter the data, so we copy while sorting
	// Copy to a vector because sorting requires random access
	size_t vecSize = distance(first, last);
	if (vecSize < 1) {
		throw except::NotEnoughData("Supplied empty data set to quantile()");
	}
	std::vector<Value> sortedVec(vecSize);
	/** @todo Reimplement using partial sorting
	 */
	std::partial_sort_copy(first, last, sortedVec.begin(), sortedVec.end());

	size_t index = 0;
	if (quantile >= 0.0 && quantile < 1.0) {
		index = static_cast<size_t>(quantile*vecSize);
	} else if (quantile == 1.0) {
		index = vecSize-1;
	}
	
	return sortedVec[index];
}

/** Tests whether a range is sorted.
 *
 * This function emulates <tt>std::is_sorted()</tt> for platforms without access 
 * to either a C++11-compliant compiler or Boost 1.50 or later.
 *
 * @tparam ConstForwardIterator The iterator type for the container to be tested. 
 * Must be a <a href="http://www.boost.org/doc/libs/release/doc/html/ForwardIterator.html">forward iterator</a>.
 * @param[in] first,last Forward iterators to the range to test. The range 
 *	is all elements in the interval [@p first, @p last).
 *
 * @return True if [@p first, @p last) is sorted in ascending order. A range 
 *	containing less than two elements is always sorted.
 *
 * @perform O(D), where D = std::distance(@p first, @p last).
 *
 * @exceptsafe The range [@p first, @p last) is unchanged in the event of 
 *	an exception if ConstForwardIterator provides at least the basic 
 *	guarantee. Does not throw exceptions unless ConstForwardIterator throws.
 * 
 * @test Empty list. Expected behavior: true.
 * @test List of size 1. Expected behavior: true.
 * @test List of size 2, sorted asc. Expected behavior: true.
 * @test List of size 2, sorted desc. Expected behavior: false.
 * @test List of size 10, list[i] = i^2. Expected behavior: true.
 * @test List of size 10, list[i] = (i-5)^2. Expected behavior: false.
 * @test List of size 10, random elements. Expected behavior: false.
 *
 * @todo Implement these test cases.
 */
template <class ConstForwardIterator>
BOOST_CONCEPT_REQUIRES(
	((ReadableIteratorConcept<ConstForwardIterator>)) 
	((ForwardTraversalConcept<ConstForwardIterator>)),	// Iterator semantics
	(bool)) 					// Return type
isSorted (ConstForwardIterator first, ConstForwardIterator last) {
	// Code shamelessly copied from http://www.cplusplus.com/reference/algorithm/is_sorted/
	if (first==last) {
		return true;
	}
	
	// Since iterators are passed by value, incrementing first does not 
	//	violate exception guarantee
	for(ConstForwardIterator next = first; ++next != last; ++first) {
		if (*next<*first) {
			return false;
		}
	}
	return true;
}

/** @} */	// end stats

}	// end kpfutils
