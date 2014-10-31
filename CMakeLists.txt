cmake_minimum_required( VERSION 3.0 )

set( PROJECT_NAME "cpcommon" )

project( ${PROJECT_NAME} )

message( STATUS "Project directory: ${PROJECT_SOURCE_DIR}" )

set( SOURCE_DIRECTORY "${PROJECT_SOURCE_DIR}/src" )
set( INCLUDE_DIRECTORY "${SOURCE_DIRECTORY}/include" )

message( STATUS "Working with source directory: ${SOURCE_DIRECTORY}" )
message( STATUS "Working with include directory: ${INCLUDE_DIRECTORY}" )

set( SOURCES "${SOURCE_DIRECTORY}/common/cpcommon.c" )

set( HEADERS "${INCLUDE_DIRECTORY}/cpcommon.h" )
LIST( APPEND HEADERS "${INCLUDE_DIRECTORY}/types.h" )
LIST( APPEND HEADERS "${INCLUDE_DIRECTORY}/target.h" )
LIST( APPEND HEADERS "${INCLUDE_DIRECTORY}/darwin/function_map.h" )

message( STATUS "C source files found: ${SOURCES}" )
message( STATUS "C header files found: ${HEADERS}" )

add_library( ${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS} )

install( TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION "lib" )
install( FILES ${HEADERS} DESTINATION "include/${PROJECT_NAME}" )
