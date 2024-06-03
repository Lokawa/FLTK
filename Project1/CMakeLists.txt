cmake_minimum_required(VERSION 3.24)
project(untitled)

link_libraries(fltk)
link_libraries(fltk_images)
link_libraries(jpeg)
link_libraries(png)
link_libraries(z comctl32)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(untitled  WIN32 main.cpp head.h map.h Draw.h Point.h)
