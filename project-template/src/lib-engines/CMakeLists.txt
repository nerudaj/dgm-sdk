cmake_minimum_required ( VERSION 3.19 )

project ( lib-engines )

get_latest_clang_format()
glob_sources_and_headers( HEADERS SOURCES )

add_library ( ${PROJECT_NAME} STATIC
	${SOURCES} ${HEADERS}
	"${CMAKE_CURRENT_SOURCE_DIR}/.clang-format"
)

target_link_libraries ( ${PROJECT_NAME}
	lib-events lib-game ${LIB_DGM} ${LIB_SFML} ${LIB_TGUI}
)

target_include_directories ( ${PROJECT_NAME}
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
	PUBLIC "${DGM_FOLDER}/include"
	PUBLIC "${SFML_FOLDER}/include"
	PUBLIC "${TGUI_FOLDER}/include"
)

autoset_target_compile_options ( ${PROJECT_NAME} FALSE )