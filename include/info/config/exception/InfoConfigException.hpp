//
// Created by tudom on 2020-01-20.
//

#pragma once

// stdlib
#include <exception>

// project
#include "../_api.hpp"

namespace info::config {
  /**
   * \brief Mother of all InfoConfig exceptions. Abstract.
   *
   * An abstract exception class extended by all exceptions thrown by the InfoConfig
   * library. This class itself, since it is abstract, duh, is not thrown.
   */
  struct INFO_CONFIG_API info_config_exception : std::exception {
      [[nodiscard]]
      const char* what() const noexcept override = 0;
  };
}
