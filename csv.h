/** File I/O functions for CSV tables
 * @file common/csv.h
 * @author Krzysztof Findeisen
 * @date Created July 24, 2011
 * @date Last modified October 25, 2013
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
