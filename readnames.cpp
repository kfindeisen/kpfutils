/** Functions for reading lists of inputs
 * @file readnames.cpp
 * @author Krzysztof Findeisen
 * @date Created February 6, 2011
 * @date Last modified July 25, 2013
 */

#include <algorithm>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/smart_ptr.hpp>
#include "alloc.tmp.h"
#include "cerror.h"
#include "lcio.h"

using namespace std;

/** Tests whether a character is a newline or not
 *
 * @param[in] x The character to test
 *
 * @return True if @p x represents a newline on Windows, Unix, or MacOS.
 *
 * @exceptsafe Does not throw exceptions.
 */
bool isNewLine(char x) {
	switch (x) {
	case '\r':
	case '\n':
		return true;
	default:
		return false;
	}
}

namespace kpfutils {

/** Reads a file containing a list of file names
 * 
 * @param[in] fileName the name of a file to be read. The file 
 *	is assumed to be formatted as a list of strings, one per 
 *	line.
 * @param[out] fileList a list of strings that stores the filenames in 
 *	@p fileName. The list may be empty.
 *
 * @exception std::bad_alloc Thrown if there is not enough memory to store 
 *	the file list.
 * @exception kpfutils::except::FileIo Thrown if the file has the wrong format.
 *
 * @exceptsafe The function arguments are unchanged in the event of an exception.
 */	
void readFileNames(const string& fileName, vector<string> &fileList) {
	using boost::algorithm::trim_right_copy_if;
	
	// copy-and-swap
	vector<string> temp;

	boost::shared_ptr<FILE> hInput = fileCheckOpen(fileName, "r");

	// Read into dates
	char buffer[250];
	while(!feof(hInput.get())) {
		if(ferror(hInput.get())) {
			fileError(hInput.get(), "Misformatted file: ");
		}
		// Empty line
		if(NULL == fgets(buffer, 250, hInput.get())) {
			continue;
		}
		// Commented line
		if(buffer[0] == '#') {
			continue;
		}
		// use strtrim to remove any trailing newline
		// be careful not to remove spaces, lest there be a 
		//	pathological filename
		temp.push_back(trim_right_copy_if(string(buffer), &isNewLine));
	}
	
	// IMPORTANT: no exceptions beyond this point
	
	swap(fileList, temp);
}

}	// end kpfutils
