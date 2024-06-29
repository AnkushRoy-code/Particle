cmake_minimum_required(VERSION 3.29.5)
project(particle)

set(CMAKE_CXX_STANDARD 11)
include_directories(include libs/imgui)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(SDL2 REQUIRED)

set(SOURCES
    src/main.cpp
    src/App.cpp
    src/SDLstuff.cpp
    src/UI.cpp
    src/particle.cpp
    src/simulation.cpp
    libs/imgui/imgui.cpp
    libs/imgui/imgui_demo.cpp
    libs/imgui/imgui_draw.cpp
    libs/imgui/imgui_widgets.cpp
    libs/imgui/imgui_tables.cpp
    libs/imgui/imgui_impl_sdl2.cpp
    libs/imgui/imgui_impl_sdlrenderer2.cpp
)

add_executable(particle ${SOURCES})
target_link_libraries(particle SDL2::SDL2 SDL2::SDL2main)
target_compile_options(particle PRIVATE -Wall -Wextra -pedantic)
