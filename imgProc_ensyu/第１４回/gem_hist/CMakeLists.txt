cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 11)
project(gem_hist)

find_package(OpenCV 4.0.1 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
file(GLOB SOURCES *.cpp)

add_executable (gem_hist ${SOURCES})
target_link_libraries (gem_hist
	PRIVATE ${OpenCV_LIBS}
)