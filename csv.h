/** File I/O functions for CSV tables
 * @file common/csv.h
 * @author Krzysztof Findeisen
 * @date Created July 24, 2011
 * @date Last modified January 14, 2014
 */

/* Copyright 2014, California Institute of Technology.
 *
 * This file is licensed under the BSD 3-Clause License. It is subject to the 
 * license terms in the LICENSE file found in the top-level directory of this 
 * distribution and at http://opensource.org/licenses/BSD-3-Clause. 
 */

#ifndef KPFUTILSCSVH
#define KPFUTILSCSVH

#include <string>
#include <vector>
#include <cstdio>

namespace kpfutils {

using namespace std;

/** @defgroup csv Text Table Support
 *
 * These functions read and write data tables to disk in text format.
 * 
 * Include csv.h to use these functions
 * 
 * @todo Redefine these interfaces in terms of variable argument lists, while 
 * retaining backward compatibility.
 *
 * @{
 */

/** Reads a file containing two columns of data
 */
void readTable(const string& fileName, const string& format, 
		vector<double>& col1, vector<double>& col2);

/** Reads a file containing two columns of data
 */
void readTable(FILE* hInput, const string& format, 
		vector<double>& col1, vector<double>& col2);

/** Reads a file containing three columns of data
 */
void readTable(const string& fileName, const string& format, 
		vector<double>& col1, vector<double>& col2, vector<double>& col3);

/** Reads a file containing three columns of data
 */
void readTable(FILE* hInput, const string& format, 
		vector<double>& col1, vector<double>& col2, vector<double>& col3);

/** Prints a file containing a two-column table
 */	
void printTable(const string& fileName, const string& header, 
		const vector<double>& col1, const vector<double>& col2);

/** Prints a file containing a two-column table
 */	
void printTable(FILE* hOutput, const string& header, 
		const vector<double>& col1, const vector<double>& col2);

/** Prints a file containing a histogram
 */	
void printHist(const string& fileName, const vector<double>& binEdges, const vector<double>& values);

/** Prints a file containing a histogram
 */	
void printHist(FILE* hOutput, const vector<double>& binEdges, const vector<double>& values);

/** @} */	// end lcio

}	// end kpfutils

#endif		// KPFUTILSCSVH
