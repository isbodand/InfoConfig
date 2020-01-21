//
// Created by tudom on 2020-01-20.
//

#include <info/config/exception/ParsingException.hpp>

INFO_CONFIG_API
info::config::parsing_exception::parsing_exception(const info::config::LocalXMLString& msg)
       : _msg(msg) {}

INFO_CONFIG_API
const char* info::config::parsing_exception::what() const noexcept {
    static std::string ret{info_config_exception::what()};

    ret += "Error occurred while parsing the XML: " + static_cast<std::string>(_msg);

    return ret.c_str();
}
