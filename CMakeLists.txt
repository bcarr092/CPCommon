cmake_minimum_required( VERSION 3.0 )

set( PROJECT_NAME "cpcommon" )

project( ${PROJECT_NAME} )

message( STATUS "Project: ${PROJECT_NAME}" )
message( STATUS "Project directory: ${PROJECT_SOURCE_DIR}" )

set( SOURCE_DIR "${PROJECT_SOURCE_DIR}/src" )
set( INCLUDE_DIR "${SOURCE_DIR}/include" )
set( INSTALL_DIR "${CMAKE_BINARY_DIR}/install" )

message( STATUS "Source directory: ${SOURCE_DIR}" )
message( STATUS "Include directory: ${INCLUDE_DIR}" )
message( STATUS "Install directory: ${INSTALL_DIR}" )

set( SOURCES "${SOURCE_DIR}/common/cpcommon.c" )

set( HEADERS "${INCLUDE_DIR}/cpcommon.h" )
LIST( APPEND HEADERS "${INCLUDE_DIR}/types.h" )
LIST( APPEND HEADERS "${INCLUDE_DIR}/target.h" )
LIST( APPEND HEADERS "${INCLUDE_DIR}/darwin/function_map.h" )

message( STATUS "C source files found: ${SOURCES}" )
message( STATUS "C header files found: ${HEADERS}" )

include_directories( ${INCLUDE_DIR} )

add_library( ${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS} )

install( TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION "${INSTALL_DIR}/lib" )
install( FILES ${HEADERS} DESTINATION "${INSTALL_DIR}/include/${PROJECT_NAME}" )
