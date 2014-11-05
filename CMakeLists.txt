cmake_minimum_required( VERSION 3.0 )

set( PROJECT_NAME "cpcommon" )

project( ${PROJECT_NAME} )

message( STATUS "Project: ${PROJECT_NAME}" )
message( STATUS "Project directory: ${PROJECT_SOURCE_DIR}" )

set( SOURCE_DIR "${PROJECT_SOURCE_DIR}/src" )
set( INCLUDE_DIR "${SOURCE_DIR}/include" )
set( INSTALL_DIR "${CMAKE_INSTALL_PREFIX}" )

message( STATUS "Source directory: ${SOURCE_DIR}" )
message( STATUS "Include directory: ${INCLUDE_DIR}" )
message( STATUS "Install directory: ${INSTALL_DIR}" )

set( SOURCES "${SOURCE_DIR}/common/cpcommon.c" )
list( APPEND SOURCES "${SOURCE_DIR}/common/log.c" )

set( HEADERS "${INCLUDE_DIR}/cpcommon.h" )
list( APPEND HEADERS "${INCLUDE_DIR}/types.h" )
list( APPEND HEADERS "${INCLUDE_DIR}/target.h" )
list( APPEND HEADERS "${INCLUDE_DIR}/log.h" )
list( APPEND HEADERS "${INCLUDE_DIR}/error_codes.h" )
list( APPEND HEADERS "${INCLUDE_DIR}/darwin/function_map.h" )

message( STATUS "C source files found: ${SOURCES}" )
message( STATUS "C header files found: ${HEADERS}" )

include_directories( ${INCLUDE_DIR} )

add_library( ${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS} )

install (
          TARGETS ${PROJECT_NAME}
          ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
          LIBRARY DESTINATION "${INSTALL_DIR}/lib"
        )
install( FILES ${HEADERS} DESTINATION "${INSTALL_DIR}/include/${PROJECT_NAME}" )

# Build test suite as well
add_subdirectory( test )

enable_testing()

find_package( Doxygen )

if( DOXYGEN_FOUND )
  set( DOXYGEN_OUTPUT "${INSTALL_DIR}/doc/${PROJECT_NAME}" )

  configure_file  (
    ${PROJECT_SOURCE_DIR}/Doxyfile.in
    ${PROJECT_BINARY_DIR}/Doxyfile
    @ONLY
                  )
  add_custom_target (
    doc_cpcommon
    ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
                    )

  file( MAKE_DIRECTORY ${DOXYGEN_OUTPUT} )

endif(DOXYGEN_FOUND)

# These are platform specific build instructions, this needs to be cleaned up
find_library( CORE_FOUNDATION_FRAMEWORK CoreFoundation )
find_library( CORE_AUDIO_FRAMEWORK CoreAudio )

set( EXTRA_LIBS ${CORE_FOUNDATION_FRAMEWORK} ${CORE_AUDIO_FRAMEWORK} )

message( STATUS "Framework libraries: ${EXTRA_LIBS}" )

target_link_libraries( ${PROJECT_NAME} ${EXTRA_LIBS} )

set( DARWINHELPER_INCLUDE_DIR "${darwinhelper_SOURCE_DIR}/src/include" )

message (
  STATUS
  "Working with darwinhelper source directory: ${DARWINHELPER_INCLUDE_DIR}"
        )

include_directories( ${DARWINHELPER_INCLUDE_DIR} )

target_link_libraries( ${PROJECT_NAME} darwinhelper )
