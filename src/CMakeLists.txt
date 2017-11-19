
# libikengine
include( sources.libikengine )
if( USE_LIBDXL )
  list( APPEND LIBIKENGINE_SRCS ${LIBIKENGINE_LIBDXL_SRCS} )
  list( APPEND LIBIKENGINE_LINK dxl )
endif()
include_directories( 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/thirdparty
  ${EIGEN3_INCLUDE_DIR} )
add_library( ikengine SHARED ${LIBIKENGINE_SRCS} )
target_link_libraries( ikengine ${LIBIKENGINE_LINK} )

install( TARGETS ikengine
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib )
install( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
         DESTINATION include 
         FILES_MATCHING PATTERN *.h 
         PATTERN util EXCLUDE )

