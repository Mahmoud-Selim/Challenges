cmake_minimum_required(VERSION 3.5)
    # require at least gcc 4.8
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "your.required.gcc.version")
    message(FATAL_ERROR "Insufficient gcc version")
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "your.required.msvc.version")
    message(FATAL_ERROR "Insufficient msvc version")
  endif()
elseif(...)
# etc.
endif()
project(Labyrinth)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11")

set(SOURCE_FILES
        main.cpp
        Labyrinth.cpp)

set(HEADER_FILES
        Labyrinth.h)

add_executable(Labyrinth ${SOURCE_FILES} ${HEADER_FILES})