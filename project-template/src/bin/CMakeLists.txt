cmake_minimum_required ( VERSION 3.19 )

project ( "${SETTINGS_BINARY_NAME}" )

get_latest_clang_format()
copy_dlls_to_build_folders( TRUE )
glob_sources ( SOURCES )

# Create final executable
add_executable ( ${PROJECT_NAME} WIN32
	${SOURCES}
	"${CMAKE_CURRENT_SOURCE_DIR}/.clang-format"
)

target_link_libraries ( ${PROJECT_NAME}
	lib-app ${LIB_CFG} ${LIB_LVLD}
)

target_include_directories ( ${PROJECT_NAME}
	PRIVATE "${JSON_FOLDER}/include"
	PRIVATE "${CXXOPTS_FOLDER}/include"
)

set_target_properties ( ${PROJECT_NAME} PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)

autoset_target_compile_options ( ${PROJECT_NAME} FALSE )

# Packaging
install (
	FILES       "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/${SETTINGS_BINARY_NAME}.exe"
	DESTINATION "bin"
)

file ( GLOB DLLS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/*.dll" )

install (
	FILES       ${DLLS}
	DESTINATION "bin"
)
