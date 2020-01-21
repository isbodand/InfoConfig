//
// Created by tudom on 2020-01-20.
//

#include <info/config/exception/InfoConfigException.hpp>

INFO_CONFIG_API
const char* info::config::info_config_exception::what() const noexcept {
    return "InfoConfig: ";
}
