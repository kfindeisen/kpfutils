/** Exception declarations for light curve operations
 * @file common/lcexcept.h
 * @author Krzysztof Findeisen
 * @date Created July 24, 2013
 * @date Last modified July 24, 2013
 */

#ifndef KPFUTILSNOTIMEEXCEPTH
#define KPFUTILSNOTIMEEXCEPTH

#include <string>
#include "checkedexception.h"

namespace kpfutils { namespace except {

using std::string;

/** @addtogroup lcio
 *
 * These functions read and write light curves to disk.
 * 
 * Include lcexcept.h to catch related exceptions.
 * 
 *  @{
 */

/** Exception thrown when a time series has no data in the requested range
 */
class NoValidTimes: public CheckedException {
public:
	/** Constructs a NoValidTimes object.
	 */
	NoValidTimes(const std::string& what_arg);
};

/** @} */	// end lcio

}}		// end kpfutils::except

#endif		// end ifndef KPFUTILSNOTIMEEXCEPTH
