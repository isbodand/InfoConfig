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

## Dependencies
include(InfoCUtils)

## Code
set(INFO_CONFIG_DEPENDENCY_DIRECTORY "${CMAKE_SOURCE_DIR}/libs")

##
# Xerces
##
set("${INFO_CONFIG_DEPENDENCY_DIRECTORY}_XERCES" "${INFO_CONFIG_DEPENDENCY_DIRECTORY}/xerces")

if (NOT EXISTS "${${INFO_CONFIG_DEPENDENCY_DIRECTORY}_XERCES}/CMakeLists.txt")
    message(STATUS "Installing Xerces")

    ## Download xerces archive
    if (NOT EXISTS "${${INFO_CONFIG_DEPENDENCY_DIRECTORY}_XERCES}/xerces.tar.xz")
        message(STATUS "Downloading Xerces")

        # Create directory if does not exist
        if (NOT EXISTS "${${INFO_CONFIG_DEPENDENCY_DIRECTORY}_XERCES}")
            file(MAKE_DIRECTORY "${${INFO_CONFIG_DEPENDENCY_DIRECTORY}_XERCES}")
        endif ()

        Download(http://xenia.sote.hu/ftp/mirrors/www.apache.org//xerces/c/3/sources/xerces-c-3.2.2.tar.xz
                 "${${INFO_CONFIG_DEPENDENCY_DIRECTORY}_XERCES}/xerces.tar.xz"
                 SHA256=6daca3b23364d8d883dc77a73f681242f69389e3564543287ed3d073007e0a8e)
    endif ()

    ## Extracting package
    ExtractXZ("${${INFO_CONFIG_DEPENDENCY_DIRECTORY}_XERCES}/xerces.tar.xz")

    ## Creating glue CMakeLists
    # Collecting variables
    file(GLOB ssXercesDirectory
         LIST_DIRECTORIES Yes
         "${${INFO_CONFIG_DEPENDENCY_DIRECTORY}_XERCES}/xerces-c-*")

    string(REGEX MATCH ".\\..\\..$" ssXVersion ${ssXercesDirectory})
    # Fuckin' inferior regex flavor

    # Writing to CMakeLists
    file(WRITE "${${INFO_CONFIG_DEPENDENCY_DIRECTORY}_XERCES}/CMakeLists.txt"
         "add_subdirectory(${ssXercesDirectory})
set_property(GLOBAL PROPERTY XERCES_INCLUDE \"${ssXercesDirectory}/src\")
set_property(GLOBAL PROPERTY XERCES_VERSION ${ssXVersion})")
endif ()

add_subdirectory("${${INFO_CONFIG_DEPENDENCY_DIRECTORY}_XERCES}")
