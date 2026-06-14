cmake_minimum_required(VERSION 3.25)
project(pi_programm)

set(CMAKE_CXX_STANDARD 26)

add_executable(pi_programm main.cpp
        functions/start_programs.hpp
        functions/load_functs.hpp
        functions/play_functs.hpp
        structures/data_structures.hpp
        structures/paths.hpp
        functions/config_functs.hpp)

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/mpv_programs/start_loop.sh
        ${CMAKE_CURRENT_BINARY_DIR}/start_loop.sh
        COPYONLY
)

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/mpv_programs/play_from_path.sh
        ${CMAKE_CURRENT_BINARY_DIR}/play_from_path.sh
        COPYONLY
)

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/mpv_programs/kill_mpv.sh
        ${CMAKE_CURRENT_BINARY_DIR}/kill_mpv.sh
        COPYONLY
)

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/config.cfg
        ${CMAKE_CURRENT_BINARY_DIR}/config.cfg
        COPYONLY
)