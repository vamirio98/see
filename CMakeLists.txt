# set the project name
set(PROJECT_NAME see)
project(${PROJECT_NAME})
cmake_minimum_required(VERSION 3.18)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_COMPILER $ENV{CXX})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(.)
file(GLOB SRC
	./*.cpp)


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
