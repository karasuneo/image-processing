cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 11)
project(final2_src_k21116)

find_package(OpenCV 4.0.1 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
file(GLOB SOURCES *.cpp)

add_executable (final2_src_k21116 ${SOURCES})
target_link_libraries (final2_src_k21116
	PRIVATE ${OpenCV_LIBS}
)