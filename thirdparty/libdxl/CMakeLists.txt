
set( LIBDXL_SRCS
  dxl_hal.c
  dynamixel.c
)

add_library( dxl SHARED ${LIBDXL_SRCS} )

install( TARGETS dxl
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib )
