cmake_minimum_required ( VERSION 3.19 )


project ( lib-events )

get_latest_clang_format()
glob_sources_and_headers( HEADERS SOURCES )

add_library (
	${PROJECT_NAME} INTERFACE
	${HEADERS}
	"${CMAKE_CURRENT_SOURCE_DIR}/.clang-format"
)

target_include_directories ( ${PROJECT_NAME}
	INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

autoset_target_compile_options ( ${PROJECT_NAME} TRUE )
