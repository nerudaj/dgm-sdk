cmake_minimum_required ( VERSION 3.19 )

# Download some helper files
file (
	DOWNLOAD
		"https://raw.githubusercontent.com/nerudaj/clang-format/main/.clang-format"
		"${CMAKE_BINARY_DIR}/.clang-format"
)

include ( "${CMAKE_SOURCE_DIR}/cmake/cpp.cmake" )

include ( "${CMAKE_SOURCE_DIR}/cmake/settings.cmake" )
include ( "${CMAKE_SOURCE_DIR}/cmake/version.cmake" )
include ( "${CMAKE_SOURCE_DIR}/cmake/utils.cmake" )

project ( "${SETTINGS_PROJECT_NAME}" )

option ( DISABLE_TESTING    "Disable unit test projects" OFF )
option ( ENABLE_BENCHMARKS "Disable benchmarking projects" OFF )
option ( CACHE_THIRD_PARTY  "Downloaded dependencies will be stored outside of build dir" OFF )

if ( ${CACHE_THIRD_PARTY} )
	set ( FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps" )
endif()

include ( "${CMAKE_SOURCE_DIR}/cmake/dependencies.cmake" )

if ( NOT ${DISABLE_TESTING})
	enable_testing()
endif()

add_subdirectory ( lib )
add_subdirectory ( bin )

# Packaging
install (
	DIRECTORY   "resources"
	DESTINATION "."
)

set ( CPACK_GENERATOR "ZIP" )
set ( CPACK_PACKAGE_VERSION_MAJOR       "${PROJECT_VERSION_MAJOR}" )
set ( CPACK_PACKAGE_VERSION_MINOR       "${PROJECT_VERSION_MINOR}" )
set ( CPACK_PACKAGE_VERSION_PATCH       "${PROJECT_VERSION_PATCH}" )
set ( CPACK_PACKAGE_FILE_NAME           "${PROJECT_NAME}-${PROJECT_VERSION}-windows-vc16-${CMAKE_GENERATOR_PLATFORM}" )

include ( CPack )
