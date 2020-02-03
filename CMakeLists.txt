# ********************************************************************************
# The following file is copyrighted under the BSD 3-Clause license.
# ********************************************************************************
#
# Copyright (c) 2020, bodand
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#   contributors may be used to endorse or promote products derived from
#   this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# ********************************************************************************

cmake_minimum_required(VERSION 3.16)
## Include modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(InfoCUtils)

## Options
option(INFO_CONFIG_BUILD_SHARED "Build the InfoConfig library as a shared object/dll" On)
#option(INFO_CONFIG_BUILD_EXAMPLE "Build the InfoConfig example usage project" Off) todo

NameOption(${INFO_CONFIG_BUILD_SHARED} "SHARED;STATIC" ssInfoConfigBuildType)

project(InfoConfig CXX)

set(INFO_PROJECT_NAME Config)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_SKIP_RPATH FALSE)
set(CMAKE_BUILD_RPATH "$ORIGIN:/lib:/lib64:/usr/lib:/usr/lib64:${CMAKE_BINARY_DIR}:${CMAKE_BUILD_RPATH}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

## Create target library
add_library(xfg ${ssInfoConfigBuildType}
            src/Config.cpp
            src/LocalXMLString.cpp
            src/exception/InfoConfigException.cpp
            src/exception/InitializationException.cpp
            src/exception/ParsingException.cpp
            src/Accessor.cpp
            )
if (INFO_CONFIG_BUILD_SHARED)
    target_compile_options(xfg PUBLIC -DINFO_CONFIG_DLL PRIVATE -DINFO_CONFIG_BUILD_DLL)
endif ()

## Load dependencies
find_package(Boost REQUIRED)

add_subdirectory(libs)
# Xerces-C
list(APPEND lLibraries xerces-c)
SilenceWarnings(xerces-c)
get_property(ssXercesIncludeDir GLOBAL PROPERTY XERCES_INCLUDE)
get_property(ssXercesVersion GLOBAL PROPERTY XERCES_VERSION)
set(ssXercesConfigdIncludeDir
    ${CMAKE_BINARY_DIR}/libs/xerces/xerces-c-${ssXercesVersion}/src
    )

## Target includes
target_include_directories(xfg
                           PUBLIC
                           "${CMAKE_SOURCE_DIR}/include"
                           PRIVATE
                           "${ssXercesIncludeDir}"
                           "${ssXercesConfigdIncludeDir}"
                           "${Boost_INCLUDE_DIR}"
                           )

## Target linkage
target_link_libraries(xfg xerces-c)

if (INFO_CONFIG_BUILD_EXAMPLE)
    add_subdirectory(example)
endif ()
