
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
option( BUILD_DOC "Build documentation" ON )
option( BUILD_APPLICATION "Build applications" ON )

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_FLAGS "-Werror=all" )

find_package( Eigen3 )
if( NOT EIGEN3_FOUND )
  message( FATAL_ERROR "Eigen3 is required to build libikengine" )
endif()

if( BUILD_DOC )
  find_package( Doxygen )
  if( NOT DOXYGEN_FOUND )
    message( FATAL_ERROR "Doxygen is required to build the docs" )
  endif()
  if( NOT DOXYGEN_DOT_FOUND )
    message( FATAL_ERROR "graphviz is required to build the docs" )
  endif()
endif()

if( BUILD_APPLICATION )
  find_package( OpenSceneGraph )
  if( NOT OPENSCENEGRAPH_FOUND )
    message( FATAL_ERROR "OpenSceneGraph is required to build the applications" )
  endif()
endif()

# libdxl
if( ENABLE_DYNAMIXEL )
  # Build the dynamixel SDK as part of this project
  # EXCLUDE_FROM_ALL ensures the install rules from this file won't be run
  add_subdirectory( ${PROJECT_SOURCE_DIR}/thirdparty/DynamixelSDK/c++ ${CMAKE_BINARY_DIR}/thirdparty/DynamixelSDK EXCLUDE_FROM_ALL )
  set( DYNAMIXELSDK_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/thirdparty/DynamixelSDK/c++/include/dynamixel_sdk )
  install( FILES "${CMAKE_BINARY_DIR}/devel/lib/${CMAKE_SHARED_LIBRARY_PREFIX}dynamixel_sdk${CMAKE_SHARED_LIBRARY_SUFFIX}"
           DESTINATION lib )
endif()

add_subdirectory( ${PROJECT_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/ikengine )

if( BUILD_TEST )
  add_subdirectory( ${PROJECT_SOURCE_DIR}/test ${CMAKE_BINARY_DIR}/test )
endif()
if( BUILD_DOC )
  add_subdirectory( ${PROJECT_SOURCE_DIR}/doc ${CMAKE_BINARY_DIR}/doc )
endif()
if( BUILD_APPLICATION )
  add_subdirectory( ${PROJECT_SOURCE_DIR}/applications ${CMAKE_BINARY_DIR}/applications )
endif()
