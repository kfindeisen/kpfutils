/** Exception declarations for file operations
 * @file common/fileio.h
 * @author Krzysztof Findeisen
 * @date Created May 8, 2013
 * @date Last modified July 24, 2013
 */

#ifndef KPFUTILSFILEEXCEPTH
#define KPFUTILSFILEEXCEPTH

#include <stdexcept>
#include <string>

namespace kpfutils { namespace except {

using std::string;

/** @addtogroup exceptions
 *
 * General-purpose exceptions.
 * 
 * Include fileio.h to inherit from FileIo.
 * 
 *  @{
 */

/** Exception thrown when a file could not be read or written to.
 */
class FileIo: public std::runtime_error {
public:
	/** Constructs a FileIo object.
	 */
	FileIo(const std::string& what_arg);
};

/** @} */	// end exceptions

}}		// end kpfutils::except

#endif		// end ifndef KPFUTILSFILEEXCEPTH
