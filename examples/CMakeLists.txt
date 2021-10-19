cmake_minimum_required ( VERSION 3.19 )

# C++ standards
include ( "${CMAKE_SOURCE_DIR}/cmake/cpp.cmake" )

# Project
project ( "dgm-lib-examples" )
include ( "${CMAKE_SOURCE_DIR}/cmake/dependencies.cmake" )
include ( "${CMAKE_SOURCE_DIR}/cmake/utils.cmake" )

# Subprojects
add_subdirectory ( "example-tileset" )
