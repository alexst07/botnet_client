##
## Minimum requrired cmake version
##
cmake_minimum_required(VERSION 2.6)

set(PROJECT_NAME botnet)
project(${PROJECT_NAME})

file(GLOB HEADERS "src/*.h")
file(GLOB SOURCES "src/*.cpp")

source_group("Headers" FILES ${HEADERS})

add_executable(	${PROJECT_NAME} ${SOURCES} ${HEADERS})