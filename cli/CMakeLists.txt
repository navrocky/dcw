set(TARGET dcw)

find_package(args-parser REQUIRED)
find_package(termcolor REQUIRED)
find_package(Boost REQUIRED)
find_package(yaml-cpp REQUIRED)

add_link_options(-static -static-libgcc -static-libstdc++)

if(RELEASE_MODE)
    add_link_options(-s -Os)
endif()

set(SOURCES
    main.cpp
    workspaces_repository.h
    workspaces_repository.cpp
    add_command.h
    add_command.cpp
    base_command.h
    base_command.cpp
    yaml_workspaces_repository.h
    yaml_workspaces_repository.cpp
)

add_executable(${TARGET} ${SOURCES}
    yaml_config.h yaml_config.cpp
    list_command.h list_command.cpp
    switch_command.h switch_command.cpp)

target_link_libraries(${TARGET}
    args-parser::args-parser
    termcolor::termcolor
    boost::boost
    yaml-cpp::yaml-cpp
)

include(GNUInstallDirs)
install(TARGETS ${TARGET}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
