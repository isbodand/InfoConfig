//
// Created by tudom on 2020-01-21.
//

#pragma once

// stdlib
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// project
#include "_api.hpp"

namespace info::config {
  struct INFO_CONFIG_API Accessor {
      explicit Accessor(std::vector<std::string>) noexcept;

//      Accessor(const std::string&) noexcept;

      void append(std::string_view) noexcept;
      void prepend(std::string_view) noexcept;

      const std::vector<std::string>& path() const;

      explicit operator std::string() const noexcept;
  private:
      std::vector<std::string> _path;
      friend struct Config;
  };

  namespace lit {
    INFO_CONFIG_API Accessor operator ""_a(const char*, std::size_t) noexcept;
  }

  INFO_CONFIG_API Accessor operator/(std::string_view, const Accessor&) noexcept;
  INFO_CONFIG_API Accessor operator/(const char*, const Accessor&) noexcept;

  INFO_CONFIG_API Accessor operator/(const Accessor&, std::string_view) noexcept;
  INFO_CONFIG_API Accessor operator/(const Accessor&, const char*) noexcept;

  INFO_CONFIG_API Accessor operator/(const Accessor&, const Accessor&) noexcept;
}
