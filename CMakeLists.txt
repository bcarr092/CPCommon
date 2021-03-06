cmake_minimum_required( VERSION 3.0 )

set( PROJECT_NAME "cpcommon" )

project( ${PROJECT_NAME} )

message( STATUS "Project: ${PROJECT_NAME}" )
message( STATUS "Project directory: ${PROJECT_SOURCE_DIR}" )

set( SOURCE_DIR "${PROJECT_SOURCE_DIR}/src" )
set( INCLUDE_DIR "${SOURCE_DIR}/include" )
set( INSTALL_DIR "${CMAKE_INSTALL_PREFIX}" )
set (
    INSTALL_LIB_DIR
    "${INSTALL_DIR}/lib/${PLATFORM}/${TARGET}/${ARCHITECTURE}"
    )

message( STATUS "Source directory: ${SOURCE_DIR}" )
message( STATUS "Include directory: ${INCLUDE_DIR}" )
message( STATUS "Install directory: ${INSTALL_DIR}" )

set( SOURCES "${SOURCE_DIR}/common/cpcommon.c" )
list( APPEND SOURCES "${SOURCE_DIR}/common/log.c" )

set( HEADERS "${INCLUDE_DIR}/cpcommon.h" )
list( APPEND HEADERS "${INCLUDE_DIR}/types.h" )
list( APPEND HEADERS "${INCLUDE_DIR}/target.h" )
list( APPEND HEADERS "${INCLUDE_DIR}/log_functions.h" )
list( APPEND HEADERS "${INCLUDE_DIR}/log_definitions.h" )
list( APPEND HEADERS "${INCLUDE_DIR}/cpcommon_error_codes.h" )

if( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" )
  list( APPEND HEADERS "${INCLUDE_DIR}/darwin/function_map.h" )

  list( APPEND SOURCES "${SOURCE_DIR}/darwin/functions.c" )
elseif( ${PLATFORM} STREQUAL "Generic" AND ${TARGET} MATCHES "^android" )
  find_library  (
                  MATH_LIB
                  m
                  HINTS "${CMAKE_FIND_ROOT_PATH}/usr/lib"
                )

  set (
        EXTRA_LIBS
        ${OPENSLES_LIB}
        ${MATH_LIB}
      )

  message( STATUS "Android libraries: ${EXTRA_LIBS}" )

  list( APPEND HEADERS "${INCLUDE_DIR}/android/function_map.h" )

  list( APPEND SOURCES "${SOURCE_DIR}/android/functions.c" )
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Windows" )
  find_library  (
                  WS2_32_LIB
                  Ws2_32 
                )
  #find_library  (
                  #MSVCRTD_LIB
                  #msvcrtd
                  #HINTS "${CMAKE_FIND_ROOT_PATH}/lib"
                #)

  set (
        EXTRA_LIBS
        ${WS2_32_LIB}
      )

  if( DEFINED MSVCRTD_LIB )
    list( APPEND EXTRA_LIBS ${MSVCRTD_LIB} )
  endif()

  message( STATUS "Windows libraries: ${EXTRA_LIBS}" )

  list( APPEND HEADERS "${INCLUDE_DIR}/windows/function_map.h" )

  list( APPEND SOURCES "${SOURCE_DIR}/windows/functions.c" )
else()
  message( FATAL_ERROR "Unsupported platform: ${PLATFORM}" )
endif()

message( STATUS "C source files found: ${SOURCES}" )
message( STATUS "C header files found: ${HEADERS}" )

include_directories( ${INCLUDE_DIR} )

add_library( ${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS} )

if( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" )
  target_link_libraries( ${PROJECT_NAME} darwinhelper )

  set( DARWINHELPER_INCLUDE_DIR "${darwinhelper_SOURCE_DIR}/src/include" )

  message (
    STATUS
    "Working with darwinhelper source directory: ${DARWINHELPER_INCLUDE_DIR}"
          )
  
  include_directories( ${DARWINHELPER_INCLUDE_DIR} )
endif()

target_link_libraries( ${PROJECT_NAME} ${EXTRA_LIBS} )

install (
          TARGETS ${PROJECT_NAME}
          ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
          LIBRARY DESTINATION "${INSTALL_LIB_DIR}"
        )
install( FILES ${HEADERS} DESTINATION "${INSTALL_DIR}/include/${PROJECT_NAME}" )

# Build test suite as well
#add_subdirectory( test )

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
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Generating API documentation with Doxygen" VERBATIM
                    )

  message( STATUS "Doxygen output is to to " ${DOXYGEN_OUTPUT} )

  file( MAKE_DIRECTORY "${DOXYGEN_OUTPUT}" )

endif(DOXYGEN_FOUND)

# These are platform specific build instructions, this needs to be cleaned up

