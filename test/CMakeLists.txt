
include( sources.test )
include_directories( 
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/src/servos 
  ${DYNAMIXELSDK_INCLUDE_DIR} )

add_executable( test_dynamixel ${TEST_DYNAMIXEL_SRCS} )
target_link_libraries( test_dynamixel ikengine )

install( TARGETS test_dynamixel
         RUNTIME DESTINATION test/bin
         LIBRARY DESTINATION test/lib
         ARCHIVE DESTINATION test/lib )

