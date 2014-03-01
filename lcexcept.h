/** Exception declarations for light curve operations
 * @file common/lcexcept.h
 * @author Krzysztof Findeisen
 * @date Created July 24, 2013
 * @date Last modified July 24, 2013
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
