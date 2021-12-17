cmake_minimum_required ( VERSION 3.19 )

# Project setup
project ( dgm-sdk )
include ( "${CMAKE_SOURCE_DIR}/cmake/cpp.cmake" )
include ( "${CMAKE_SOURCE_DIR}/cmake/version.cmake" )
enable_testing()

# TODO: docs

# Packaging
set ( CPACK_GENERATOR "ZIP" )
set ( CPACK_PACKAGE_VERSION_MAJOR       "${PROJECT_VERSION_MAJOR}" )
set ( CPACK_PACKAGE_VERSION_MINOR       "${PROJECT_VERSION_MINOR}" )
set ( CPACK_PACKAGE_VERSION_PATCH       "${PROJECT_VERSION_PATCH}" )
set ( CPACK_PACKAGE_FILE_NAME           "${PROJECT_NAME}-${PROJECT_VERSION}-windows-vc16-${CMAKE_GENERATOR_PLATFORM}" )

install (
	DIRECTORY   "examples"
	DESTINATION "."
	REGEX "vsbuild" EXCLUDE
)

install (
	DIRECTORY   "project-template"
	DESTINATION "."
	REGEX "vsbuild" EXCLUDE
)

install (
	DIRECTORY   "tutorials"
	DESTINATION "."
)

install (
	DIRECTORY   "licenses"
	DESTINATION "."
)

install (
	FILES       "Readme-release.md"
	DESTINATION "."
	RENAME      "Readme.md"
)

install (
	FILES       "changelog.txt"
	DESTINATION "."
)

include ( CPack )