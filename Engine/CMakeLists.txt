cmake_minimum_required(VERSION 3.10)

project(BizarreEngine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(Engine)

target_include_directories(Engine PUBLIC src include)

file(GLOB_RECURSE _CPP_SRCS src/*.cpp)
file(GLOB_RECURSE _H_SRS src/*.h)

message(STATUS "Engine sources: ${_CPP_SRCS} ${_H_SRCS}")

target_sources(Engine PUBLIC ${_CPP_SRCS} ${_H_SRS})

target_link_libraries(Engine PUBLIC X11 xcb)
