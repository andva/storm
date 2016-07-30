project(storm)
cmake_minimum_required(VERSION 2.8.6)

include(cmake/cotire.cmake)
IF(MSVC)
	LIST(APPEND FLAGS
		/EHsc
		# Compiler warning level 3
		/W3
		# Multi-threaded build
		/MP
		# Enables code analysis and control options.
		/analyze
		# Disable minimal rebuild to not supress warnings in modules
		/Gm-
		# Treat all compiler warnings as errors
		/WX
		)
	ADD_DEFINITIONS(${FLAGS})
ELSE()
	ADD_DEFINITIONS(-std=c++11)
	ADD_DEFINITIONS(-std=c++0x)
ENDIF(MSVC)

add_subdirectory(external)

add_subdirectory(src/hscore)
add_subdirectory(src/graphics)

list(APPEND SOURCES "src/main.cpp")

include_directories(
	${SDL_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
	${CORE_INCLUDE_DIR}
	${GRAPHICS_INCLUDE_DIR}
	)

link_directories(${SDL_LIB_DIR})

add_executable(stormer ${SOURCES})
 FIND_LIBRARY(OpenGL_LIBRARY OpenGL)

target_link_libraries(stormer SDL2 core ${OpenGL_LIBRARY} graphics)
add_dependencies(stormer GLM SDL TINYOBJ)
