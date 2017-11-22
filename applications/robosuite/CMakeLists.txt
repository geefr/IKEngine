
include( sources )

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/src 
  ${EIGEN3_INCLUDE_DIR}
)

add_executable( robosuite ${SRCS} )

install( TARGETS robosuite
         RUNTIME DESTINATION bin )
target_link_libraries( robosuite
  ikengine
  osg
  osgGA
  osgViewer )
