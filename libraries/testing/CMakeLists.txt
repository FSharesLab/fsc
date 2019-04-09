file(GLOB HEADERS "include/fscio/testing/*.hpp")

## SORT .cpp by most likely to change / break compile
add_library( fscio_testing
             tester.cpp
             tester_network.cpp
             ${HEADERS}
        )

target_link_libraries( fscio_testing fscio_chain fc chainbase Logging IR WAST WASM Runtime )
target_include_directories( fscio_testing
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include"
                                   "${CMAKE_CURRENT_SOURCE_DIR}/../wasm-jit/Include"
                                   "${CMAKE_BINARY_DIR}/contracts"
                            )

add_dependencies( fscio_testing fscio.bios )

if(MSVC)
  set_source_files_properties( db_init.cpp db_block.cpp database.cpp block_log.cpp PROPERTIES COMPILE_FLAGS "/bigobj" )
endif(MSVC)

set_target_properties( fscio_testing PROPERTIES PUBLIC_HEADER "${HEADERS}" )
install( TARGETS fscio_testing
   RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
   LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
   ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
   PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/fscio/testing
)
install_directory_permissions( DIRECTORY ${CMAKE_INSTALL_FULL_INCLUDEDIR}/fscio/testing )

