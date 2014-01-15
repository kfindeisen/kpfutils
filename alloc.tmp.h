/** Functions converting C-style allocations to C++-style ones
 * @file common/alloc.tmp.h
 * @author Krzysztof Findeisen
 * @date Created May 27, 2013
 * @date Last modified January 14, 2014
 */

#ifndef KPFUTILSALLOCH
#define KPFUTILSALLOCH

#include <string>
#include <cstdio>
#include <boost/smart_ptr.hpp>

namespace kpfutils {

/** @defgroup cstyle C-style Wrappers
 *
 * These functions wrap C++ conventions around C-style code.
 * 
 * Include alloc.tmp.h to wrap resource allocations.
 *
 * @{
 */

/** Wrapper that throws @ref kpfutils::except::FileIo "FileIo" if it cannot open a file
 */
boost::shared_ptr<FILE> fileCheckOpen(const std::string& fileName, const char* mode);

/** Wrapper that throws @c std::bad_alloc if an object was not allocated and 
 *	has no effect otherwise.
 *
 * @tparam T The type of the allocated object.
 *
 * @param[in] p A pointer that is expected to point to a newly allocated 
 *	object of type @p T.
 *
 * @return The pointer @p p, unchanged.
 *
 * @exception std::bad_alloc Thrown if @p p is null.
 *
 * @exceptsafe The function arguments are unchanged in the event of 
 *	an exception.
 */
template <typename T>
T* checkAlloc(T* const p) {
	if (p == NULL) {
		throw std::bad_alloc();
	}
	return p;
}

/** @} */ 	// End alloc

}	// end kpfutils

#endif	// KPFUTILSALLOCH
