cmake_minimum_required(VERSION 3.17)
project(game LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/")
set(CMAKE_CURRENT_BINARY_DIR "${CMAKE_SOURCE_DIR}/bin/")

set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "./")

file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/include/*.h")
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

include_directories("${CMAKE_SOURCE_DIR}/include/")

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

find_package(BearLibTerminal REQUIRED)
include_directories(${BLT_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${BLT_LIBRARY})

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	file(COPY ${BLT_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
else()
	file(COPY ${BLT_LIBRARY} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()