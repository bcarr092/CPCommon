cmake_minimum_required( VERSION 3.0 )

set( PROJECT_NAME "cpcommon_tests" )

project( ${PROJECT_NAME} )

message( STATUS "Project: ${PROJECT_NAME}" )
message( STATUS "Project directory: ${PROJECT_SOURCE_DIR}" )

set( SOURCE_DIR "${PROJECT_SOURCE_DIR}/src" )
set( INCLUDE_DIR "${SOURCE_DIR}/include" )
set( INSTALL_DIR "${CMAKE_BINARY_DIR}/install" )

message( STATUS "Source directory: ${SOURCE_DIR}" )
message( STATUS "Include directory: ${INCLUDE_DIR}" )
message( STATUS "Install directory: ${INSTALL_DIR}" )

set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM BOTH )
set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH )
set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH )

find_package( SWIG REQUIRED )
find_package( PythonLibs REQUIRED )

set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )

include( ${SWIG_USE_FILE} )

set( CPCOMMON_INCLUDE_DIRECTORY "${cpcommon_SOURCE_DIR}/src/include" )

include_directories( ${CPCOMMON_INCLUDE_DIRECTORY} )
include_directories( ${PYTHON_INCLUDE_PATH} )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

swig_add_module( ${PROJECT_NAME} python "${PROJECT_NAME}.i" )
swig_link_libraries( ${PROJECT_NAME} ${PYTHON_LIBRARIES} cpcommon )

set( SCRIPTS "${PROJECT_SOURCE_DIR}/test.py" )

set( WRAPPERS "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.py" )

message( STATUS "Copying scripts: ${SCRIPTS}" )
message( STATUS "Copying wrappers: ${WRAPPERS}" )

foreach( FILE_TO_COPY IN ITEMS ${SCRIPTS} )
    message( STATUS "Copying script ${FILE_TO_COPY} to ${PROJECT_BINARY_DIR}" )
    
    add_custom_command( TARGET "_${PROJECT_NAME}" PRE_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                        "${FILE_TO_COPY}" "${PROJECT_BINARY_DIR}" )
                        
endforeach( FILE_TO_COPY )

install(  TARGETS "_${PROJECT_NAME}" DESTINATION
          "${INSTALL_DIR}/tests/${PROJECT_NAME}" )
install(  PROGRAMS ${SCRIPTS} DESTINATION
          "${INSTALL_DIR}/tests/${PROJECT_NAME}" )
install(  FILES ${WRAPPERS} DESTINATION
          "${INSTALL_DIR}/tests/${PROJECT_NAME}" )

enable_testing()

add_test( ${PROJECT_NAME} "${PROJECT_BINARY_DIR}/test.py" )

# These are platform specific build instructions, this needs to be cleaned up
find_library( CORE_FOUNDATION_FRAMEWORK CoreFoundation )
find_library( CORE_AUDIO_FRAMEWORK CoreAudio )

set( EXTRA_LIBS ${CORE_FOUNDATION_FRAMEWORK} ${CORE_AUDIO_FRAMEWORK} )

message( STATUS "Framework libraries: ${EXTRA_LIBS}" )

swig_link_libraries( ${PROJECT_NAME} ${EXTRA_LIBS} )
