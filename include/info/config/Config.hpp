//
// Created by tudom on 2020-01-15.
//

#pragma once

// stdlib
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>

// dependencies
#pragma warning(push, 0)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#include <xercesc/dom/DOM.hpp>
#pragma GCC diagnostic pop
#pragma warning(pop)

// project libs
#include "_api.hpp"
#include "exception.hpp"
#include "Accessor.hpp"

namespace info::config {
  namespace xml = xercesc;

  struct INFO_CONFIG_API Config {
      Config(std::string_view);

      virtual ~Config();

      std::optional<LocalXMLString> get[[nodiscard]](const Accessor&) const;
  private:
      xml::DOMDocument* _doc;
  };
}
