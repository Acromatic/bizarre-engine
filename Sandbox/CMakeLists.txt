cmake_minimum_required(VERSION 3.10)

project(BizarreEngine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Sandbox)

target_link_libraries(Sandbox PUBLIC Engine)

file(GLOB_RECURSE _CPP_SRCS src/*.cpp)
file(GLOB_RECURSE _H_SRCS src/*.h)

message(STATUS "Sandbox sources: ${_CPP_SRCS} ${_H_SRCS}")

target_sources(Sandbox PUBLIC ${_CPP_SRCS} ${_H_SRCS})
