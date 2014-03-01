/** File I/O functions for CSV tables
 * @file common/csv.h
 * @author Krzysztof Findeisen
 * @date Created July 24, 2011
 * @date Last modified January 14, 2014
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
