// ********************************************************************************
// The following file is copyrighted under the BSD 3-Clause license.
// ********************************************************************************
//
// Copyright (c) 2020, bodand
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ********************************************************************************
//
// Created by tudom on 2020-02-02.
//

#pragma once

#if defined(__cpp_char8_t)
/**
 * \brief MACRO. Defines the currently supported character types as a Boost.Preprocessor sequence.
 *
 * Defines a sequence of the supported character types.
 *
 * \note The InfoPreprocessor library, from which this is extracted from, does not wish to
 * replace Boost.Preprocessor, only build upon it, therefore, Boost.Preprocessor is heavily advised
 * when using IPP (of course, anything which is API compatible is applicable).
 *
 * \warning This is currently very limited, the only one type which is actually checked
 * for is `char8_t`, others are just assumed to exist (including `char16_t` and `char32_t`).
 * This works if you work with a major compiler, but if something less known has a weird
 * conformance it ~~can~~ will break.
 */
#  define INFO_PP_CHAR_TYPES (char)(wchar_t)(char8_t)(char16_t)(char32_t)
#else
/**
 * \brief MACRO. Defines the currently supported character types as a Boost.Preprocessor sequence.
 *
 * Defines a sequence of the supported character types.
 *
 * \note The InfoPreprocessor library, from which this is extracted from, does not wish to
 * replace Boost.Preprocessor, only build upon it, therefore, Boost.Preprocessor is heavily advised
 * when using IPP (of course, anything which is API compatible is applicable).
 *
 * \warning This is currently very limited, the only one type which is actually checked
 * for is `char8_t`, others are just assumed to exist (including `char16_t` and `char32_t`).
 * This works if you work with a major compiler, but if something less known has a weird
 * conformance it ~~can~~ will break.
 */
#  define INFO_PP_CHAR_TYPES (char)(wchar_t)(char16_t)(char32_t)
#endif

/**
 * \brief MACRO. Invokes the first parameter as a function-type macro,
 * using the second parameter as the macro parameters. The second parameter shall
 * be a Boost.Preprocessor tuple.
 *
 * Uses the second parameter of values as a Boost.Preprocessor tuple type (anything in the form of
 * `(A, B, C)`) and invokes the firs parameter of a macro with those parameter.
 *
 * The two-step indirection is present so it expands passed macro arguments.
 *
 * \note The InfoPreprocessor library, from which this is extracted from, does not wish to
 * replace Boost.Preprocessor, only build upon it, therefore, Boost.Preprocessor is heavily advised
 * when using IPP (of course, anything which is API compatible is applicable).
 *
 * \param MACRO The macro expression which is expandable into a function-type macro name.
 * \param BOOST_PP_TUPLE A tuple of values in the form of a Boost.Preprocessor tuple. This is used
 * as the set of parameters to invoke the macro with.
 */
#define INFO_PP_INVOKE(MACRO, BOOST_PP_TUPLE)\
    INFO_PP_INVOKE_I(MACRO, BOOST_PP_TUPLE)

/**
 * \brief Implementation for INFO_PP_INVOKE
 *
 * \sa INFO_PP_INVOKE(MACRO, BOOST_PP_TUPLE)
 */
#define INFO_PP_INVOKE_I(MACRO, TUPLE)\
    MACRO TUPLE
