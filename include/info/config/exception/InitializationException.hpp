//
// Created by tudom on 2020-01-20.
//

#pragma once

// stdlib
#include <string>
#include <exception>

// project
#include "../_api.hpp"
#include "InfoConfigException.hpp"
#include "../LocalXMLString.hpp"

namespace info::config {
  /**
   * \brief Exception class thrown when the xml fails to initialize
   *
   * Exception. The library throws it if/when the handling xml library requires
   * initialization and this routine throws. The message of the original exception is
   * represented in the current message.
   *
   * As of 1.0.0 the only xml library supported is Apache Xerces-C. This is supposed
   * to be lifted in the future using some lunatic trickery.
   */
  struct INFO_CONFIG_API initialization_exception : info_config_exception {
      [[nodiscard]]
      const char* what() const noexcept override;

      initialization_exception(const LocalXMLString&);
  private:
      LocalXMLString _libMessage;
  };
}
