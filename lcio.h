/** File I/O functions for lightcurve analysis tools
 * @file common/lcio.h
 * @author Krzysztof Findeisen
 * @date Created February 4, 2011
 * @date Last modified July 25, 2012
 */

/* Copyright 2014, California Institute of Technology.
 *
 * This file is licensed under the BSD 3-Clause License. It is subject to the 
 * license terms in the LICENSE file found in the top-level directory of this 
 * distribution and at http://opensource.org/licenses/BSD-3-Clause. 
 */

#ifndef LCIOH
#define LCIOH

#include <string>
#include <vector>

namespace kpfutils {

using std::string;

/** @defgroup lcio Lightcurve I/O
 *
 * These functions read and write light curves to disk.
 * 
 * Include lcio.h to use these functions
 *
 * @{
 */

/** Shorthand for a vector of doubles
 */
typedef std::vector<double> DoubleVec;

/** Reads a file containing a list of file names
 */
void readFileNames(const string& fileName, std::vector<string> &fileList);

/** Filters a set of vectors to include only dates between @p date1 and @p date2
 */	
void filterLightCurve(double date1, double date2, DoubleVec &times, 
	DoubleVec &arr1, DoubleVec &arr2);

/** Reads a file containing a list of Julian days, measurements, and errors
 */	
void readWgLightCurve(const string& fileName, double errMax, DoubleVec &timeVec, 
	DoubleVec &dataVec, DoubleVec &errVec);

/** Reads a file containing a list of obsids, Julian days, measurements, errors, and limits
 */	
void readWg2LightCurve(const string& fileName, double errMax, DoubleVec &timeVec, 
	DoubleVec &dataVec, DoubleVec &errVec);

/** Reads a file containing a list of Julian days and measurements
 */	
void readMcLightCurve(const string& fileName, DoubleVec &timeVec, 
	DoubleVec &dataVec);

/** Reads a file containing a list of Julian days and measurements
 */	
void readCsvLightCurve(const string& fileName, DoubleVec &timeVec, 
	DoubleVec &dataVec);

/** Prints a file containing a periodogram
 */	
void printPeriodogram(const string& fileName, const DoubleVec &freq, const DoubleVec &power, 
	double threshold, double fap);

/** Prints a file containing an autocorrelation function
 */	
void printAcf(const string& fileName, const DoubleVec &times, const DoubleVec &acf);

/** Prints a file containing a Delta-m Delta-t scatter plot
 */	
void printDmDt(const string& fileName, const DoubleVec &times, const DoubleVec &deltam);

/** Prints a file containing a rms vs t scatter plot
 */	
void printRmsT(const string& fileName, const DoubleVec &times, const DoubleVec &rmsVals);

/** @} */	// end lcio

}	// end kpfutils

#endif
