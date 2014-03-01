/** Defines macros for overriding compiler warnings
 * @file common/warnflags.h
 * @author Krzysztof Findeisen
 * @date Created April 11, 2013
 * @date Last modified April 11, 2013
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

// The version of G++ being used determines how much finesse I can use to 
//	disable warnings
#if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406
#define GNUC_FINEWARN
#elif ((__GNUC__ * 100) + __GNUC_MINOR__) >= 402
#define GNUC_COARSEWARN
#endif
// Will need a separate set of flags if we're using a different compiler
