cmake_minimum_required(VERSION 3.17)
project(game)
set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "./CMake/")
set(CMAKE_CURRENT_BINARY_DIR "./bin/")

add_executable(${PROJECT_NAME} "./src/main.cpp")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(PLATFORM 64)
else()
	set(PLATFORM 32)
endif()

find_package(BearLibTerminal REQUIRED)
include_directories(SYSTEM ${BLT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${BLT_LIBRARIES})

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	file(COPY ${BLT_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# *пытаюсь прицепить путь библиотечки относительно исполняемого файла (в линухе (не получается))*
#else()
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	file(COPY ${BLT_LIBRARY} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()