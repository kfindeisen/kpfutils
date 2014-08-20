/** Defines macros for overriding compiler warnings
 * @file common/warnflags.h
 * @author Krzysztof Findeisen
 * @date Created April 11, 2013
 * @date Last modified April 11, 2013
 */

/* Copyright 2014, California Institute of Technology.
 *
 * This file is licensed under the BSD 3-Clause License. It is subject to the 
 * license terms in the LICENSE file found in the top-level directory of this 
 * distribution and at http://opensource.org/licenses/BSD-3-Clause. 
 */

// The version of G++ being used determines how much finesse I can use to 
//	disable warnings
#if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406
#define GNUC_FINEWARN
#elif ((__GNUC__ * 100) + __GNUC_MINOR__) >= 402
#define GNUC_COARSEWARN
#endif
// Will need a separate set of flags if we're using a different compiler
