##
## Minimum requrired cmake version
##
cmake_minimum_required(VERSION 2.6)

set(PROJECT_NAME botnet)
project(${PROJECT_NAME})

add_executable(	${PROJECT_NAME}
				${CMAKE_CURRENT_SOURCE_DIR}/src/http_client.cpp
				${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)