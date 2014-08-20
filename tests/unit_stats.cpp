/** Test unit for statistics template functions in stats.tmp.h
 * @file common/tests/unit_stats.cpp
 * @author Krzysztof Findeisen
 * @date Created July 20, 2011
 * @date Last modified July 24, 2013
 */

/* Copyright 2014, California Institute of Technology.
 *
 * This file is part of the kpfutils Test Suite.
 * 
 * The kpfutils Test Suite is free software: you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as published 
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version, subject to the following 
 * exception added under Section 7 of the License:
 *	* Neither the name of the copyright holder nor the names of its contributors 
 *	  may be used to endorse or promote products derived from this software 
 *	  without specific prior written permission.
 * 
 * The kpfutils Test Suite is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with the kpfutils Test Suite. If not, see <http://www.gnu.org/licenses/>.
 */

#include "../warnflags.h"

// Boost.Test uses C-style casts and non-virtual destructors
#ifdef GNUC_COARSEWARN
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Weffc++"
#endif

// Boost.Test uses C-style casts and non-virtual destructors
#ifdef GNUC_FINEWARN
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Weffc++"
#endif

#include <boost/test/unit_test.hpp>

// Re-enable all compiler warnings
#ifdef GNUC_FINEWARN
#pragma GCC diagnostic pop
#endif

#include <list>
#include <stdexcept>
#include <vector>
#include <boost/smart_ptr.hpp>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_statistics_double.h>
#include <gsl/gsl_statistics_int.h>
#include "../nan.h"
#include "../stats.tmp.h"
#include "../alloc.tmp.h"

namespace kpfutils { namespace test {

using boost::shared_array;
using boost::shared_ptr;
using namespace std;

/** Data common to the test cases.
 *
 * Contains arrays, lists, and vectors with mock data.
 */
class StatsData {
public: 
	const static size_t TEST_LEN       = 100;
	const static size_t TEST_COUNT     =  10;
	const static double TEST_TOLERANCE;

	/** Defines the data for each test case.
	 *
	 * @exception std::bad_alloc Thrown if there is not enough memory to 
	 *	store the testing data.
	 *
	 * @exceptsafe Object construction is atomic.
	 */
	StatsData() : emptyList(), oneList(1, 42), twoList(), 
			intArray(), intList(), dblArray(), dblList(), dblVec() {
		twoList.push_back(-10);
		twoList.push_back(27);
	
		// Data come from a random number generator
		shared_ptr<gsl_rng> testRng(checkAlloc(gsl_rng_alloc(gsl_rng_mt19937)), 
			&gsl_rng_free);
		gsl_rng_set(testRng.get(), 42);
		
		// Define the arrays, then the STL versions
		for (size_t nTest = 0; nTest < TEST_COUNT; nTest++) {
			intArray.push_back(shared_array<int   >(new int   [TEST_LEN]));
			intList.push_back(  list<int   >());

			dblArray.push_back(shared_array<double>(new double[TEST_LEN]));
			dblList.push_back(  list<double>());
			dblVec .push_back(vector<double>());
			dblVec.back().reserve(TEST_LEN);
			for (size_t i = 0; i < TEST_LEN; i++) {
				{
					// Large sigma to allow interesting truncation to int
					int intVal = static_cast<int>(
						gsl_ran_gaussian(testRng.get(), 1000.0));
					intArray.back()[i] = intVal;
					intList .back().push_back(intVal);
				}

				{
					double dblVal = gsl_ran_ugaussian(testRng.get());
					dblArray.back()[i] = dblVal;
					dblList .back().push_back(dblVal);
					dblVec  .back().push_back(dblVal);
				}
			}
		}
	}
	
	virtual ~StatsData() {
	}
	
	/** Empty list of ints
	 */
	list<int> emptyList;
	/** Length-1 list of ints
	 */
	list<int> oneList;
	/** Length-2 list of ints
	 */
	list<int> twoList;
	
	/** Length-100 collections of integers
	 */
	vector<shared_array<int   > > intArray;
	vector<        list<int   > > intList;
	/** Length-100 collections of floating point numbers
	 */
	vector<shared_array<double> > dblArray;
	vector<        list<double> > dblList;
	vector<      vector<double> > dblVec;
};
const double StatsData::TEST_TOLERANCE = 1e-8;

/** Test cases for generic mean and variance functions
 * @class BoostTest::test_stats
 */
BOOST_FIXTURE_TEST_SUITE(test_stats, StatsData)

/** Tests whether mean() works as advertised
 *
 * @exceptsafe Does not throw exceptions.
 */
BOOST_AUTO_TEST_CASE(mean)
{
	/** @test List of ints, length 0. Expected behavior: throw invalid_argument.
	 */
	BOOST_CHECK_THROW(kpfutils::mean(emptyList.begin(), emptyList.end()), 
		std::invalid_argument);
	
	/** @test List of ints, length 1. Expected behavior: return list[0]
	 */
	BOOST_CHECK_NO_THROW(BOOST_CHECK_EQUAL(
		kpfutils::mean(oneList.begin(), oneList.end()), 
		oneList.front()));
	
	for (size_t nTest = 0; nTest < TEST_COUNT; nTest++) {
		int trueMean = static_cast<int>(
			gsl_stats_int_mean(intArray[nTest].get(), 1, TEST_LEN));
		/** @test List of ints, length 100, randomly generated. Expected behavior: 
		 * 	agrees with gsl_stats_mean in 10 out of 10 trials.
		 */
		BOOST_CHECK_NO_THROW(BOOST_CHECK_EQUAL(
			kpfutils::mean(intList[nTest].begin(), intList[nTest].end()), 
			trueMean));
		
		/** @test Array of ints, length 100, randomly generated. Expected behavior: 
		 *	agrees with gsl_stats_mean in 10 out of 10 trials.
		 */
		BOOST_CHECK_NO_THROW(BOOST_CHECK_EQUAL(
			kpfutils::mean(intArray[nTest].get(), intArray[nTest].get()+TEST_LEN), 
			trueMean));
	}

	for (size_t nTest = 0; nTest < TEST_COUNT; nTest++) {
		double trueMean = gsl_stats_mean(dblArray[nTest].get(), 1, TEST_LEN);
		/** @test List of doubles, length 100, randomly generated. Expected behavior: 
		 *	agrees with gsl_stats_mean to within 1e-8 in 10 out of 10 trials.
		 */
		BOOST_CHECK_NO_THROW(BOOST_CHECK_CLOSE(
			kpfutils::mean(dblList[nTest].begin(), dblList[nTest].end()), 
			trueMean, TEST_TOLERANCE));
		
		/** @test Vector of doubles, length 100, randomly generated. Expected behavior: 
		 *	agrees with gsl_stats_mean to within 1e-8 in 10 out of 10 trials.
		 */
		BOOST_CHECK_NO_THROW(BOOST_CHECK_CLOSE(
			kpfutils::mean(dblVec[nTest].begin(), dblVec[nTest].end()), 
			trueMean, TEST_TOLERANCE));
		
		/** @test Array of doubles, length 100, randomly generated. Expected behavior: 
		 *	agrees with gsl_stats_mean to within 1e-8 in 10 out of 10 trials.
		 */
		BOOST_CHECK_NO_THROW(BOOST_CHECK_CLOSE(
			kpfutils::mean(dblArray[nTest].get(), dblArray[nTest].get()+TEST_LEN), 
			trueMean, TEST_TOLERANCE));
	}
}

/** Tests whether variance() works as advertised
 *
 * @exceptsafe Does not throw exceptions.
 */
BOOST_AUTO_TEST_CASE(variance)
{
	/** @test List of ints, length 0. Expected behavior: throw invalid_argument.
	 */
	BOOST_CHECK_THROW(kpfutils::variance(emptyList.begin(), emptyList.end()), 
		std::invalid_argument);
	
	/** @test List of ints, length 1. Expected behavior: throw invalid_argument.
	 */
	BOOST_CHECK_THROW(kpfutils::variance(oneList.begin(), oneList.end()), 
		std::invalid_argument);
	
	/** @test List of ints, length 2. Expected behavior: return 
	 *		(list::back()-list::front())^2/2
	 */
	{
		int trueVar = twoList.back()-twoList.front();
		trueVar *= trueVar;
		trueVar /= 2;
		BOOST_CHECK_NO_THROW(BOOST_CHECK_EQUAL(
			kpfutils::variance(twoList.begin(), twoList.end()), 
			trueVar));
	}
	
	for (size_t nTest = 0; nTest < TEST_COUNT; nTest++) {
		int trueVar = static_cast<int>(
			gsl_stats_int_variance(intArray[nTest].get(), 1, TEST_LEN));
		/** @test List of ints, length 100, randomly generated. Expected behavior: 
		 *	agrees with gsl_stats_variance in 10 out of 10 trials.
		 */
		BOOST_CHECK_NO_THROW(BOOST_CHECK_EQUAL(
			kpfutils::variance(intList[nTest].begin(), intList[nTest].end()), 
			trueVar));
	}

	for (size_t nTest = 0; nTest < TEST_COUNT; nTest++) {
		double trueVar = gsl_stats_variance(dblArray[nTest].get(), 1, TEST_LEN);
		/** @test List of doubles, length 100, randomly generated. Expected behavior: 
		 *	agrees with gsl_stats_variance to within 1e-8 in 10 out of 10 trials.
		 */
		BOOST_CHECK_NO_THROW(BOOST_CHECK_CLOSE(
			kpfutils::variance(dblList[nTest].begin(), dblList[nTest].end()),
			trueVar, TEST_TOLERANCE));
		
		/** @test Vector of doubles, length 100, randomly generated. Expected behavior: 
		 *	agrees with gsl_stats_variance to within 1e-8 in 10 out of 10 trials.
		 */
		BOOST_CHECK_NO_THROW(BOOST_CHECK_CLOSE(
			kpfutils::variance(dblVec[nTest].begin(), dblVec[nTest].end()), 
			trueVar, TEST_TOLERANCE));
		
		/** @test Array of doubles, length 100, randomly generated. Expected behavior: 
		 *	agrees with gsl_stats_variance to within 1e-8 in 10 out of 10 trials.
		 */
		BOOST_CHECK_NO_THROW(BOOST_CHECK_CLOSE(
			kpfutils::variance(dblArray[nTest].get(), 
			dblArray[nTest].get()+TEST_LEN), 
			trueVar, TEST_TOLERANCE));
	}
}

BOOST_AUTO_TEST_SUITE_END()

// Boost.Test uses non-virtual destructors
#ifdef GNUC_FINEWARN
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#endif

/** Test cases for testing functions related to handling Nan values
 * @class BoostTest::test_nan
 */
BOOST_AUTO_TEST_SUITE(test_nan)

/** Tests whether NaN diagnostics work as advertised
 *
 * @exceptsafe Does not throw exceptions.
 */
BOOST_AUTO_TEST_CASE(nan_check) {
	// Easy access to special double values
	typedef std::numeric_limits<double> d;
	
	BOOST_WARN(d::     has_infinity);
	BOOST_WARN(d::    has_quiet_NaN);
	BOOST_WARN(d::has_signaling_NaN);

	// Skip tests if the system doesn't support special floating-point values
	BOOST_CHECK(!d::     has_infinity || !isNan( d::     infinity()));
	BOOST_CHECK(                         !isNan( 3.0               ));
	BOOST_CHECK(                         !isNan( 0.0               ));
	BOOST_CHECK(                         !isNan(-3.0               ));
	BOOST_CHECK(!d::     has_infinity || !isNan(-d::     infinity()));
	BOOST_CHECK(!d::    has_quiet_NaN ||  isNan(-d::    quiet_NaN()));
	BOOST_CHECK(!d::has_signaling_NaN ||  isNan(-d::signaling_NaN()));
	
	BOOST_CHECK(!d::     has_infinity ||  isNanOrInf( d::     infinity()));
	BOOST_CHECK(                         !isNanOrInf( 3.0               ));
	BOOST_CHECK(                         !isNanOrInf( 0.0               ));
	BOOST_CHECK(                         !isNanOrInf(-3.0               ));
	BOOST_CHECK(!d::     has_infinity ||  isNanOrInf(-d::     infinity()));
	BOOST_CHECK(!d::    has_quiet_NaN ||  isNanOrInf(-d::    quiet_NaN()));
	BOOST_CHECK(!d::has_signaling_NaN ||  isNanOrInf(-d::signaling_NaN()));
}

BOOST_AUTO_TEST_SUITE_END()

// Re-enable all compiler warnings
#ifdef GNUC_FINEWARN
#pragma GCC diagnostic pop
#endif

}}	// end kpfutils::test
