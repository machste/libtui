cmake_minimum_required(VERSION 3.25)

project(tui
		VERSION 0.1.0
		DESCRIPTION "Terminal User Interface (TUI) Library"
		LANGUAGES C)

find_package(PkgConfig REQUIRED)

pkg_check_modules(MODULES REQUIRED libmasc>=1.6.0 ncurses)

include(GNUInstallDirs)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(UNIX)
    set(CMAKE_INSTALL_PREFIX /usr)
endif(UNIX)

option(DEBUG "Enable Debugging (GDB support and no optimisation)." OFF)
option(LOG_ENABLED "Use logging for more detailed information." ON)

if(DEBUG)
	add_definitions(-O0 -ggdb3 -DDEBUG)
else()
	add_definitions(-Os -g)
endif()
add_definitions(-Wall -Werror -std=gnu11)

file(GLOB HEADERS include/tui/*.h)
file(GLOB_RECURSE SOURCES src/*.c)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "${HEADERS}")

target_include_directories(${PROJECT_NAME} PUBLIC include PRIVATE ${MODULES_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PRIVATE ${MODULES_CFLAGS_OTHER})
target_link_libraries(${PROJECT_NAME} ${MODULES_LIBRARIES})

configure_file(lib${PROJECT_NAME}.pc.in lib${PROJECT_NAME}.pc @ONLY)

configure_file(config.h.in ${PROJECT_BINARY_DIR}/config.h)
add_definitions("-include config.h")

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tui)

install(FILES "include/tui.h" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/lib${PROJECT_NAME}.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

# Setup examples
file(GLOB EXAMPLE_SRCS example/*.c)

foreach(EXAMPLE_SRC ${EXAMPLE_SRCS})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SRC} NAME_WE)

    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SRC})

    target_compile_options(${EXAMPLE_NAME} PRIVATE ${MODULES_CFLAGS_OTHER})
    target_link_libraries(${EXAMPLE_NAME} ${PROJECT_NAME} ${MODULES_LIBRARIES})

    set_target_properties(${EXAMPLE_NAME} PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/example_bin)
endforeach(EXAMPLE_SRC)
