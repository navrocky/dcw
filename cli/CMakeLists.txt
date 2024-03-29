set(TARGET dcwm)

find_package(args-parser REQUIRED)
find_package(termcolor REQUIRED)

add_link_options(-static -static-libgcc -static-libstdc++)

if(RELEASE_MODE)
    add_link_options(-s -Os)
endif()

set(SOURCES
    main.cpp
)

add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET}
    args-parser::args-parser
    termcolor::termcolor
)

# include(GNUInstallDirs)
# install(TARGETS ${TARGET}
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
