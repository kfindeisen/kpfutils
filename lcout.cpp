/** Light curve output functions
 * @file common/lcout.cpp
 * @author Krzysztof Findeisen
 * @date Created July 24, 2011
 * @date Last modified July 25, 2013
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

#include <vector>
#include <cstdio>
#include "alloc.tmp.h"
#include "csv.h"
#include "cerror.h"
#include "lcio.h"

namespace kpfutils {

using namespace std;

/** Prints a file containing a periodogram
 * 
 * @param[in] fileName the name of a file to be written to
 * @param[in] freq a vector of frequencies at which the periodogram has been
 *	measured
 * @param[in] power a vector of powers in the periodogram
 * @param[in] threshold the significance threshold
 * @param[in] fap the false alarm probability associated with threshold
 *
 * @pre @p freq.size() = @p power.size()
 * 
 * @post Produces a text file containing two header lines in the format "THRESHOLD: #" 
 *	and "FAP: #", followed by two space-delimited columns 
 *	containing the frequencies and corresponding power.
 *
 * @exception std::invalid_argument Thrown if @p freq.size() &ne; @p power.size()
 * @exception kpfutils::except::FileIo Thrown if any file operation fails.
 *
 * @exceptsafe The function arguments are unchanged in the event of an exception.
 */
void printPeriodogram(const string& fileName, const DoubleVec &freq, const DoubleVec &power, 
		double threshold, double fap) {
	boost::shared_ptr<FILE> hOutput = fileCheckOpen(fileName, "w");

	// Print the FAP value
	if (fap < 0.05) {
		if (fprintf(hOutput.get(), "FAP %.1g%% above %7.1f\n", fap*100.0, threshold) < 0) {
			fileError(hOutput.get(), "Could not print header in printPeriodogram(): ");
		}
	} else {
		if (fprintf(hOutput.get(), "FAP %.0f%% above %7.1f\n", fap*100.0, threshold) < 0) {
			fileError(hOutput.get(), "Could not print header in printPeriodogram(): ");
		}
	}
	
	// Print the table
	printTable(hOutput.get(), "Freq\tPower", freq, power);
//	int status = fprintf(hOutput, "Freq\tPower\n");
//	if (status < 0) {
//		throw std::runtime_error("Could not print periodogram column header.");
//	}
//	for(size_t i = 0; i < freq.size(); i++) {
//		status = fprintf(hOutput, "%7.4f\t%7.4f\n", freq[i], power[i]);
//		if (status < 0) {
//			throw std::runtime_error("Could not print periodogram.");
//		}
//	}
}

/** Prints a file containing an autocorrelation function
 * 
 * @param[in] fileName the name of a file to be written to
 * @param[in] times a vector of time offsets at which the ACF has been measured
 * @param[in] acf a vector of correlations
 *
 * @pre @p times.size() = @p acf.size()
 * 
 * @post Produces a text file containing two space-delimited columns containing the 
 *	offsets and corresponding autocorrelation.
 *
 * @exception std::invalid_argument Thrown if @p times.size() &ne; @p acf.size()
 * @exception kpfutils::except::FileIo Thrown if any file operation fails.
 *
 * @exceptsafe The function arguments are unchanged in the event of an exception.
 */	
void printAcf(const string& fileName, const DoubleVec &times, const DoubleVec &acf) {
	boost::shared_ptr<FILE> hOutput = fileCheckOpen(fileName, "w");

	printTable(hOutput.get(), "Offset\tACF", times, acf);
	// Print the table
//	int status = fprintf(hOutput, "Offset\tACF\n");
//	if (status < 0) {
//		throw std::runtime_error("Could not print ACF column header.");
//	}
//	for(size_t i = 0; i < times.size(); i++) {
//		status = fprintf(hOutput, "%7.4f\t%7.4f\n", times[i], acf[i]);
//		if (status < 0) {
//			throw std::runtime_error("Could not print Acf.");
//		}
//	}
}

/** Prints a file containing a Delta-m Delta-t scatter plot
 * 
 * @param[in] fileName the name of a file to be written to
 * @param[in] deltaT a vector of time differences
 * @param[in] deltaM a vector of magnitude differences
 *
 * @pre @p deltaT.size() = @p deltaM.size()
 * 
 * @post Produces a text file containing two space-delimited columns containing the 
 *	time and magnitude differences, respectively
 *
 * @exception std::invalid_argument Thrown if @p deltaT.size() &ne; @p deltaM.size()
 * @exception kpfutils::except::FileIo Thrown if any file operation fails.
 *
 * @exceptsafe The function arguments are unchanged in the event of an exception.
 */
void printDmDt(const string& fileName, const DoubleVec &deltaT, const DoubleVec &deltaM) {
	boost::shared_ptr<FILE> hOutput = fileCheckOpen(fileName, "w");

	printTable(hOutput.get(), "Offset\tMag Diff.", deltaT, deltaM);
	// Print the table
//	int status = fprintf(hOutput, "Offset\tMag Diff.\n");
//	if (status < 0) {
//		throw std::runtime_error("Could not print dmdt column header.");
//	}
//	for(size_t i = 0; i < times.size(); i++) {
//		status = fprintf(hOutput, "%7.4f\t%7.4f\n", times[i], deltam[i]);
//		if (status < 0) {
//			throw std::runtime_error("Could not print dmdt plot.");
//		}
//	}
}

/** Prints a file containing a rms vs t scatter plot
 * 
 * @param[in] fileName the name of a file to be written to
 * @param[in] times a vector of time differences
 * @param[in] rmsVals a vector of RMS scores
 *
 * @pre @p times.size() &ne; @p rmsVals.size()
 * 
 * @post Produces a text file containing two space-delimited columns containing the 
 *	time and RMS values, respectively
 *
 * @exception std::invalid_argument Thrown if @p times.size() &ne; @p rmsVals.size()
 * @exception kpfutils::except::FileIo Thrown if any file operation fails.
 *
 * @exceptsafe The function arguments are unchanged in the event of an exception.
 */	
void printRmsT(const string& fileName, const DoubleVec &times, const DoubleVec &rmsVals) {
	boost::shared_ptr<FILE> hOutput = fileCheckOpen(fileName, "w");

	printTable(hOutput.get(), "Interval\tRMS", times, rmsVals);
	// Print the table
//	int status = fprintf(hOutput, "Interval\tRMS\n");
//	if (status < 0) {
//		throw std::runtime_error("Could not print RMS header.");
//	}
//	for(size_t i = 0; i < times.size(); i++) {
//		status = fprintf(hOutput, "%7.4f\t%7.4f\n", times[i], rmsVals[i]);
//		if (status < 0) {
//			throw std::runtime_error("Could not print RMS vs t plot.");
//		}
//	}
}

}	// end kpfutils
