cmake_minimum_required(VERSION 3.10)

project(BizarreEngine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

add_subdirectory(Engine)
add_subdirectory(Sandbox)
