//
// Created by tudom on 2020-01-21.
//

#include <iostream>

#include <info/config/Config.hpp>

int main() {
    using namespace info::config::lit;
    // example.xfg
    std::string file{"example.xfg"};

    info::config::Config conf{file};

    auto proj = "example-config"_a / "project";

    auto nameOpt = conf.get(proj / "project-name");
    auto majorOpt = conf.get(proj / "project-version" / "major");
    auto minorOpt = conf.get(proj / "project-version" / "minor");

    if (nameOpt && majorOpt && minorOpt) {
        auto& name = *nameOpt;
        auto& major = *majorOpt;
        auto& minor = *minorOpt;

        std::cout << "Project: " << name
                  << "\nVersion: " << major << "." << minor
                  << std::endl;
    } else {
        std::cout << "Ill-formed configuration file" << std::endl;
    }
}
