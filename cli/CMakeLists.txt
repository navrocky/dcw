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
    commands/add_command.cpp
    commands/add_command.h
    commands/base_command.h
    commands/down_command.cpp
    commands/down_command.h
    commands/list_command.cpp
    commands/list_command.h
    commands/purge_command.cpp
    commands/purge_command.h
    commands/remove_command.cpp
    commands/remove_command.h
    commands/up_command.cpp
    commands/up_command.h
    compose_executor.cpp
    compose_executor.h
    dcw_config.cpp
    dcw_config.h
    main.cpp
    process_executor.cpp
    process_executor.h
    state_repository.cpp
    state_repository.h
    workspace.h
    workspace_service.cpp
    workspace_service.h
    workspaces_repository.h
    yaml_config.cpp
    yaml_config.h
    yaml_workspaces_repository.cpp
    yaml_workspaces_repository.h
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
