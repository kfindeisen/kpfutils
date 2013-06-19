/** Base exception class analogous to std::runtime_error and std::logic_error
 * @file common/except/exception.h
 * @author Krzysztof Findeisen
 * @date Created April 22, 2013
 * @date Last modified April 22, 2013
 */

#ifndef KPFUTILSEXCEPTH
#define KPFUTILSEXCEPTH

#include <exception>
#include <string>

namespace kpfutils { namespace except {

using std::string;

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

}}		// end kpfutils::except

#endif		// end ifndef KPFUTILSEXCEPTH