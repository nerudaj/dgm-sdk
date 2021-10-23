cmake_minimum_required ( VERSION 3.19 )

include ( "${CMAKE_SOURCE_DIR}/cmake/settings.cmake" )
include ( "${CMAKE_SOURCE_DIR}/cmake/version.cmake" )
include ( "${CMAKE_SOURCE_DIR}/cmake/dependencies.cmake" )
include ( "${CMAKE_SOURCE_DIR}/cmake/utils.cmake" )
include ( "${CMAKE_SOURCE_DIR}/cmake/cpp.cmake" )

project ( "${SETTINGS_PROJECT_NAME}" )
enable_testing()

add_subdirectory ( lib )
add_subdirectory ( bin )

# TODO: packaging
