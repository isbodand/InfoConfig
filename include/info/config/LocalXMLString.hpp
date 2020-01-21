//
// Created by tudom on 2020-01-19.
//

#pragma once

// stdlib
#include <ostream>
#include <memory>

// used dependencies
#pragma warning(push, 0)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#include <xercesc/util/XMLString.hpp>
#pragma GCC diagnostic pop
#pragma warning(pop)

// project headers
#include "_api.hpp"

namespace info::config {
  struct INFO_CONFIG_API LocalXMLString {
      LocalXMLString();
      LocalXMLString(const XMLCh* content);

      virtual ~LocalXMLString();

      operator std::string() const noexcept;
      operator std::string_view() const noexcept;

      INFO_CONFIG_API
      friend std::ostream& operator<<(std::ostream&, LocalXMLString&);
  private:
      char* _content;
  };
}
