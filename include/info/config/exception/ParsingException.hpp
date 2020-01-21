//
// Created by tudom on 2020-01-20.
//

#pragma once

// stdlib
#include <string>
#include <exception>
#include <info/config/LocalXMLString.hpp>

// project
#include "../_api.hpp"
#include "InfoConfigException.hpp"

namespace info::config {
  struct INFO_CONFIG_API parsing_exception : info_config_exception {
      const char* what() const noexcept override;

      parsing_exception(const LocalXMLString& msg);
  private:
      LocalXMLString _msg;
  };
}
