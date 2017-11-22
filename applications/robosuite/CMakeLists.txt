
include( sources )

add_executable( robosuite ${SRCS} )

install( TARGETS robosuite
         RUNTIME DESTINATION bin )
target_link_libraries( robosuite
  osg
  osgGA
  osgViewer )
