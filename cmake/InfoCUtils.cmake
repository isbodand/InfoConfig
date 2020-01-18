# --------------------------------------------------------------------------------
# The following file is copyrighted under the BSD 3-Clause license.
# --------------------------------------------------------------------------------
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
# --------------------------------------------------------------------------------

## Dependency modules
include(CheckCXXCompilerFlag)

## Downloads a file specified in the first parameter to the path specified in the second
## The first param must be a valid URL, and the second a valid path; otherwise
## behaviour is undefined.
function(Download issURL issFilePath issHash)
    file(DOWNLOAD ${issURL} "${issFilePath}"
         STATUS tss.sseDwnStatus
         EXPECTED_HASH ${issHash}
         )
    list(GET tsn.sseDwnStatus 0 snErrorCode)
    list(GET tsn.sseDwnStatus 1 ssErrorMsg)

    if (NOT snErrorCode EQUAL 0)
        get_filename_component(ssFilename "${issFilePath}" NAME)

        message(FATAL_ERROR "${ssFilename}: error during downloading: ${ssErrorMsg}")
    endif ()
endfunction()

## Extracts a .tar.xz file at the specified location. If the file is not of the
## required type, behaviour is undefined.
function(ExtractXZ issFilePath)
    if (WIN32)
        set(EXPFX cmd /c)
    endif ()
    get_filename_component(ssPath "${issFilePath}" DIRECTORY)
    get_filename_component(ssFilename "${issFilePath}" NAME)

    execute_process(
            COMMAND ${EXPFX} cmake -E tar xJf "${ssFilename}"
            WORKING_DIRECTORY "${ssPath}"
    )
endfunction()

## Collects the available warnings and enables all that can be enabled
function(ApplyWarnings issTarget)

    function(CheckWarningFlag isName)
        check_cxx_compiler_flag("-W${isName}" "HasWarning_${isName}")
        set("bHasWarning${isName}" ${HasWarning_${isName}} PARENT_SCOPE)
    endfunction()

    set(lWarnings)

    # Possible warnings to check for
    set(lPossibleWarnings
        # Originating from Clang
        all extra sign-compare switch-enum uninitialized unused cast-qual cast-align
        abstract-vbase-init array-bounds-pointer-arithmetic assign-enum conditional-uninitialized
        consumed deprecated-implementations documentation-deprecated-sync non-virtual-dtor
        header-hygiene infinite-recursion keyword-macro loop-analysis missing-braces
        move newline-eof over-aligned redundant-parens reorder reserved-id-macro sign-conversion
        signed-enum-bitfield sometimes-uninitialized tautological-overlap-compare thread-safety
        undefined-internal-type undefined-reinterpret-cast unneeded-internal-declaration
        unreachable-code-aggressive unreachable-code-loop-increment
        unused-const-variable unused-exception-parameter unused-parameter unused-template unused-variable
        pedantic # -Wpedantic != -pedantic, right?
        no-unknown-pragmas no-unused-macros
        # Additions from GCC
        suggest-attribute=pure suggest-attribute=const suggest-attribute=cold suggest-final-types
        suggest-final-methods duplicated-branches trampolines placement-new=2 redundant-decls logical-op
        # Additions from MSVC
        4
        # User requested
        ${INFO_${INFO_PROJECT_NAME}_ADDITIONAL_WARNINGS} # todo document this
        )

    # -pedantic check
    check_cxx_compiler_flag(-pedantic bHasRawPedantic)
    if (bHasRawPedantic)
        list(APPEND lWarnings -pedantic)
    endif ()

    # check warning flags
    foreach (ssWarning IN LISTS lPossibleWarnings)
        CheckWarningFlag(${ssWarning})
        if (bHasWarning${ssWarning})
            list(APPEND lWarnings -W${ssWarning})
        endif ()
    endforeach ()

    target_compile_options(${issTarget} ${lWarnings})
endfunction()

## Silences all compiler warnings
## Works for: GCC, Clang, and MSVC; possibly others
function(SilenceWarnings issTarget)
    target_compile_options(${issTarget} PRIVATE -w)
endfunction()

## Assigns a string value to a variable depending on the value of the option
function(NameOption ibOptionValue ilOptions ossStringValue)
    if (ibOptionValue)
        list(GET ilOptions 0 ssVal)
    else ()
        list(GET ilOptions 1 ssVal)
    endif ()
    set(${ossStringValue} ${ssVal} PARENT_SCOPE)
endfunction()
