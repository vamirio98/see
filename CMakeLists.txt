cmake_minimum_required(VERSION 3.18)

# set the project name
set(PROJECT_NAME see)
project(${PROJECT_NAME})

set(SEE_VERSION_MAJOR 0)
set(SEE_VERSION_MINOR 1)

# configure a header file to pass some of the Cmake settings to the source code
configure_file(
	"${PROJECT_SOURCE_DIR}/see_config.h.in"
	"${PROJECT_BINARY_DIR}/see_config.h"
	)

# add the binary tree to the search path for include files to find the
# see_config.h
include_directories("${PROJECT_BINARY_DIR}")

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_COMPILER $ENV{CXX})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(".")
file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

# specify target
add_executable(${PROJECT_NAME} ${SRC})
if (WIN32)
	find_package(SDL2 CONFIG REQUIRED)
	find_package(sdl2-image CONFIG REQUIRED)
	target_link_libraries(${PROJECT_NAME}
		PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_image)
else()
	set(CMAKE_CXX_FLAGS "-Wall -O2 -std=c++11")
	set(LINK_LIBRARIES SDL2 SDL2_image)
	target_link_libraries(${PROJECT_NAME} ${LINK_LIBRARIES})
endif()
