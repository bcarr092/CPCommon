cmake_minimum_required( VERSION 3.0 )

set( PROJECT_NAME "prjCPCommon" )

include( "~/Developer/CMake/CrossPlatformHelper.cmake" )

# Project name will be prjCPCommon
project( ${PROJECT_NAME} )

cross_platform_initialize()

add_library( ${PROJECT_NAME} STATIC ${SOURCES} ${INCLUDES} )

install( TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION lib )

install( FILES ${INCLUDES} DESTINATION "include/${PROJECT_NAME}" )
