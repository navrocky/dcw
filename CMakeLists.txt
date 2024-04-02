cmake_minimum_required(VERSION 3.5)

project(dcw LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

string(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_UPPERCASE)

if(CMAKE_BUILD_TYPE_UPPERCASE MATCHES "(RELEASE|RELWITHDEBINFO|MINSIZEREL)")
    set(RELEASE_MODE ON)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-comment -Wno-reorder -Werror=return-type -Woverloaded-virtual")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")

if(NOT RELEASE_MODE)
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-comment -Wno-reorder -Werror=return-type -Woverloaded-virtual")
else()
endif()

add_subdirectory(cli)
