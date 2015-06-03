cmake_minimum_required(VERSION 2.6)

project(database)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 0)
set(${PROJECT_NAME}_VERSION_PATCH 1)
set(${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}")
message(STATUS "${PROJECT_NAME} ${${PROJECT_NAME}_VERSION}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -gdwarf2")
#set(CMAKE_ASM_NASM_COMPILER "yasm")

set(SOURCES
  main.cpp
  dbkey.cpp
  dbfilein.cpp
  dbfileout.cpp
  dbfield.cpp
  dbrecord.cpp
  dbiterator.cpp
  )

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${ADDITIONAL_LIBRARIES})
