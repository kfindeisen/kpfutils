/** Base exception class analogous to std::runtime_error and std::logic_error
 * @file common/checkedexception.h
 * @author Krzysztof Findeisen
 * @date Created April 22, 2013
 * @date Last modified April 22, 2013
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

#ifndef KPFUTILSEXCEPTH
#define KPFUTILSEXCEPTH

#include <exception>
#include <string>

namespace kpfutils { namespace except {

using std::string;

/** @defgroup exceptions Exception Support
 *
 * General-purpose exceptions
 * 
 * These exceptions cover situations that can appear in any program. Programs 
 * may wish to specialize these exceptions to their own needs.
 * 
 * Include checkedexception.h to inherit from CheckedException. 
 *
 *  @{
 */

/** This is the base class for exceptions thrown by Lightcurve MC that are 
 * foreseeable and can, in principle, be handled at run time. 
 * 
 * This class models the "checked exception" concept from Java. It is 
 * therefore a conceptual sibling to @c std::runtime_error, which is similar to 
 * Java's errors, and @c std::logic_error, which is similar to Java's runtime 
 * exceptions. As such, CheckedException has an analogous interface to 
 * @c std::runtime_error and @c std::logic_error.
 */
class CheckedException : public std::exception {
public:
	/** Constructs a CheckedException object.
	 */
	explicit CheckedException(const string& what_arg);
	virtual ~CheckedException() throw();
	
	/** Returns a null terminated character sequence that may be used to 
	 * identify the exception.
	 */
	virtual const char* what() const throw();

private: 
	string arg;
};

/** @} */	// end exceptions

}}		// end kpfutils::except

#endif		// end ifndef KPFUTILSEXCEPTH
