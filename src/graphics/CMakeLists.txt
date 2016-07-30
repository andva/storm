project(graphics)

file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.cpp)

set(GRAPHICS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CORE_INCLUDE_DIR}
	${SDL_INCLUDE_DIR}
	)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

add_library(graphics ${HEADERS} ${SOURCES})

target_link_libraries(graphics SDL2)