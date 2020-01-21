//
// Created by tudom on 2020-01-19.
//

#include <info/config/LocalXMLString.hpp>


INFO_CONFIG_API
info::config::LocalXMLString::LocalXMLString(const XMLCh* content) {
    _content = xercesc::XMLString::transcode(content);
}

INFO_CONFIG_API
info::config::LocalXMLString::~LocalXMLString() {
    if (_content != nullptr
        && strcmp(_content, "\0") != 0)
        xercesc::XMLString::release(&_content);
}

INFO_CONFIG_API
info::config::LocalXMLString::operator std::string() const noexcept {
    if (_content != nullptr)
        return {_content};
    return {};
}

INFO_CONFIG_API
info::config::LocalXMLString::operator std::string_view() const noexcept {
    if (_content != nullptr)
        return {_content};
    return {};
}

INFO_CONFIG_API
info::config::LocalXMLString::LocalXMLString()
       : _content{nullptr} {}

INFO_CONFIG_API
std::ostream& info::config::operator<<(std::ostream& os, LocalXMLString& str) {
    os << str._content;
    return os;
}

