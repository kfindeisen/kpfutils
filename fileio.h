/** Exception declarations for file operations
 * @file common/except/fileio.h
 * @author Krzysztof Findeisen
 * @date Created May 8, 2013
 * @date Last modified May 8, 2013
 */

#ifndef KPFUTILSFILEEXCEPTH
#define KPFUTILSFILEEXCEPTH

#include <stdexcept>
#include <string>

namespace kpfutils { namespace except {

using std::string;

/** Exception thrown when a file could not be read or written to.
 */
class FileIo: public std::runtime_error {
public:
	/** Constructs a FileIo object.
	 */
	FileIo(const std::string& what_arg);
};

}}		// end kpfutils::except

#endif		// end ifndef KPFUTILSFILEEXCEPTH
