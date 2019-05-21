cmake_minimum_required( VERSION 3.5 )

project( FSCIO )

enable_testing()

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
   message(WARNING "CMAKE_INSTALL_PREFIX is set to default path of ${CMAKE_INSTALL_PREFIX}, resetting to ${CMAKE_INSTALL_PREFIX}/fscio")
   set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/fscio")
elseif ("${CMAKE_INSTALL_PREFIX}" STREQUAL "/usr/local")
   message(WARNING "CMAKE_INSTALL_PREFIX is explicitly set to /usr/local. This is not recommended.")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries/fc/CMakeModules")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")

if (UNIX)
   if (APPLE)
      if (LLVM_DIR STREQUAL "" OR NOT LLVM_DIR)
         set(LLVM_DIR "/usr/local/opt/llvm@4/lib/cmake/llvm/")
      endif()
   endif()
endif()

include( GNUInstallDirs )
include( VersionMacros )
include( SetupTargetMacros )
include( InstallDirectoryPermissions )
include( MASSigning )

set( BLOCKCHAIN_NAME "FSCIO" )
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_EXTENSIONS ON )
set( CXX_STANDARD_REQUIRED ON)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 3)

if(VERSION_SUFFIX)
    set(VERSION_FULL "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}-${VERSION_SUFFIX}")
else()
    set(VERSION_FULL "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
endif()

set( CLI_CLIENT_EXECUTABLE_NAME clfsc )
set( NODE_EXECUTABLE_NAME nodfsc )
set( KEY_STORE_EXECUTABLE_NAME kfscd )
set( GUI_CLIENT_EXECUTABLE_NAME fscio )
set( CUSTOM_URL_SCHEME "gcs" )
set( INSTALLER_APP_ID "68ad7005-8eee-49c9-95ce-9eed97e5b347" )

# http://stackoverflow.com/a/18369825
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6.0)
        message(FATAL_ERROR "GCC version must be at least 6.0!")
    endif()
    if ("${CMAKE_GENERATOR}" STREQUAL "Ninja")
       add_compile_options(-fdiagnostics-color=always)
    endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.0)
        message(FATAL_ERROR "Clang version must be at least 4.0!")
    endif()
    if ("${CMAKE_GENERATOR}" STREQUAL "Ninja")
       add_compile_options(-fcolor-diagnostics)
    endif()
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
set(BUILD_DOXYGEN FALSE CACHE BOOL "Build doxygen documentation on every make")
set(BUILD_MONGO_DB_PLUGIN FALSE CACHE BOOL "Build mongo database plugin")
set(BUILD_KAFKA_PLUGIN FALSE CACHE BOOL "Build kafka plugin")

#set (USE_PCH 1)

if (USE_PCH)
  include (cotire)
endif(USE_PCH)

# add defaults for openssl
if ("${OPENSSL_ROOT_DIR}" STREQUAL "")
   if (NOT "$ENV{OPENSSL_ROOT_DIR}" STREQUAL "")
      set(OPENSSL_ROOT_DIR $ENV{OPENSSL_ROOT_DIR})
      set(OPENSSL_INCLUDE_DIR ${OPENSSL_ROOT_DIR}/include)
   elseif (APPLE)
      set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
      set(OPENSSL_INCLUDE_DIR "/usr/local/opt/openssl/include")
   elseif(UNIX AND NOT APPLE)
      set(OPENSSL_ROOT_DIR "/usr/include/openssl")
      set(OPENSSL_INCLUDE_DIR "/usr/include/openssl/include")
   else()
      message(FATAL_ERROR "openssl not found and don't know where to look, please specify OPENSSL_ROOT_DIR")
   endif()
endif()

if(UNIX)
  if(APPLE)
    set(whole_archive_flag "-force_load")
    set(no_whole_archive_flag "")
  else()
    set(whole_archive_flag "--whole-archive")
    set(no_whole_archive_flag "--no-whole-archive")
  endif()
else()
  set(whole_archive_flag "--whole-archive")
  set(no_whole_archive_flag "--no-whole-archive")
endif()

SET( Boost_USE_STATIC_LIBS ON CACHE STRING "ON or OFF" )
IF( WIN32 )
  SET(BOOST_ROOT $ENV{BOOST_ROOT})
  set(Boost_USE_MULTITHREADED ON)
  set(BOOST_ALL_DYN_LINK OFF) # force dynamic linking for all libraries
ENDIF(WIN32)
FIND_PACKAGE(Boost 1.67 REQUIRED COMPONENTS
    thread
    date_time
    filesystem
    system
    program_options
    signals
    serialization
    chrono
    unit_test_framework
    context
    locale
    iostreams)

# Some new stdlibc++s will #error on <experimental/string_view>; a problem for boost pre-1.69
if( APPLE AND UNIX )
   add_definitions(-DBOOST_ASIO_DISABLE_STD_EXPERIMENTAL_STRING_VIEW)
endif()

if( WIN32 )

    message( STATUS "Configuring FSCIO on WIN32")
    set( DB_VERSION 60 )
    set( BDB_STATIC_LIBS 1 )

    set( ZLIB_LIBRARIES "" )
    SET( DEFAULT_EXECUTABLE_INSTALL_DIR bin/ )

    set(CRYPTO_LIB)

    #looks like this flag can have different default on some machines.
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /SAFESEH:NO")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SAFESEH:NO")

    # Probably cmake has a bug and vcxproj generated for executable in Debug conf. has disabled debug info
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG")

    # On windows tcl should be installed to the directory pointed by setenv.bat script
    SET(TCL_INCLUDE_PATH $ENV{TCL_ROOT}/include)
    MESSAGE(STATUS "tcl INCLUDE PATH: ${TCL_INCLUDE_PATH}")

    FIND_PACKAGE(TCL)
    MESSAGE(STATUS "tcl_library: ${TCL_LIBRARY}")

    SET(TCL_LIBS "optimized;${TCL_LIBRARY};debug;")
    get_filename_component(TCL_LIB_PATH "${TCL_LIBRARY}" PATH)
    get_filename_component(TCL_LIB_NAME "${TCL_LIBRARY}" NAME_WE)
    get_filename_component(TCL_LIB_EXT "${TCL_LIBRARY}" EXT)

    SET(TCL_LIBS "${TCL_LIBS}${TCL_LIB_PATH}/${TCL_LIB_NAME}g${TCL_LIB_EXT}")
    SET(TCL_LIBRARY ${TCL_LIBS})

else( WIN32 ) # Apple AND Linux

    if( APPLE )
        # Apple Specific Options Here
        message( STATUS "Configuring FSCIO on OS X" )
        set( CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-deprecated-declarations" )
    else( APPLE )
        # Linux Specific Options Here
        message( STATUS "Configuring FSCIO on Linux" )
        set( CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall" )
        if ( FULL_STATIC_BUILD )
          set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++ -static-libgcc")
        endif ( FULL_STATIC_BUILD )

        if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
            if( CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 4.0.0 OR CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.0.0 )
                set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-partial-specialization" )
            endif()
        endif()
    endif( APPLE )

    if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-builtin-memcmp" )
    endif()

    if( "${CMAKE_GENERATOR}" STREQUAL "Ninja" )
        if( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
            set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics" )
        endif()
    endif()

    # based on http://www.delorie.com/gnu/docs/gdb/gdb_70.html
    # uncomment this line to tell GDB about macros (slows compile times)
    # set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gdwarf-2 -g3" )

endif( WIN32 )

set(ENABLE_COVERAGE_TESTING FALSE CACHE BOOL "Build FSCIO for code coverage analysis")

if(ENABLE_COVERAGE_TESTING)
  SET(CMAKE_CXX_FLAGS "--coverage ${CMAKE_CXX_FLAGS}")
  find_program( LCOV_PATH  lcov )
  find_program( LLVMCOV_PATH  llvm-cov )
  find_program( GENHTML_PATH NAMES genhtml)
endif()

include(utils)
add_subdirectory( externals )

if ("${CORE_SYMBOL_NAME}" STREQUAL "")
  set( CORE_SYMBOL_NAME "FSC" )
endif()
string(TOUPPER ${CORE_SYMBOL_NAME} CORE_SYMBOL_NAME)

string(LENGTH ${CORE_SYMBOL_NAME} CORE_SYMBOL_NAME_LENGTH)
if (CORE_SYMBOL_NAME_LENGTH GREATER 7)
  message(FATAL_ERROR "CORE_SYMBOL_NAME length must be between 1 and 7 characters")
endif()

message( STATUS "Using '${CORE_SYMBOL_NAME}' as CORE symbol name" )

if ("${CORE_SYMBOL_PRECISION}" STREQUAL "")
  set( CORE_SYMBOL_PRECISION 8 )
endif()

message( STATUS "Using '${CORE_SYMBOL_PRECISION}' as CORE symbol precision" )

if ("${FSCIO_ROOT_KEY}" STREQUAL "")
   set(FSCIO_ROOT_KEY "FSC6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV")
endif()

message( STATUS "Using '${FSCIO_ROOT_KEY}' as public key for 'fscio' account" )

include(wasm)
add_subdirectory( libraries )
add_subdirectory( contracts )
add_subdirectory( plugins )
add_subdirectory( programs )
add_subdirectory( scripts )
add_subdirectory( unittests )
add_subdirectory( tests )
add_subdirectory( tools )
add_subdirectory( debian )

install_directory_permissions(DIRECTORY ${CMAKE_INSTALL_FULL_SYSCONFDIR}/fscio)

install(FILES testnet.template DESTINATION ${CMAKE_INSTALL_FULL_SYSCONFDIR}/fscio/launcher)
install_directory_permissions(DIRECTORY ${CMAKE_INSTALL_FULL_SYSCONFDIR}/fscio)
install_directory_permissions(DIRECTORY ${CMAKE_INSTALL_FULL_SYSCONFDIR}/fscio/launcher)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/testnet.template ${CMAKE_CURRENT_BINARY_DIR}/etc/fscio/launcher/testnet.template COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fscio.version.in ${CMAKE_CURRENT_BINARY_DIR}/fscio.version.hpp)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/fscio.version.hpp DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR})

set(FSC_ROOT_DIR ${CMAKE_BINARY_DIR})
configure_file(${CMAKE_SOURCE_DIR}/CMakeModules/fscio-config.cmake.in ${CMAKE_BINARY_DIR}/lib/cmake/fscio/fscio-config.cmake @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/CMakeModules/FscioTesterBuild.cmake.in ${CMAKE_BINARY_DIR}/lib/cmake/fscio/FscioTester.cmake @ONLY)

set(FSC_ROOT_DIR ${CMAKE_INSTALL_PREFIX})
configure_file(${CMAKE_SOURCE_DIR}/CMakeModules/fscio-config.cmake.in ${CMAKE_BINARY_DIR}/modules/fscio-config.cmake @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/modules/fscio-config.cmake DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake/fscio)
configure_file(${CMAKE_SOURCE_DIR}/CMakeModules/FscioTester.cmake.in ${CMAKE_BINARY_DIR}/modules/FscioTester.cmake @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/modules/FscioTester.cmake DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake/fscio)

configure_file(${CMAKE_SOURCE_DIR}/LICENSE 
               ${CMAKE_BINARY_DIR}/licenses/fscio/LICENSE COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/libraries/wabt/LICENSE 
               ${CMAKE_BINARY_DIR}/licenses/fscio/LICENSE.wabt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/libraries/softfloat/COPYING.txt 
               ${CMAKE_BINARY_DIR}/licenses/fscio/LICENSE.softfloat COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/libraries/wasm-jit/LICENSE 
               ${CMAKE_BINARY_DIR}/licenses/fscio/LICENSE.wavm COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/libraries/fc/secp256k1/upstream/COPYING 
               ${CMAKE_BINARY_DIR}/licenses/fscio/LICENSE.secp256k1 COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/libraries/fc/src/network/LICENSE.go 
               ${CMAKE_BINARY_DIR}/licenses/fscio/LICENSE.go COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/externals/binaryen/LICENSE 
               ${CMAKE_BINARY_DIR}/licenses/fscio/LICENSE.binaryen COPYONLY)

install(FILES LICENSE DESTINATION ${CMAKE_INSTALL_FULL_DATAROOTDIR}/licenses/fscio/)
install(FILES libraries/wabt/LICENSE DESTINATION ${CMAKE_INSTALL_FULL_DATAROOTDIR}/licenses/fscio/ RENAME LICENSE.wabt)
install(FILES libraries/softfloat/COPYING.txt DESTINATION ${CMAKE_INSTALL_FULL_DATAROOTDIR}/licenses/fscio/ RENAME LICENSE.softfloat)
install(FILES libraries/wasm-jit/LICENSE DESTINATION ${CMAKE_INSTALL_FULL_DATAROOTDIR}/licenses/fscio/ RENAME LICENSE.wavm)
install(FILES libraries/fc/secp256k1/upstream/COPYING DESTINATION ${CMAKE_INSTALL_FULL_DATAROOTDIR}/licenses/fscio/ RENAME LICENSE.secp256k1)
install(FILES externals/binaryen/LICENSE DESTINATION ${CMAKE_INSTALL_FULL_DATAROOTDIR}/licenses/fscio/ RENAME LICENSE.binaryen)
install(FILES libraries/fc/src/network/LICENSE.go DESTINATION ${CMAKE_INSTALL_FULL_DATAROOTDIR}/licenses/fscio/ )

include(package)
include(doxygen)
