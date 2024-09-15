cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)

option(PRODUCTION_BUILD "Make this a production build" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization

if(MSVC) 
add_compile_options(/arch:AVX2) #make sure SIMD optimizations take place
endif()

project(ParticleSimulation)

set(SDL_STATIC ON)

add_subdirectory(thirdparty/SDL-release-2.30.5)
add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/imgui-docking)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 17)

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC GLFW_INCLUDE_NONE=1) 

if(PRODUCTION_BUILD)
	# setup the ASSETS_PATH macro to be in the root folder of your exe
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") 
 
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1) 

else()
	# This is useful to get an ASSETS_PATH in your IDE during development
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0) 

endif()

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES})

if(MSVC) # If using the VS compiler...

	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)

	#add this line if you want to remove the console!
	#set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") #no console
	
	#set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug<$<CONFIG:Debug>:Debug>")
	#set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

endif()

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

set(RESOURCES_OUTPUT_DIR "${CMAKE_BINARY_DIR}/res")

# Custom command to copy the resources folder
add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/res
    ${RESOURCES_OUTPUT_DIR}
    COMMENT "Copying resources to the build directory."
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GL REQUIRED gl)
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE ${GL_LIBRARIES})
include_directories(${GL_INCLUDE_DIRS})

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm 
    glad SDL2-static imgui)

# target_compile_options(ParticleSimulation PRIVATE -fsanitize=address) # for memory leaks
# target_link_options(ParticleSimulation PRIVATE -fsanitize=address)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_compile_options("${CMAKE_PROJECT_NAME}" PRIVATE -Wall -O3 -ffast-math)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_compile_options("${CMAKE_PROJECT_NAME}" PRIVATE -Wall -O3 -ffast-math -Wextra -pedantic)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  target_compile_options("${CMAKE_PROJECT_NAME}" PRIVATE -Wall -O3  -lGL -ffast-math -Wextra -pedantic)
endif()

