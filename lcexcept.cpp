/** Exception declarations for light curve operations
 * @file common/lcexcept.cpp
 * @author Krzysztof Findeisen
 * @date Created July 24, 2013
 * @date Last modified July 24, 2013
 */

#include <string>
#include "checkedexception.h"
#include "lcexcept.h"

namespace kpfutils { namespace except {

using std::string;

/** Constructs a NoValidTimes object.
 *
 * @param[in] what_arg A string with the same content as the value 
 *	returned by what().
 *
 * @post this->what() = @p what_arg.c_str()
 *
 * @exception std::bad_alloc Thrown if there is not enough memory to 
 *	construct the exception.
 * 
 * @exceptsafe Object construction is atomic.
 */
NoValidTimes::NoValidTimes(const string& what_arg) : CheckedException(what_arg) {
}

}}		// end kpfutils::except
