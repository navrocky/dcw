set(TARGET dcw)

find_package(termcolor REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(CLI11 REQUIRED)

add_link_options(-static -static-libgcc -static-libstdc++)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

if(RELEASE_MODE)
    add_link_options(-s -Os)
endif()

configure_file(config.h.in config.h)

set(SOURCES
    main.cpp
    yaml_config.h
    yaml_config.cpp
    workspaces_repository.h
    workspace_service.h
    workspace_service.cpp
    state_repository.h
    state_repository.cpp
    process_executor.h
    process_executor.cpp
    compose_executor.h
    compose_executor.cpp
    workspace.h
    dcw_config.h
    dcw_config.cpp

    yaml_workspaces_repository.h
    yaml_workspaces_repository.cpp
    commands/add_command.h
    commands/add_command.cpp
    commands/remove_command.h
    commands/remove_command.cpp
    commands/base_command.h
    commands/list_command.h
    commands/list_command.cpp
    commands/up_command.h
    commands/up_command.cpp
    commands/down_command.h
    commands/down_command.cpp
)

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET}
    termcolor::termcolor
    yaml-cpp::yaml-cpp
    CLI11::CLI11
)

include(GNUInstallDirs)
install(TARGETS ${TARGET}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
