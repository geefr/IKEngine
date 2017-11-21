
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
option( ENABLE_DYNAMIXEL "Include support for Dynamixel servos" ON )
option( BUILD_TEST "Build test executables" ON )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_FLAGS "-Werror=all" )

find_package( Eigen3 )
if( NOT EIGEN3_FOUND )
  message( FATAL_ERROR "Eigen3 is required to build libikengine" )
endif()

# libdxl
if( ENABLE_DYNAMIXEL )
  # Build the dynamixel SDK as part of this project
  # EXCLUDE_FROM_ALL ensures the install rules from this file won't be run
  add_subdirectory( ${PROJECT_SOURCE_DIR}/thirdparty/DynamixelSDK/c++ ${CMAKE_BINARY_DIR}/thirdparty/DynamixelSDK EXCLUDE_FROM_ALL )
  set( DYNAMIXELSDK_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/thirdparty/DynamixelSDK/c++/include/dynamixel_sdk )
endif()

add_subdirectory( ${PROJECT_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/ikengine )

if( BUILD_TEST )
  add_subdirectory( ${PROJECT_SOURCE_DIR}/test ${CMAKE_BINARY_DIR}/test )
endif()
