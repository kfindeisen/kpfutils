/** Light curve manipulation functions
 * @file lcmanip.cpp
 * @author Krzysztof Findeisen
 * @date Created February 6, 2011
 * @date Last modified July 24, 2013
 */

#include <algorithm>
#include <vector>
#include <boost/lexical_cast.hpp>
#include "checkedexception.h"
#include "lcexcept.h"
#include "lcio.h"

namespace kpfutils {

using namespace std;
using boost::lexical_cast;

/** Filters a set of vectors to include only dates between @p date1 and @p date2
 *
 * @param[in] date1 the smallest Julian date to be allowed in @p times
 * @param[in] date2 the largest Julian date to be allowed in @p times
 * @param[in,out] times a vector of times to be trimmed to [@p date1, @p date2]
 * @param[in,out] arr1, arr2 vectors of measurements corresponding to @p times, 
 *	to be trimmed in parallel
 *
 * @pre @p times is sorted in ascending order
 * 
 * @post @p times is updated to contain only items greater than or equal to 
 *	@p date1 and less than or equal to @p date2. Any entries corresponding 
 *	to deleted entries of @p times are deleted from @p arr1 and @p arr2.
 *
 * @exception kpfutils::except::NoValidTimes Thrown if @p date2 < @p date1 or 
 *	if all values in @p times are outside [@p date1, @p date2]. 
 * @exception std::bad_alloc Thrown if there is not enough memory to 
 *	reprocess the vectors
 *
 * @exceptsafe The function arguments are unchanged in the event of an exception.
 */
void filterLightCurve(double date1, double date2, DoubleVec &times, 
		DoubleVec &arr1, DoubleVec &arr2) {
	DoubleVec::iterator timeStart=times.begin(), 
		arr1Start=arr1.begin(), arr2Start=arr2.begin();
	DoubleVec::iterator firstOk=times.end(), firstNotOk=times.end();
	
	// Find the range we want to keep
	for(DoubleVec::iterator curTime=timeStart; curTime != times.end(); curTime++) {
		if (*curTime >= date1) {
			firstOk = curTime;
			break;
		}
	}
	// firstOk may be equal to end(); that will work [giving no data]
	// date2 may be <= date1; that will also work [giving no data]
	for(DoubleVec::iterator curTime=firstOk; curTime != times.end(); curTime++) {
		if (*curTime > date2) {
			firstNotOk = curTime;
			break;
		}
	}
	
	// firstOk and lastOk are now random access iterators pointing 
	//	to the valid range of elements, 
	//	begin() <= firstOk <= firstNotOk <= end()
	// firstOk == firstNotOk ==> no valid numbers
	if (firstOk == firstNotOk) {
		try {
			throw except::NoValidTimes("No photometry in [" + lexical_cast<string>(date1) 
				+ ", " + lexical_cast<string>(date2) + "]");
		} catch (const boost::bad_lexical_cast &e) {
			throw except::NoValidTimes("No photometry in range");
		}
	} else {
		using std::swap;
		
		size_t offsetNotOk = distance(timeStart, firstNotOk);
		size_t offsetOk    = distance(timeStart, firstOk   );
		
		// copy-and-swap
		vector<double> temp1(arr1), temp2(arr2), tempTimes(times);
		
		// Order matters to avoid invalidating the iterators
		//	Delete back, then front, and delete times last
		temp1    .erase(temp1    .begin()+offsetNotOk, temp1    .end());
		temp1    .erase(temp1    .begin()            , temp1    .begin()+offsetOk);
		temp2    .erase(temp2    .begin()+offsetNotOk, temp2    .end());
		temp2    .erase(temp2    .begin()            , temp2    .begin()+offsetOk);
		tempTimes.erase(tempTimes.begin()+offsetNotOk, tempTimes.end());
		tempTimes.erase(tempTimes.begin()            , tempTimes.begin()+offsetOk);
		
		swap(arr1, temp1);
		swap(arr2, temp2);
		swap(times, tempTimes);
	}
}

}	// end kpfutils
