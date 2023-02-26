cmake_minimum_required(VERSION 3.22)
project(Proiect)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory("${PROJECT_SOURCE_DIR}/Server" "${PROJECT_SOURCE_DIR}/Server_output")
add_subdirectory("${PROJECT_SOURCE_DIR}/Client" "${PROJECT_SOURCE_DIR}/Client_output")
