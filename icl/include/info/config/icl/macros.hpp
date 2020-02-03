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

#pragma once

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/seq/to_tuple.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/cat.hpp>

#include "pp.hpp"

/**
 * \brief Specializes a template type depending on the char-type it is instantiated with
 * like std::basic_string is.
 *
 * Defines the template's instantiated name in the same schema as std::basic_string<CharT, Traits> is
 * specialized (eg. `std::string` and `std::wstring` for `char` and `wchar_t` respectively).
 *
 * \warning If the type is not a character type (not any of `char`, `wchar_t`, `charN_t` where `N` is
 * `8`, `16`, or `32`) function will fail as such macros do not exist in the pattern matching format.
 *
 * \param ID The identifier of the type to specialize, eg. `string`.
 * \param TYPE The type with which the template type (such as `basic_##ID` eg. `basic_string`) is
 * instantiated.
 */
#define INFO_CONFIG_ICL_SPECIALIZE_NAME(ID, TYPE) INFO_CONFIG_ICL_SPECIALIZED_NAME_##TYPE(ID)
/**
 * \brief Implementation of INFO_CONFIG_ICL_SPECIALIZED_NAME.
 * \sa INFO_CONFIG_ICL_SPECIALIZED_NAME
 */
#define INFO_CONFIG_ICL_SPECIALIZED_NAME_char(ID) ID
/**
 * \brief Implementation of INFO_CONFIG_ICL_SPECIALIZED_NAME.
 * \sa INFO_CONFIG_ICL_SPECIALIZED_NAME
 */
#define INFO_CONFIG_ICL_SPECIALIZED_NAME_wchar_t(ID) w##ID
/**
 * \brief Implementation of INFO_CONFIG_ICL_SPECIALIZED_NAME.
 * \sa INFO_CONFIG_ICL_SPECIALIZED_NAME
 */
#define INFO_CONFIG_ICL_SPECIALIZED_NAME_char8_t(ID) u8##ID
/**
 * \brief Implementation of INFO_CONFIG_ICL_SPECIALIZED_NAME.
 * \sa INFO_CONFIG_ICL_SPECIALIZED_NAME
 */
#define INFO_CONFIG_ICL_SPECIALIZED_NAME_char16_t(ID) u16##ID
/**
 * \brief Implementation of INFO_CONFIG_ICL_SPECIALIZED_NAME.
 * \sa INFO_CONFIG_ICL_SPECIALIZED_NAME
 */
#define INFO_CONFIG_ICL_SPECIALIZED_NAME_char32_t(ID) u32##ID

/******************************************************************************/
/// character type based specialization for types
/**
 * \brief Function-type macro used by the loop of INFO_CONFIG_ICL_SPECIALIZE_TYPE.
 *
 * \sa INFO_CONFIG_ICL_SPECIALIZE_TYPE
 */
#define INFO_CONFIG_ICL_SPECIALIZE_TYPE_R(R, ID, TYPE)\
    INFO_CONFIG_ICL_SPECIALIZE_TYPE_R_I(ID, INFO_CONFIG_ICL_SPECIALIZE_NAME(ID, TYPE), TYPE)

/**
* \brief Implementation of INFO_CONFIG_ICL_SPECIALIZE_TYPE_R
* \sa INFO_CONFIG_ICL_SPECIALIZE_TYPE_R
*/
#define INFO_CONFIG_ICL_SPECIALIZE_TYPE_R_I(ID, SPECIALIZED_ID, TYPE)\
    using SPECIALIZED_ID = basic_##ID<TYPE>;

/**
 * \brief MACRO. Creates std::string like specializations for templates with character
 * type-parameters.
 *
 * Creates using declarations for each char-type specialized template of the given
 * template.
 *
 * This follows the schema of std::basic_string.
 *
 * \param TYPEID The identifier of the to be used as the base specialization for `char`,
 * and is the identifier, which if prefixed with `basic_` results in the template id to specialize.
 */
#define INFO_CONFIG_ICL_SPECIALIZE_TYPE(TYPEID)\
    BOOST_PP_SEQ_FOR_EACH(INFO_CONFIG_ICL_SPECIALIZE_TYPE_R, TYPEID, INFO_PP_CHAR_TYPES)

/******************************************************************************/
/// character type based specialization for parser rules
#define INFO_CONFIG_ICL_SPECIALIZE_PARSER_CLASS(ID, TYPE)\
    BOOST_PP_CAT(parser_, INFO_CONFIG_ICL_SPECIALIZE_NAME(ID, TYPE))

#define INFO_CONFIG_ICL_SPECIALIZE_PARSER(ID, TYPE)\
    BOOST_PP_CAT(INFO_CONFIG_ICL_SPECIALIZE_NAME(ID, TYPE), _)

#define INFO_CONFIG_ICL_SPECIALIZE_X3_R(R, ID, TYPE)\
    INFO_CONFIG_ICL_SPECIALIZE_X3_R_I(\
        INFO_CONFIG_ICL_SPECIALIZE_PARSER_CLASS(ID, TYPE),\
        INFO_CONFIG_ICL_SPECIALIZE_PARSER(ID, TYPE),\
        INFO_CONFIG_ICL_SPECIALIZE_NAME(ID, TYPE)\
    )

#define INFO_CONFIG_ICL_SPECIALIZE_X3_R_I(PARSER_CLASS, PARSER, NAME)\
    x3::rule<class PARSER_CLASS, NAME> PARSER(BOOST_PP_STRINGIZE(NAME));

/**
 * \brief MACRO. Creates character type specialization based Boost.Spirit X3 parser rules.
 */
#define INFO_CONFIG_ICL_SPECIALIZE_X3(TYPEID)\
    BOOST_PP_SEQ_FOR_EACH(INFO_CONFIG_ICL_SPECIALIZE_X3_R, TYPEID, INFO_PP_CHAR_TYPES)

/******************************************************************************/
/// character type based specialization for parser definitions
#define INFO_CONFIG_ICL_SPECIALIZE_PARSER_DEF(ID, TYPE)\
    INFO_CONFIG_ICL_SPECIALIZE_PARSER_DEF_I(ID, TYPE)

#define INFO_CONFIG_ICL_SPECIALIZE_PARSER_DEF_I(ID, TYPE)\
    BOOST_PP_CAT(INFO_CONFIG_ICL_SPECIALIZE_NAME(ID, TYPE), __def)

#define INFO_CONFIG_ICL_SPECIALIZE_X3_DEFS_R(R, INFO, TYPE)\
    INFO_CONFIG_ICL_SPECIALIZE_X3_DEFS_R_I(\
        INFO_CONFIG_ICL_SPECIALIZE_PARSER_DEF(\
            BOOST_PP_SEQ_ELEM(0, INFO),\
            TYPE\
        ),\
        BOOST_PP_SEQ_ELEM(1, INFO)\
    )

#define INFO_CONFIG_ICL_SPECIALIZE_X3_DEFS_R_I(ID, PARSER_CODE)\
    auto ID = PARSER_CODE;

/**
 * \brief MACRO. Creates character type specialization based Boost.Spirit X3 parser
 * definitions.
 */
#define INFO_CONFIG_ICL_SPECIALIZE_X3_DEFS(TYPEID, PARSER_CODE)\
    BOOST_PP_SEQ_FOR_EACH(INFO_CONFIG_ICL_SPECIALIZE_X3_DEFS_R, (TYPEID)(PARSER_CODE), INFO_PP_CHAR_TYPES)

/******************************************************************************/
/// character type based specialization for BOOST_SPIRIT_DEFINE
#define INFO_CONFIG_ICL_SPECIALIZE_PARSER2(S, ID, TYPE)\
    INFO_CONFIG_ICL_SPECIALIZE_PARSER(ID, TYPE)

/**
 * \brief MACRO. Defines character type specialization based Boost.Spirit X3 parser
 * definitions with the BOOST_SPIRIT_DEFINE macro call.
 *
 * \note BOOST_SPIRIT_DEFINE needs to be in scope when the macro is used.
 */
#define INFO_CONFIG_ICL_SPECIALIZE_SPIRIT_DEFINE(TYPEID)\
    INFO_PP_INVOKE(\
        BOOST_SPIRIT_DEFINE,\
        BOOST_PP_SEQ_TO_TUPLE(\
            BOOST_PP_SEQ_TRANSFORM(\
                INFO_CONFIG_ICL_SPECIALIZE_PARSER2,\
                TYPEID,\
                INFO_PP_CHAR_TYPES\
            )\
        )\
    )
