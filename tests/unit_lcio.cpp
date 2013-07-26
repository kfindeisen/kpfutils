/** Test unit for light curve I/O functions in lcio.h
 * @file common/tests/unit_lcio.cpp
 * @author Krzysztof Findeisen
 * @date Created July 25, 2011
 * @date Last modified July 25, 2013
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

#include <vector>
#include <cmath>

using std::vector;

// Private functions to test
void sortByTime(vector<double>& times, vector<double>& data);
void sortByTime(vector<double>& times, vector<double>& data, vector<double>& errs);

namespace kpfutils { namespace test {

/** Data common to the test cases.
 *
 * Contains arrays, lists, and vectors with mock data.
 */
class LcIoData {
public: 
	const static size_t TEST_LEN = 200;

	/** Defines the data for each test case.
	 *
	 * @exception std::bad_alloc Thrown if there is not enough memory to 
	 *	store the testing data.
	 *
	 * @exceptsafe Object construction is atomic.
	 */
	LcIoData() : mockTimes(), mockData(), mockErrs() {
	for(size_t i = 0; i < TEST_LEN; i++) {
		mockTimes.push_back(10.0*sin(0.1*i));
		mockData .push_back(10.0*cos(0.1*i));
		mockErrs .push_back(0.1);
	}
	}
	
	virtual ~LcIoData() {
	}
	
	/** Data for testing preprocessing of light curves
	 */
	vector<double> mockTimes, mockData, mockErrs;
};

/** Test cases for light curve input
 * @class BoostTest::test_lcread
 */
BOOST_FIXTURE_TEST_SUITE(test_lcread, LcIoData)

/** Tests whether sortByTime() can handle mid-sized data sets
 *
 * @exceptsafe Does not throw exceptions.
 */
BOOST_AUTO_TEST_CASE(time_sort2)
{
	BOOST_CHECK_NO_THROW(sortByTime(mockTimes, mockData));
}

/** Tests whether sortByTime() can handle mid-sized data sets
 *
 * @exceptsafe Does not throw exceptions.
 */
BOOST_AUTO_TEST_CASE(time_sort3)
{
	BOOST_CHECK_NO_THROW(sortByTime(mockTimes, mockData, mockErrs));
}

BOOST_AUTO_TEST_SUITE_END()

}}	// end kpfutils::test
