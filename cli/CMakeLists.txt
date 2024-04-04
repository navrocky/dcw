set(TARGET dcw)

find_package(args-parser REQUIRED)
find_package(termcolor REQUIRED)
find_package(yaml-cpp REQUIRED)

add_link_options(-static -static-libgcc -static-libstdc++)

if(RELEASE_MODE)
    add_link_options(-s -Os)
endif()

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

    yaml_workspaces_repository.h
    yaml_workspaces_repository.cpp
    commands/add_command.h
    commands/add_command.cpp
    commands/remove_command.h
    commands/remove_command.cpp
    commands/base_command.h
    commands/base_command.cpp
    commands/list_command.h
    commands/list_command.cpp
    commands/up_command.h
    commands/up_command.cpp
    commands/down_command.h
    commands/down_command.cpp
)

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET}
    args-parser::args-parser
    termcolor::termcolor
    yaml-cpp::yaml-cpp
)

include(GNUInstallDirs)
install(TARGETS ${TARGET}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
