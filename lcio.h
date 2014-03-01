/** File I/O functions for lightcurve analysis tools
 * @file common/lcio.h
 * @author Krzysztof Findeisen
 * @date Created February 4, 2011
 * @date Last modified July 25, 2012
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
