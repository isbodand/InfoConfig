//
// Created by tudom on 2020-01-15.
//

#pragma once

#ifdef _WIN32
#  ifdef INFO_CONFIG_DLL
#    ifdef INFO_CONFIG_BUILD_DLL
#      define INFO_CONFIG_API __declspec(dllexport)
#      define INFO_CONFIG_LOCAL
#    else
#      define INFO_CONFIG_API __declspec(dllimport)
#      define INFO_CONFIG_LOCAL
#    endif
#  else
#    define INFO_CONFIG_API
#    define INFO_CONFIG_LOCAL
#  endif
#else
#  ifdef INFO_CONFIG_DLL
#    ifdef INFO_CONFIG_BUILD_DLL
#      define INFO_CONFIG_API __attribute__((visibility("default")))
#      define INFO_CONFIG_LOCAL __attribute__((visibility("hidden")))
#    else
#      define INFO_CONFIG_API
#      define INFO_CONFIG_LOCAL
#    endif
#  else
#    define INFO_CONFIG_API
#    define INFO_CONFIG_LOCAL
#  endif
#endif
