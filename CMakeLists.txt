
cmake_minimum_required(VERSION 3.2)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message( FATAL_ERROR "In-tree builds are not supported by this project")
endif()

set( IKENGINE_VERSION_MAJOR 0 )
set( IKENGINE_VERSION_MINOR 0 )
set( IKENGINE_VERSION_PATCH 1 )
set( IKENGINE_VERSION_STRING ${IKENGINE_VERSION_MAJOR}.${IKENGINE_VERSION_MINOR}.${IKENGINE_VERSION_PATCH} )
set( IKENGINE_VERSION_ABI 0 )

project( ikengine )

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE )
  set_property( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Release" "Debug" "MinSizeRel" "RelWithDebInfo" )
endif()

set( LIB_TYPE SHARED CACHE STRING "The type of library to build" )
set_property( CACHE LIB_TYPE PROPERTY STRINGS "SHARED" "STATIC" )
option( USE_LIBDXL "Include support for Dynamixel servos" ON )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_FLAGS "-Werror=all" )

find_package( Eigen3 )
if( NOT EIGEN3_FOUND )
  message( FATAL_ERROR "Eigen3 is required to build libikengine" )
endif()

# libdxl
if( USE_LIBDXL )
  add_subdirectory( ${PROJECT_SOURCE_DIR}/thirdparty/libdxl ${CMAKE_BINARY_DIR}/libdxl )
endif()

# libikengine
include( sources.libikengine )
if( USE_LIBDXL )
  list( APPEND LIBIKENGINE_SRCS ${LIBIKENGINE_LIBDXL_SRCS} )
  list( APPEND LIBIKENGINE_LINK dxl )
endif()
include_directories( 
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/thirdparty
  ${EIGEN3_INCLUDE_DIR} )
add_library( ikengine SHARED ${LIBIKENGINE_SRCS} )
target_link_libraries( ikengine ${LIBIKENGINE_LINK} )

install( TARGETS ikengine
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib )
install( DIRECTORY ${PROJECT_SOURCE_DIR}
         DESTINATION include 
         FILES_MATCHING PATTERN *.h 
         PATTERN thirdparty EXCLUDE
         PATTERN util EXCLUDE )

