cmake_minimum_required(VERSION 3.10)
project(particle)

set(CMAKE_CXX_STANDARD 11)
include_directories(include libs/imgui)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ParticleVendored "Use vendored libraries" ON)

if(ParticleVendored)
    add_subdirectory(libs/SDL2 EXCLUDE_FROM_ALL)
else()
    # 1. Look for a SDL2 package, 2. look for the SDL2 component and 3. fail if none can be found
    find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

    # 1. Look for a SDL2 package, 2. Look for the SDL2maincomponent and 3. DO NOT fail when SDL2main is not available
    find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
endif()

# find_package(OpenMP REQUIRED)
# find_package(SDL2 REQUIRED)

set(SOURCES
    src/main.cpp
    src/App.cpp
    src/SDLstuff.cpp
    src/UI.cpp
    src/particle.cpp
    libs/imgui/imgui.cpp
    libs/imgui/imgui_demo.cpp
    libs/imgui/imgui_draw.cpp
    libs/imgui/imgui_widgets.cpp
    libs/imgui/imgui_tables.cpp
    libs/imgui/imgui_impl_sdl2.cpp
    libs/imgui/imgui_impl_sdlrenderer2.cpp
)

add_executable(particle ${SOURCES})
# target_link_libraries(particle SDL2::SDL2 SDL2::SDL2main OpenMP::OpenMP_CXX)
target_link_libraries(particle SDL2::SDL2 SDL2::SDL2main)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_compile_options(particle PRIVATE -Wall -O3 -ffast-math)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_compile_options(particle PRIVATE -Wall -O3 -ffast-math -Wextra -pedantic)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  target_compile_options(particle PRIVATE -Wall -O3 -ffast-math -Wextra -pedantic)
endif()

