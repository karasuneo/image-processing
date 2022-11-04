cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 11)
project(gem_count_black)

find_package(OpenCV 4.0.1 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
file(GLOB SOURCES *.cpp)

add_executable (gem_count_black ${SOURCES})
target_link_libraries (gem_count_black
	PRIVATE ${OpenCV_LIBS}
)