/** Light curve output functions
 * @file common/lcin.cpp
 * @author Krzysztof Findeisen
 * @date Created February 6, 2011
 * @date Last modified July 25, 2013
 */

/* Copyright 2014, California Institute of Technology.
 *
 * This file is licensed under the BSD 3-Clause License. It is subject to the 
 * license terms in the LICENSE file found in the top-level directory of this 
 * distribution and at http://opensource.org/licenses/BSD-3-Clause. 
 */

#include <algorithm>
#include <utility>
#include <string>
#include <vector>
#include <cstdio>
#include "alloc.tmp.h"
#include "csv.h"
#include "lcio.h"

using namespace std;

/** Removes all (time, data, error) triplets exceeding an error threshold
 * 
 * @param[in] errMax the maximum error to tolerate in a data point
 * @param[in,out] times a vector containing the times of each observation
 * @param[in,out] data a vector containing the measurement (typically flux 
 *	or magnitude) observed at each time
 * @param[in,out] errs a vector containing the error on each measurement
 *
 * @invariant @p times.size() = @p data.size() = @p errs.size()
 * @invariant for all i, @p data[i] &plusmn; @p errs[i] is the 
 *	measurement taken at @p times[i]
 *
 * @post all elements of @p errs exceeding @p errMax are removed, along with 
 *	all corresponding elements of @p times and @p data
 *
 * @exception std::bad_alloc Thrown if there is not enough memory to modify 
 *	the data.
 *
 * @exceptsafe The function arguments are unchanged in the event of an exception.
 *
 * @todo Reimplement using a filter iterator
 */
void errorFilter(double errMax, 
		vector<double>& times, vector<double>& data, vector<double>& errs) {
	// copy-and-swap
	vector<double> tempTimes(times), tempData(data), tempErrs(errs);
	
	for(size_t i = 0; i < tempErrs.size(); ) {
		// loop invariant: tempTimes.size() = tempData.size() = tempErrs.size()
		// loop invariant: for all k, tempData[k] +/- tempErrs[k] is 
		//		the measurement taken at tempTimes[k]
		// loop invariant: all errs[0...i) are <= errMax
		// loop variant: tempErrs.size() - i
		if (tempErrs[i] <= errMax) {
			i++;
		} else {
			tempTimes.erase(tempTimes.begin()+i);
			tempData .erase(tempData .begin()+i);
			tempErrs .erase(tempErrs .begin()+i);
		}
	}
	
	// IMPORTANT: no exceptions beyond this point
	
	swap(times, tempTimes);
	swap(data , tempData);
	swap(errs , tempErrs);
}

/** Sorts the (time, data) pairs in time order
 * 
 * @param[in,out] times a vector containing the times of each observation
 * @param[in,out] data a vector containing the measurement (typically flux 
 *	or magnitude) observed at each time
 *
 * @pre @p times.size() = @p data.size()
 * @post @p times is sorted in ascending order
 * @invariant for all i, @p data[i] is the measurement taken 
 *	at @p times[i]
 *
 * @exception std::bad_alloc Thrown if there is not enough memory to sort 
 *	the data.
 *
 * @exceptsafe The function arguments are unchanged in the event of an exception.
 *
 * @todo Reimplement using a permutation iterator
 */
void sortByTime(vector<double>& times, vector<double>& data) {
	vector<pair<double, double> > sortableVec;
	
	// Pack into a single vector for sorting together
	for(size_t i = 0; i < times.size(); i++) {
		// C++98 can't parse push_back({...}), so break up the expression
		sortableVec.push_back(make_pair(times[i], data[i]));
	}
	
	sort(sortableVec.begin(), sortableVec.end());
	
	// copy-and-swap
	// note: exactly the same number of copies as if we'd copied directly 
	//	from sortableVec to (times, data)
	vector<double> tempTimes, tempData;
	tempTimes.reserve(times.size());
	tempData .reserve(data .size());
	for(vector<pair<double, double> >::const_iterator it = sortableVec.begin(); 
			it != sortableVec.end(); it++) {
		tempTimes.push_back(it->first);
		tempData .push_back(it->second);
	}
	
	// IMPORTANT: no exceptions beyond this point
	
	swap(times, tempTimes);
	swap(data , tempData);
}

/** Allows (time, data, error) triplets to be compared in time order
 */
struct Triple {
	double time;
	double data;
	double error;
};
/** Time order comparison of (time, data, error) triplets
 */
bool operator<(const Triple& first, const Triple& second) {
	return (first.time < second.time);
}

/** Sorts the (time, data, error) triplets in time order
 * 
 * @param[in,out] times a vector containing the times of each observation
 * @param[in,out] data a vector containing the measurement (typically flux 
 *	or magnitude) observed at each time
 * @param[in,out] errs a vector containing the error on each measurement
 *
 * @post @p times is sorted in ascending order
 * @invariant @p times.size() = @p data.size() = @p errs.size()
 * @invariant for all i, @p data[i] &plusmn; @p errs[i] is the 
 *	measurement taken at @p times[i]
 *
 * @exception std::bad_alloc Thrown if there is not enough memory to sort 
 *	the data.
 *
 * @exceptsafe The function arguments are unchanged in the event of an exception.
 *
 * @todo Reimplement using a permutation iterator
 */
void sortByTime(vector<double>& times, vector<double>& data, vector<double>& errs) {
	vector<Triple> sortableVec;
	
	// Pack into a single vector for sorting together
	for(size_t i = 0; i < times.size(); i++) {
		// C++98 can't parse push_back({...}), so break up the expression
		Triple newVal = {times[i], data[i], errs[i]};
		sortableVec.push_back(newVal);
	}
	
	sort(sortableVec.begin(), sortableVec.end());
	
	// copy-and-swap
	// note: exactly the same number of copies as if we'd copied directly 
	//	from sortableVec to (times, data, errs)
	vector<double> tempTimes, tempData, tempErrs;
	tempTimes.reserve(times.size());
	tempData .reserve(data .size());
	tempErrs .reserve(errs .size());
	for(vector<Triple>::const_iterator it = sortableVec.begin(); 
			it != sortableVec.end(); it++) {
		tempTimes.push_back(it->time);
		tempData .push_back(it->data);
		tempErrs .push_back(it->error);
	}
	
	// IMPORTANT: no exceptions beyond this point
	
	swap(times, tempTimes);
	swap(data , tempData);
	swap(errs , tempErrs);
}

namespace kpfutils {

/** Reads a file containing a list of Julian days, measurements, and errors
 * 
 * @param[in] fileName the name of a file to be read. The file 
 *	is assumed to be formatted as a 3xN space-delimited table, 
 *	with the first column a floating point Julian date, the second 
 *	a floating point measurement, and the third a floating point 
 *	measurement error. The file may also contain comment lines 
 *	preceded by '#'.
 * @param[in] errMax the maximum error to tolerate in a data 
 *	point. Any points with an error exceeding @p errMax are ignored.
 * @param[out] timeVec a vector containing the times of each 
 *		observation
 * @param[out] dataVec a vector containing the measurement (typically flux 
 *	or magnitude) observed at each time
 * @param[out] errVec a vector containing the error on each measurement
 *
 * @post @p timeVec is sorted in ascending order
 * @post @p timeVec.size() = @p dataVec.size() = @p errVec.size()
 * @post for all i, @p dataVec[i] &plusmn; @p errVec[i] is the 
 *	measurement taken at @p timeVec[i]
 * @post for all i, @p errVec[i] &le; @p errMax
 *
 * @exception std::bad_alloc Thrown if there is not enough memory to store 
 *	the data.
 * @exception kpfutils::except::FileIo Thrown if any file operation fails.
 *
 * @exceptsafe The function arguments are unchanged in the event of an exception.
 */
void readWgLightCurve(const string& fileName, double errMax, DoubleVec &timeVec, 
		DoubleVec &dataVec, DoubleVec &errVec) {
	// copy-and-swap
	vector<double> tempTimes, tempData, tempErrs;
	
	boost::shared_ptr<FILE> hInput = fileCheckOpen(fileName, "r");

	readTable(hInput.get(), " %lf %lf %lf", tempTimes, tempData, tempErrs);
	errorFilter(errMax, tempTimes, tempData, tempErrs);
	sortByTime(tempTimes, tempData, tempErrs);

	// IMPORTANT: no exceptions beyond this point
	
	swap(timeVec, tempTimes);
	swap(dataVec, tempData );
	swap( errVec, tempErrs );
}

/** Reads a file containing a list of obsids, Julian days, measurements, errors, and limits
 * 
 * @param[in] fileName the name of a file to be read. The file 
 *	is assumed to be formatted as a 5xN space-delimited table, with 
 *	the first column a running index, the second a floating point 
 *	Julian date, the third a floating point measurement, the fourth 
 *	a floating point error, and the fifth a detection limit in the same 
 *	units as the measurement. The file may also contain comment lines 
 *	preceded by '#'.
 * @param[in] errMax the maximum error to tolerate in a data point. Any 
 *	points with an error exceeding @p errMax are ignored.
 * @param[out] timeVec a vector containing the times of each 
 *	observation
 * @param[out] dataVec a vector containing the measurement (typically flux 
 *	or magnitude) observed at each time
 * @param[out] errVec a vector containing the error on each measurement
 *
 * @post @p timeVec is sorted in ascending order
 * @post @p timeVec.size() = @p dataVec.size() = @p errVec.size()
 * @post for all i, @p dataVec[i] &plusmn; @p errVec[i] is the 
 *	measurement taken at @p timeVec[i]
 * @post for all i, @p errVec[i] &le; @p errMax
 *
 * @exception std::bad_alloc Thrown if there is not enough memory to store 
 *	the data.
 * @exception kpfutils::except::FileIo Thrown if any file operation fails.
 *
 * @exceptsafe The function arguments are unchanged in the event of an exception.
 *
 * @bug Current implementation ignores limits.
 */
void readWg2LightCurve(const string& fileName, double errMax, DoubleVec &timeVec, 
		DoubleVec &dataVec, DoubleVec &errVec) {
	// copy-and-swap
	vector<double> tempTimes, tempData, tempErrs;
	
	boost::shared_ptr<FILE> hInput = fileCheckOpen(fileName, "r");

	readTable(hInput.get(), " %*i %lf %lf %lf %*lf", tempTimes, tempData, tempErrs);
	errorFilter(errMax, tempTimes, tempData, tempErrs);
	sortByTime(tempTimes, tempData, tempErrs);

	// IMPORTANT: no exceptions beyond this point
	
	swap(timeVec, tempTimes);
	swap(dataVec, tempData );
	swap( errVec, tempErrs );
}

/** Reads a file containing a list of Julian days and measurements
 * 
 * @param[in] fileName the name of a file to be read. The file 
 *	is assumed to be formatted as a 2xN space-delimited table, 
 *	with the first column a floating point Julian date and the second 
 *	a floating point measurement. The file may also contain comment lines 
 *	preceded by '#'.
 * @param[out] timeVec a vector containing the times of each 
 *	observation
 * @param[out] dataVec a vector containing the measurement (typically flux 
 *	or magnitude) observed at each time
 *
 * @post @p timeVec is sorted in ascending order
 * @post @p timeVec.size() = @p dataVec.size()
 * @post for all i, @p dataVec[i] is the measurement taken at @p timeVec[i]
 *
 * @exception std::bad_alloc Thrown if there is not enough memory to store 
 *	the data.
 * @exception kpfutils::except::FileIo Thrown if any file operation fails.
 *
 * @exceptsafe The function arguments are unchanged in the event of an exception.
 */
void readMcLightCurve(const string& fileName, DoubleVec &timeVec, DoubleVec &dataVec) {
	// copy-and-swap
	vector<double> tempTimes, tempData;
	
	boost::shared_ptr<FILE> hInput = fileCheckOpen(fileName, "r");

	readTable(hInput.get(), " %lf %lf", tempTimes, tempData);
	sortByTime(tempTimes, tempData);

	// IMPORTANT: no exceptions beyond this point
	
	swap(timeVec, tempTimes);
	swap(dataVec, tempData );
}

/** Reads a file containing a list of Julian days and measurements
 * 
 * @param[in] fileName the name of a file to be read. The file 
 *	is assumed to be formatted as a 2xN comma-delimited table, 
 *	with the first column a floating point Julian date and the second 
 *	a floating point measurement. The file may also contain comment lines 
 *	preceded by '#'.
 * @param[out] timeVec a vector containing the times of each 
 *	observation
 * @param[out] dataVec a vector containing the measurement (typically flux 
 *	or magnitude) observed at each time
 *
 * @post @p timeVec is sorted in ascending order
 * @post @p timeVec.size() = @p dataVec.size()
 * @post for all i, @p dataVec[i] is the measurement taken at @p timeVec[i]
 *
 * @exception std::bad_alloc Thrown if there is not enough memory to store 
 *	the data.
 * @exception kpfutils::except::FileIo Thrown if any file operation fails.
 *
 * @exceptsafe The function arguments are unchanged in the event of an exception.
 */
void readCsvLightCurve(const string& fileName, DoubleVec &timeVec, DoubleVec &dataVec) {
	// copy-and-swap
	vector<double> tempTimes, tempData;
	
	boost::shared_ptr<FILE> hInput = fileCheckOpen(fileName, "r");

	readTable(hInput.get(), " %lf , %lf", tempTimes, tempData);
	sortByTime(tempTimes, tempData);

	// IMPORTANT: no exceptions beyond this point
	
	swap(timeVec, tempTimes);
	swap(dataVec, tempData );
}

}	// end kpfutils
