if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(PLATFORM 64)
else()
	set(PLATFORM 32)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(LIB_PATH "${CMAKE_SOURCE_DIR}/lib/BearLibTerminal/OSX/")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(LIB_PATH "${CMAKE_SOURCE_DIR}/lib/BearLibTerminal/Windows${PLATFORM}/")
else()
	set(LIB_PATH "${CMAKE_SOURCE_DIR}/lib/BearLibTerminal/Linux${PLATFORM}/")
endif()

find_library(BLT_LIBRARY NAME BearLibTerminal PATHS ${LIB_PATH})

find_path(BLT_INCLUDE_DIR BearLibTerminal.h PATHS "${CMAKE_SOURCE_DIR}/lib/BearLibTerminal/include/")

set(BLT_DLL "${LIB_PATH}/BearLibTerminal.dll")