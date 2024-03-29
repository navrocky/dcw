cmake_minimum_required(VERSION 3.5)

project(dcw LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

string(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_UPPERCASE)

if(CMAKE_BUILD_TYPE_UPPERCASE MATCHES "(RELEASE|RELWITHDEBINFO|MINSIZEREL)")
    set(RELEASE_MODE ON)
endif()

add_subdirectory(cli)