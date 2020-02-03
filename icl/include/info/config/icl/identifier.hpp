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

// stdlib
#include <string>
#include <memory>
#include <vector>
#include <utility>

// Boost.Fusion
#include <boost/fusion/adapted/adt/adapt_adt.hpp>

// Boost.Spirit X3
#include <boost/spirit/home/x3.hpp>
namespace x3 = boost::spirit::x3;

// project
#include "macros.hpp"

namespace info::config::icl {
  /**
   * \brief basic_identifier that represents one entity in the configuration.
   *
   * \paragraph A basic_identifier uniquely identifies any entity within any one given InfoConfig
   * configuration script. This can either be a value, a function, or a namespace.
   *
   * \paragraph A basic_identifier may be nested as in contained within a namespace eg. 'Foo:bar' which
   * refers to the bar element of Foo namespace.
   * In case of a nested identifier basic_identifier behaves as a simply linked list with the direction
   * of the linkage pointing to the containing namespace: for example for 'info:scriptor:output:file'
   *   [ file | -> [output | -> [scriptor | -> [info | null]]]].
   *
   * \note Each element contains the their complete path, so nobody panic that the linked list
   * will ultimately destroy performance.
   *
   * \note All standardized overloads from std::string are overloaded for identifier as well.
   *
   * \tparam CharT The character type used by the configuration's encoding. Behaviror is equivalent
   *                to that of std::basic_string
   * \tparam Traits The character traits of the CharT type used to store identifiers.
   *
   * \author bodand
   * \since 1.0.0
   */
  template<class CharT, class Traits = std::char_traits<CharT>>
  struct basic_identifier {
      /**
       * \brief Defines the currently template-instantiated type of basic_identifier
       */
      using self_type = basic_identifier<CharT, Traits>;
      /**
       * \brief The std::basic_string instantiation used by the required template parameters.
       */
      using string_type = std::basic_string<CharT, Traits>;
      /**
       * \brief The type of reference to the string_type.
       *
       * \sa string_type
       */
      using reference_type = string_type&;
      /**
       * \brief A constant reference to string_type.
       *
       * \sa string_type
       */
      using creference_type = string_type const&;

      /**
       * \brief Getter for the value of the identifier. Non-const.
       *
       * \paragraph Returns a reference to the stored value of the identifier. This
       * is a basic_string type appropriated to the supplied template parameters.
       *
       * \note No specific setter exists within an InfoSoft codebase, the non-const
       * reference getters are used for such an internally discouraged practice.
       *
       * \warning nodiscard
       *
       * \return A reference to the identifier value.
       */
      [[nodiscard]]
      reference_type value() noexcept;

      /**
       * \brief Getter for the value of the identifier. Const.
       *
       * \paragraph Returns a reference to the stored value of the identifier. This
       * is a basic_string type appropriated to the supplied template parameters.
       *
       * \note This function exists so that the compiler can safely optimize calls to
       * the getter.
       *
       * \warning nodiscard
       *
       * \return A reference to the identifier value.
       */
      [[nodiscard]]
      creference_type value() const noexcept;

      /**
       * \brief Marks the identifier to be in a scope, changes 'id' to 'scope:id'.
       *
       * \paragraph Enscopes the identifier in the specified scope. Used when flattening the
       * AST, for whatever reason^1.
       *
       * \paragraph This changes 'id' into 'scope:id', and does not interfere with
       * any other value anywhere else.
       *
       * \note (1) AST flattening may be used when the library decides an optimized search
       * tree can be built in some way eg. when their is only one big namespace scope
       * which contains all values.
       *
       * \param scopename The name of the scope to insert the id into.
       */
      void enscope(std::string_view) noexcept;

      /**
       * \brief Removes an optionally specified level of scoping from the identifier.
       * If the target is unscoped operation is nop.
       *
       * \param lvl The levels of scope to strip from the identifier. Default is 1.
       *
       * \return The stripped scope(s), delimited with a colon (`:`) if multiple are stripped.
       */
      std::string stripScope(std::size_t = 1) noexcept;
  private:
      string_type _value; ///< The value of the identifier storing everything, including scopes.
  };

  INFO_CONFIG_ICL_SPECIALIZE_TYPE(identifier);

  template<class CharT, class Traits>
  typename basic_identifier<CharT, Traits>::reference_type
  basic_identifier<CharT, Traits>::value() noexcept {
      return _value;
  }

  template<class CharT, class Traits>
  typename basic_identifier<CharT, Traits>::creference_type
  basic_identifier<CharT, Traits>::value() const noexcept {
      return _value;
  }

  template<class CharT, class Traits>
  void basic_identifier<CharT, Traits>::enscope(std::string_view scopename) noexcept {
      _value.insert(0, scopename);
  }

  template<class CharT, class Traits>
  std::string basic_identifier<CharT, Traits>::stripScope(std::size_t lvl) noexcept {
      std::string ret{};
      for (; lvl != 0; --lvl && !(ret += ':').empty()) {
          auto pos = _value.find(':');
          if (pos == _value.npos) {
              ret.resize(ret.size() - 1);
              return ret;
          }
          ret += _value.substr(0, pos);
          _value = _value.substr(pos + 1);
      }
      return ret;
  }
}

BOOST_FUSION_ADAPT_TPL_ADT(
       (CharT),
       (info::config::icl::basic_identifier) (CharT),
       (obj.value(), obj.value() = val)
)

namespace info::config::icl::parse {
  namespace icl = info::config::icl;
  namespace enc = boost::spirit::x3::ascii;

  using enc::char_;

  INFO_CONFIG_ICL_SPECIALIZE_X3(identifier);

  INFO_CONFIG_ICL_SPECIALIZE_X3_DEFS(identifier,
                                     enc::alpha >> *enc::alnum);

  INFO_CONFIG_ICL_SPECIALIZE_SPIRIT_DEFINE(identifier);
}
