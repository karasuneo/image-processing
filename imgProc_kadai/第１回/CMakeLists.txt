cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 11)
project(01_01_face_x21116)

find_package(OpenCV 4.5.1 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
file(GLOB SOURCES *.cpp)

add_executable (01_01_face_x21116 ${SOURCES})
target_link_libraries (01_01_face_x21116
	PRIVATE ${OpenCV_LIBS}
)