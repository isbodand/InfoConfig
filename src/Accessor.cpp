//
// Created by tudom on 2020-01-21.
//

#include <info/config/Accessor.hpp>

// stdlib
#include <utility>
#include <sstream>
// dependencies
#include <boost/algorithm/string.hpp>

INFO_CONFIG_API
info::config::Accessor::Accessor(std::vector<std::string> path) noexcept
       : _path{std::move(path)} {}

//INFO_CONFIG_API
//info::config::Accessor::Accessor(const std::string& path) noexcept
//       : _path{} {
//    boost::split(_path, path, [](char c) { return c == '/'; });
//}

INFO_CONFIG_API
info::config::Accessor::operator std::string() const noexcept {
    std::ostringstream ss;
    for (auto&& frag : _path) {
        ss << '/' << frag;
    }
    return ss.str();
}

void info::config::Accessor::append(std::string_view frag) noexcept {
    _path.emplace_back(frag.data());
}

void info::config::Accessor::prepend(std::string_view frag) noexcept {
    _path.emplace(_path.begin(), frag.data());
}

const std::vector<std::string>& info::config::Accessor::path() const {
    return _path;
}

INFO_CONFIG_API
info::config::Accessor info::config::operator/(std::string_view frag,
                                               const Accessor& acc) noexcept {
    return operator/(frag.data(), acc);
}

INFO_CONFIG_API
info::config::Accessor info::config::operator/(const char* frag,
                                               const Accessor& acc) noexcept {
    Accessor cp{acc};
    cp.append(frag);
    return cp;
}

INFO_CONFIG_API
info::config::Accessor info::config::operator/(const Accessor& acc,
                                               std::string_view frag) noexcept {
    return operator/(frag.data(), acc);
}

info::config::Accessor info::config::operator/(const info::config::Accessor& acc,
                                               const char* frag) noexcept {
    Accessor cp{acc};
    cp.append(frag);
    return cp;
}

INFO_CONFIG_API
info::config::Accessor info::config::operator/(const Accessor& acc1,
                                               const Accessor& acc2) noexcept {
    Accessor ret{acc1};
    for (auto&& frag : acc2.path()) {
        ret.append(frag);
    }
    return ret;
}

INFO_CONFIG_API
info::config::Accessor info::config::lit::operator ""_a(const char* str, std::size_t len) noexcept {
    std::vector<std::string> frags;
    boost::split(frags, std::string{str, len}, [](char c) { return c == '/'; });
    return Accessor{frags};
}
