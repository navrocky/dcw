cmake_minimum_required(VERSION 3.5)

project(dcw LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

string(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_UPPERCASE)

if(CMAKE_BUILD_TYPE_UPPERCASE MATCHES "(RELEASE|RELWITHDEBINFO|MINSIZEREL)")
    set(RELEASE_MODE ON)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-comment -Wno-reorder -Werror=return-type -Woverloaded-virtual -Wno-unused-parameter")

if(NOT RELEASE_MODE)
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-comment -Wno-reorder -Werror=return-type -Woverloaded-virtual")
else()
endif()

# read version
file(READ "CHANGELOG.md" VERSION_FILE_CONTENT)
string(REGEX REPLACE "^# ([0-9.]+).*$" "\\1" APP_VERSION ${VERSION_FILE_CONTENT})
message(STATUS "App version: " ${APP_VERSION})

# patch files with version
function(patch_version FILE REGEXP)
    file(READ ${FILE} FILE_CONTENT)
    string(REGEX REPLACE ${REGEXP} "\\1${APP_VERSION}\\2" NEW_FILE_CONTENT ${FILE_CONTENT})
    file(WRITE ${FILE} ${NEW_FILE_CONTENT})
endfunction()

patch_version("install.sh" "(releases/download/)[0-9.]+(/dcw)")

add_subdirectory(cli)
