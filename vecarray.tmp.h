/** Conversion functions between vectors and arrays
 * @file vecarray.tmp.h
 * @author Krzysztof Findeisen
 * @date Created May 26, 2013
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

#include <stdexcept>
#include <vector>
#include <boost/smart_ptr.hpp>

namespace kpfutils {

/** @defgroup vecarray Vector and Array Conversions
 *
 * These functions wrap copying of vectors into arrays and vice versa.
 *
 * Use these functions by including vecarray.tmp.h
 *  @{
 */

/** Returns an array copy of a vector.
 *
 * @tparam T The type of the elements in the vector. Elements must be <a href="http://www.boost.org/doc/libs/release/doc/html/Assignable.html">assignable</a> and <a href="http://www.boost.org/doc/libs/release/doc/html/DefaultConstructible.html">default-constructible</a>.
 *
 * @param[in] vec The vector to copy.
 *
 * @return An array containing the same elements in the same order 
 *	as @p vec.
 *
 * @pre @p vec.size() > 0
 *
 * @exception std::bad_alloc Thrown if could not allocate the array.
 * @exception std::length_error Thrown if attempted to create 
 *	a length-0 array.
 *
 * @exceptsafe The function arguments are unchanged in the event 
 *	of an exception.
 */
template <typename T>
boost::shared_array<T> vecToArr(const std::vector<T>& vec) {
	size_t n = vec.size();
	if (n <= 0) {
		throw std::length_error("Empty vector passed to vecToArray().");
	}
	
	boost::shared_array<T> arr(new T[n]);
	for(size_t i = 0; i < n; i++) {
		arr[i] = vec[i];
	}
	
	return arr;
}

/** Returns a vector copy of an array.
 *
 * @tparam T The type of the elements in the array. Elements must be <a href="http://www.boost.org/doc/libs/release/doc/html/Assignable.html">assignable</a> and <a href="http://www.boost.org/doc/libs/release/doc/html/DefaultConstructible.html">default-constructible</a>.
 *
 * @param[in] arr,n The array to copy.
 *
 * @pre @p n > 0
 *
 * @return A vector containing the same elements in the same order 
 *	as @p arr.
 *
 * @exception std::bad_alloc Thrown if could not allocate the array.
 *
 * @exceptsafe The function arguments are unchanged in the event 
 *	of an exception.
 */
template <typename T>
std::vector<T> arrToVec(const T arr[], size_t n) {
	std::vector<T> vec;
	vec.reserve(n);
	
	for(size_t i = 0; i < n; i++) {
		vec.push_back(arr[i]);
	}
	
	return vec;
}

/** @} */	// end conversion

}	// end kpfutils
