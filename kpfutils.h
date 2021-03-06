/** Mock header for defining module-wide documentation
 * @file common/kpfutils.h
 * @author Krzysztof Findeisen
 * @date Created June 18, 2013
 * @date Last modified February 28, 2014
 */

/* Copyright 2014, California Institute of Technology.
 *
 * This file is licensed under the BSD 3-Clause License. It is subject to the 
 * license terms in the LICENSE file found in the top-level directory of this 
 * distribution and at http://opensource.org/licenses/BSD-3-Clause. 
 */

#ifndef KPFUTILSH
#define KPFUTILSH

/** Current version of the library, for compatibility requirements.
 *
 * @internal "+build" tag can be used to distinguish which development 
 *	version was used to create which output
 */
#define KPFUTILS_VERSION_STRING "1.0.0"

/** Machine-readable version information
 */
#define KPFUTILS_MAJOR_VERSION 1
/** Machine-readable version information
 */
#define KPFUTILS_MINOR_VERSION 0

/** @mainpage
 *
 * @section intro Overview
 *
 * The contents of this directory, and the the @c kpfutils namespace, are not 
 * a single library. Rather, they are a set of common tools and conventions 
 * I use for writing astronomical applications. They are needed to compile 
 * other C++ programs I have written, but are not intended for standalone use.
 *
 * @section legal License
 * 
 * @subsection kpfutils
 *
 * Copyright 2014, California Institute of Technology
 * 
 * Licensed under the BSD 3-Clause License (the "License"). You may obtain a copy 
 * of the License at http://opensource.org/licenses/BSD-3-Clause. A copy is provided 
 * for your convenience in plain text format in <a href="../../LICENSE">common/LICENSE</a>.
 * 
 * @subsection kpfutilstest Test Suite
 *
 * Copyright (C) 2014 California Institute of Technology
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version, subject to the following 
 * exception added under Section 7 of the License:
 *	* Neither the name of the copyright holder nor the names of its contributors 
 *	  may be used to endorse or promote products derived from this software 
 *	  without specific prior written permission.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License 
 * in <a href="../../tests/LICENSE">common/tests/LICENSE</a> 
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @page install Installation
 *
 * @section install_reqs Requirements
 *
 * @c kpfutils is written in standard C++, and should build on any 
 * C++98/C++03-compliant compiler. For portability between build 
 * environments, no TR1 or C++11 features are included. However, the 
 * makefile itself is specific to GCC, so users wishing to install 
 * @c kpfutils on a non-Unix platform may need to revise the contents of 
 * the following files: 
 * - @c makefile
 * - @c makefile.inc
 * - @c makefile.common
 * - @c makefile.subdirs
 * 
 * The library may switch to CMake in the future for improved portability.
 *
 * @c kpfutils depends on the following external libraries:
 * - <a href="http://www.boost.org/">Boost</a> 1.33 or later
 * 
 * Boost is not provided with the installation package, as it is included 
 * with many C++ compilers and operating systems. Please contact your 
 * system administrator if Boost is not installed.
 * 
 * In addition, (re-)generating this documentation requires 
 * <a href="http://www.doxygen.org/">Doxygen</a> 1.8.0 or later.
 *
 * @section install_put File Locations
 *
 * This directory (@c common) should be placed in the same directory as the 
 * build directories of any programs that rely on @c kpfutils. Programs will 
 * look for a <tt>../common/</tt> directory when searching for include files and 
 * when linking to the library.
 * 
 * @section install_make Build Commands
 *
 * Running <tt>make</tt>, with no arguments, will build @c libkpfutils.a in 
 * the @c common directory. Running <tt>make unittest</tt> will build the 
 * unit test suite at @c tests/test. Running <tt>make autotest</tt> will 
 * build the library and the test suite, if neccessary, before running all 
 * tests. Finally, running <tt>make doc</tt> will 
 * generate this documentation at @c doc/html/index.html and 
 * (if you have LaTeX installed) @c doc/latex/refman.pdf, and running 
 * <tt>make all</tt> will generate the library, the test suite, and the 
 * documentation.
 *
 * Since @c libkpfutils.a is a static library intended only for building the 
 * programs in the same directory tree, there is no need to move the file to 
 * a standard library location. Once the library is compiled and tested, 
 * installation is complete.
 *
 *
 * @page changelog Version History
 *
 * @brief <b></b>
 * 
 * @c kpfutils conforms to 
 * <a href="http://semver.org/spec/v2.0.0.html">version 2.0.0 of the Semantic Versioning specification</a>. 
 * All version numbers are to be interpreted as described therein. This 
 * documentation constitutes the public API for the library.
 *
 * @section v1_0_0 Version 1.0.0
 *
 * Initial release.
 * 
 */

/** Common namespace for all components of the library.
 */
namespace kpfutils {}

#endif		// KPFUTILSH
