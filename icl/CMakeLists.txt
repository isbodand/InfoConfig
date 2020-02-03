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

if (INFO_PROJECT_NAME)
    set(_INFO_PROJECT_NAME ${INFO_PROJECT_NAME})
    set(INFO_FIX_PROJECT_NAME Yes)
endif ()
set(INFO_PROJECT_NAME ConfigLanguage)
## BEGIN Project

## CMake Project init
project(Info${INFO_PROJECT_NAME} CXX)

## Project level macros
set(${INFO_PROJECT_NAME}_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

## Initialize target
add_library(icl INTERFACE)

## Get dependencies
find_package(Boost REQUIRED)

## Set target properties
target_include_directories(icl
                           INTERFACE
                           ${${INFO_PROJECT_NAME}_INCLUDE_DIR}
                           ${Boost_INCLUDE_DIRS}
                           )

## END Project
if (INFO_FIX_PROJECT_NAME)
    set(INFO_PROJECT_NAME ${_INFO_PROJECT_NAME})
endif ()
