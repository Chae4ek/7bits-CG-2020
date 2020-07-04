if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(LIB_PATH "${CMAKE_SOURCE_DIR}/lib/BearLibTerminal/OSX/")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	set(LIB_PATH "${CMAKE_SOURCE_DIR}/lib/BearLibTerminal/Windows${PLATFORM}/")
else()
	set(LIB_PATH "${CMAKE_SOURCE_DIR}/lib/BearLibTerminal/Linux${PLATFORM}/")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	if(MSVC)
		set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
	else()
		set(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")
	endif()
	find_library(BLT_LIBRARY NAME BearLibTerminal PATHS ${LIB_PATH})
else()
	find_library(BLT_LIBRARY NAME BearLibTerminal PATHS ${LIB_PATH})
endif()

find_path(BLT_INCLUDE_DIR BearLibTerminal.h PATHS "${CMAKE_SOURCE_DIR}/lib/BearLibTerminal/include/")

set(BLT_DEFINITIONS "")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(BLT DEFAULT_MSG BLT_LIBRARY BLT_INCLUDE_DIR)

mark_as_advanced(BLT_LIBRARY BLT_INCLUDE_DIR)

set(BLT_INCLUDE_DIRS ${BLT_INCLUDE_DIR})
set(BLT_LIBRARIES ${BLT_LIBRARY})
set(BLT_DLL "${LIB_PATH}/BearLibTerminal.dll")