//
// Created by tudom on 2020-01-20.
//

#include <info/config/exception/InitializationException.hpp>

INFO_CONFIG_API
const char* info::config::initialization_exception::what() const noexcept {
    static std::string ret{info_config_exception::what()};

    ret += "XML library failed initialization: " + static_cast<std::string>(_libMessage);

    return ret.c_str();
}

INFO_CONFIG_API
info::config::initialization_exception::initialization_exception(
       const info::config::LocalXMLString& libMessage
)
       : _libMessage{libMessage} {}
