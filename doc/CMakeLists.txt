    
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
set(DOXYOUT ${CMAKE_CURRENT_BINARY_DIR}/output)

# Settings in Doxyfile.in
set( DOXY_PROJECT_NAME ${CMAKE_PROJECT_NAME} )
set( DOXY_PROJECT_VERSION ${IKENGINE_VERSION_STRING} )
set( DOXY_PROJECT_SYNOPSIS "Inverse Kinematics and robotics library" )
set( DOXY_OUTPUT_DIR ${DOXYOUT} )
set( DOXY_INPUT ${PROJECT_SOURCE_DIR}/src )

configure_file(${DOXYFILE_IN} ${DOXYFILE} @ONLY)

add_custom_target( ikengine_doc ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM )

install( DIRECTORY ${DOXYOUT}/html/
         DESTINATION doc/IKengine )
