cmake_minimum_required ( VERSION 3.19 )

# C++ standards
include ( "${CMAKE_SOURCE_DIR}/cmake/cpp.cmake" )

set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Compiled" )

# Project
project ( "dgm-lib-examples" )
include ( "${CMAKE_SOURCE_DIR}/cmake/dependencies.cmake" )
include ( "${CMAKE_SOURCE_DIR}/cmake/utils.cmake" )

configure_file (
	"${CMAKE_SOURCE_DIR}/ResourceDir.hpp.in"
	"${CMAKE_SOURCE_DIR}/ResourceDir.hpp"
)

# Subprojects
add_subdirectory ( "shared" )
add_subdirectory ( "example-app" )
add_subdirectory ( "example-controller" )
add_subdirectory ( "example-particle-effects" )
add_subdirectory ( "example-simple-ai" )
add_subdirectory ( "example-tileset" )
add_subdirectory ( "example-pathfind" )
add_subdirectory ( "example-spatial-buffer" )
add_subdirectory ( "example-math" )