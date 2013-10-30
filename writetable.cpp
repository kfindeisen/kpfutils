/** File I/O functions for CSV tables
 * @file common/writetable.cpp
 * @author Krzysztof Findeisen
 * @date Created July 24, 2011
 * @date Last modified October 29, 2013
 */

#include <stdexcept>
#include <vector>
#include <cstdio>
#include <boost/lexical_cast.hpp>
#include <boost/smart_ptr.hpp>
#include "alloc.tmp.h"
#include "cerror.h"
#include "csv.h"
#include "fileio.h"

namespace kpfutils {

using namespace std;
using boost::lexical_cast;

/** Prints a file containing a two-column table
 * 
 * @param[in] fileName an the name of a file to be written to
 * @param[in] header a string to be printed at the start of the file
 * @param[in] col1, col2 vectors of values to print
 *
 * @pre @p col1.size() = @p col2.size()
 * 
 * @post Produces a text file containing two space-delimited columns. If the 
 *	 file already exists, it is replaced.
 *
 * @exception std::invalid_argument Thrown if @p col1.size() &ne; @p col2.size()
 * @exception kpfutils::except::FileIo Thrown if any file operation fails.
 *
 * @exceptsafe Program is in a consistent state in the event of an exception.
 */
void printTable(const string& fileName, const string& header, 
		const vector<double>& col1, const vector<double>& col2) {
	try {
		boost::shared_ptr<FILE> hOutput = fileCheckOpen(fileName, "w");
		printTable(hOutput.get(), header, col1, col2);
	} catch (const std::runtime_error& e) {
		throw except::FileIo(e.what());
	}
}

/** Prints a file containing a two-column table
 * 
 * @param[in] hOutput an open file handle to be written to
 * @param[in] header a string to be printed at the start of the file
 * @param[in] col1, col2 vectors of values to print
 *
 * @pre @p col1.size() = @p col2.size()
 * 
 * @post Produces a text file containing two space-delimited columns
 *
 * @exception std::invalid_argument Thrown if @p col1.size() &ne; @p col2.size()
 * @exception kpfutils::except::FileIo Thrown if any file operation fails.
 *
 * @exceptsafe Program is in a consistent state in the event of an exception.
 */
void printTable(FILE* hOutput, const string& header, 
		const vector<double>& col1, const vector<double>& col2) {
	if (col1.size() != col2.size()) {
		try {
			throw invalid_argument("Mismatched vectors passed to printTable() (gave " 
				+ lexical_cast<string>(col1.size()) + " and " 
				+ lexical_cast<string>(col2.size()) + ")");
		} catch (const boost::bad_lexical_cast& e) {
			throw std::invalid_argument("Mismatched vectors passed to printTable()");
		}
	}

	// Header first
	if (fprintf(hOutput, (header + "\n").c_str()) < 0) {
		fileError(hOutput, "Could not print header in printTable(): ");
	}

	// Data
	for(size_t i = 0; i < col1.size(); i++) {
		if (fprintf(hOutput, "%7.4f\t%7.4f\n", col1[i], col2[i]) < 0) {
			fileError(hOutput, "Could not print data in printTable(): ");
		}
	}
}

/** Prints a file containing a histogram
 * 
 * @param[in] fileName the name of a file to be written to
 * @param[in] binEdges a vector of starting and ending bin edges
 * @param[in] values a vector of bin heights
 * 
 * @pre @p binEdges.size() = @p values.size()+1
 * @pre for all i, @p values[i] is the number of items between binEdges[i] and binEdges[i+1]
 * 
 * @post Produces a text file containing two space-delimited columns containing the 
 *	bin edges and values, respectively. If the file already exists, it is replaced.
 *
 * @exception std::invalid_argument Thrown if @p binEdges.size() &ne; @p values.size()+1
 * @exception kpfutils::except::FileIo Thrown if any file operation fails.
 *
 * @exceptsafe Program is in a consistent state in the event of an exception.
 */
void printHist(const string& fileName, 
		const vector<double>& binEdges, const vector<double>& values) {
	try {
		boost::shared_ptr<FILE> hOutput = fileCheckOpen(fileName, "w");
		printHist(hOutput.get(), binEdges, values);
	} catch (const std::runtime_error& e) {
		throw except::FileIo(e.what());
	}
}

/** Prints a file containing a histogram
 * 
 * @param[in] hOutput an open file handle to be written to
 * @param[in] binEdges a vector of starting and ending bin edges
 * @param[in] values a vector of bin heights
 * 
 * @pre @p binEdges.size() = @p values.size()+1
 * @pre for all i, @p values[i] is the number of items between binEdges[i] and binEdges[i+1]
 * 
 * @post Produces a text file containing two space-delimited columns containing the 
 *	bin edges and values, respectively
 *
 * @exception std::invalid_argument Thrown if @p binEdges.size() &ne; @p values.size()+1
 * @exception kpfutils::except::FileIo Thrown if any file operation fails.
 *
 * @exceptsafe Program is in a consistent state in the event of an exception.
 */
void printHist(FILE* hOutput, const vector<double>& binEdges, const vector<double>& values) {
	if (binEdges.size() != values.size()+1) {
		try {
			throw invalid_argument("Mismatched vectors passed to printHist() (gave " 
				+ lexical_cast<string>(binEdges.size()) + " and " 
				+ lexical_cast<string>(values.size()) + ")");
		} catch (const boost::bad_lexical_cast& e) {
			throw std::invalid_argument("Mismatched vectors passed to printHist()");
		}
	}

	// Header first
	if (fprintf(hOutput, "Bin Start\tValue\n") < 0) {
		fileError(hOutput, "Could not print header in printHist(): ");
	}

	// Data
	for(size_t i = 0; i < values.size(); i++) {
		if (fprintf(hOutput, "%7.4f\t%7.4f\n", binEdges[i], values[i]) < 0) {
			fileError(hOutput, "Could not print data in printHist(): ");
		}
	}
	// Last bin edge needs special treatment
	if (fprintf(hOutput, "%7.4f\n", binEdges[values.size()]) < 0) {
		fileError(hOutput, "Could not print data in printHist(): ");
	}
}

}	// end kpfutils
