/** File I/O functions for CSV tables
 * @file common/readtable.cpp
 * @author Krzysztof Findeisen
 * @date Created July 25, 2013
 * @date Last modified October 29, 2013
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

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>
#include <boost/algorithm/string.hpp>
#include <boost/smart_ptr.hpp>
#include "alloc.tmp.h"
#include "cerror.h"
#include "csv.h"
#include "fileio.h"

namespace kpfutils {

using namespace std;

/** Reads a file containing two columns of data
 * 
 * @param[in] fileName the name of a file to be read. The file 
 *	is assumed to be formatted as a 2xN table, with each row in the 
 *	format given by @p format. The file may also contain comment lines 
 *	preceded by '#'.
 * @param[in] format a scanf-style formatting string representing a single row 
 *	of the table in @p hInput
 * @param[out] col1, col2 vectors containing the columns of the table
 *
 * @pre <tt>scanf(format, ...)</tt> reads exactly two floating-point values
 *
 * @post @p col1 and @p col2 contain the data contained in the 
 *	two selected columns of @p fileName
 * @post @p col1.size() = @p col2.size()
 *
 * @exception std::bad_alloc Thrown if there is not enough memory to store 
 *	the data.
 * @exception kpfutils::except::FileIo Thrown if any file operation fails.
 *
 * @exceptsafe Program is in a consistent state in the event of an exception.
 */
void readTable(const string& fileName, const string& format, 
		vector<double>& col1, vector<double>& col2) {
	try {
		boost::shared_ptr<FILE> hInput = fileCheckOpen(fileName, "r");
		readTable(hInput.get(), format, col1, col2);
	} catch (const std::runtime_error& e) {
		throw except::FileIo(e.what());
	}
}

/** Reads a file containing two columns of data
 * 
 * @param[in] hInput an open file handle to be read. The file represented 
 *	by @p hInput is assumed to be formatted as a 2xN table, with each 
 *	row in the format given by @p format. The file may also contain 
 *	comment lines preceded by '#'.
 * @param[in] format a scanf-style formatting string representing a single row 
 *	of the table in @p hInput
 * @param[out] col1, col2 vectors containing the columns of the table
 *
 * @pre <tt>scanf(format, ...)</tt> reads exactly two floating-point values
 *
 * @post @p col1 and @p col2 contain the data contained in the 
 *	two selected columns of @p hInput
 * @post @p col1.size() = @p col2.size()
 *
 * @exception std::bad_alloc Thrown if there is not enough memory to store 
 *	the data.
 * @exception kpfutils::except::FileIo Thrown if any file operation fails.
 * @exception std::runtime_error Thrown if file marker becomes invalidated 
 *	during the read
 *
 * @exceptsafe Program is in a consistent state in the event of an exception.
 */
void readTable(FILE* hInput, const string& format, 
		vector<double>& col1, vector<double>& col2) {
	// copy-and-swap
	vector<double> temp1, temp2;
	
	while (!feof(hInput)) {
		// Save start-of-line
		fpos_t curLine;
		if (0 != fgetpos(hInput, &curLine)) {
			cError("Could not save file position: ");
		}
		
		char lineBuffer[256], commentTest;
		int nRead;

		// Test whether it's a comment line
		// Grab the first NON-WHITESPACE character
		nRead = fscanf(hInput, " %1c\n", &commentTest);
		if (nRead == EOF) {
			break;
		} else if (nRead < 1 || ferror(hInput)) {
			fileError(hInput, "While looking for first non-whitespace character on file line: ");
		}
		
		if ('#' == commentTest) {
			// Skip to the next line
			if(NULL == fgets(lineBuffer, 256, hInput)) {
				fileError(hInput, "While reading comment line from file: ");
			}
		} else {
			// Not a comment line, so start over and read it in
			if (0 != fsetpos(hInput, &curLine)) {
				cError("Could not restore file position: ");
			}

			double val1, val2;
			nRead = fscanf(hInput, (format + "\n").c_str(), 
				&val1, &val2);
			if(nRead < 1 || ferror(hInput) || nRead == EOF) {
				fileError(hInput, "Misformatted file: ");
			}

			temp1.push_back(val1);
			temp2.push_back(val2);
		}
	}
	
	// IMPORTANT: no exceptions beyond this point
	
	using std::swap;
	swap(col1, temp1);
	swap(col2, temp2);
}

/** Reads a file containing three columns of data
 * 
 * @param[in] fileName the name of a file to be read. The file 
 *	is assumed to be formatted as a 3xN table, with each row in the 
 *	format given by @p format. The file may also contain comment lines 
 *	preceded by '#'.
 * @param[in] format a scanf-style formatting string representing a single row 
 *	of the table in @p hInput
 * @param[out] col1, col2, col3 vectors containing the columns of the table
 *
 * @pre <tt>scanf(format, ...)</tt> reads exactly three floating-point values
 *
 * @post @p col1, @p col2, and @p col3 contain the data contained in the 
 *	three selected columns of @p fileName
 * @post @p col1.size() = @p col2.size() = @p col3.size()
 *
 * @exception std::bad_alloc Thrown if there is not enough memory to store 
 *	the data.
 * @exception kpfutils::except::FileIo Thrown if any file operation fails.
 *
 * @exceptsafe Program is in a consistent state in the event of an exception.
 */
void readTable(const string& fileName, const string& format, 
		vector<double>& col1, vector<double>& col2, vector<double>& col3) {
	try {
		boost::shared_ptr<FILE> hInput = fileCheckOpen(fileName, "r");
		readTable(hInput.get(), format, col1, col2, col3);
	} catch (const std::runtime_error& e) {
		throw except::FileIo(e.what());
	}
}

/** Reads a file containing three columns of data
 * 
 * @param[in] hInput an open file handle to be read. The file represented 
 *	by @p hInput is assumed to be formatted as a 3xN table, with each 
 *	row in the format given by @p format. The file may also contain 
 *	comment lines preceded by '#'.
 * @param[in] format a scanf-style formatting string representing a single row 
 *	of the table in @p hInput
 * @param[out] col1, col2, col3 vectors containing the columns of the table
 *
 * @pre <tt>scanf(format, ...)</tt> reads exactly three floating-point values
 *
 * @post @p col1, @p col2, and @p col3 contain the data contained in the 
 *	three selected columns of @p hInput
 * @post @p col1.size() = @p col2.size() = @p col3.size()
 *
 * @exception std::bad_alloc Thrown if there is not enough memory to store 
 *	the data.
 * @exception kpfutils::except::FileIo Thrown if any file operation fails.
 * @exception std::runtime_error Thrown if file marker becomes invalidated 
 *	during the read
 *
 * @exceptsafe Program is in a consistent state in the event of an exception.
 */
void readTable(FILE* hInput, const string& format, 
		vector<double>& col1, vector<double>& col2, vector<double>& col3) {
	// copy-and-swap
	vector<double> temp1, temp2, temp3;
	
	while (!feof(hInput)) {
		// Save start-of-line
		fpos_t curLine;
		if (0 != fgetpos(hInput, &curLine)) {
			cError("Could not save file position: ");
		}
		
		char lineBuffer[256], commentTest;
		int nRead;

		// Test whether it's a comment line
		// Grab the first NON-WHITESPACE character
		nRead = fscanf(hInput, " %1c\n", &commentTest);
		if (nRead == EOF) {
			break;
		} else if (nRead < 1 || ferror(hInput)) {
			fileError(hInput, "While looking for first non-whitespace character on file line: ");
		}
		
		if ('#' == commentTest) {
			// Skip to the next line
			if(NULL == fgets(lineBuffer, 256, hInput)) {
				fileError(hInput, "While reading comment line from file: ");
			}
		} else {
			// Not a comment line, so start over and read it in
			if (0 != fsetpos(hInput, &curLine)) {
				cError("Could not restore file position: ");
			}

			double val1, val2, val3;
			nRead = fscanf(hInput, (format + "\n").c_str(), 
				&val1, &val2, &val3);
			if(nRead < 1 || ferror(hInput) || nRead == EOF) {
				fileError(hInput, "Misformatted file: ");
			}

			temp1.push_back(val1);
			temp2.push_back(val2);
			temp3.push_back(val3);
		}
	}
	
	// IMPORTANT: no exceptions beyond this point
	
	using std::swap;
	swap(col1, temp1);
	swap(col2, temp2);
	swap(col3, temp3);
}

}	// end kpfutils
