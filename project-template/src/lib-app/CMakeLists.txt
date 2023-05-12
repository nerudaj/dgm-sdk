cmake_minimum_required ( VERSION 3.19 )

project ( lib-app )

configure_file (
	"${CMAKE_CURRENT_SOURCE_DIR}/include/settings/GameTitle.hpp.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/settings/GameTitle.hpp"
)

get_latest_clang_format()
glob_sources_and_headers( HEADERS SOURCES )

add_library ( ${PROJECT_NAME} STATIC
	${HEADERS} ${SOURCES}
	"${CMAKE_CURRENT_SOURCE_DIR}/.clang-format"
)

target_include_directories ( ${PROJECT_NAME}
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
	PUBLIC "${DGM_FOLDER}/include"
	PUBLIC "${DGM_FSM_FOLDER}/include"
	PUBLIC "${SFML_FOLDER}/include"
	PUBLIC "${TGUI_FOLDER}/include"
	PUBLIC "${DSH_FOLDER}/include"
)

target_link_libraries ( ${PROJECT_NAME}
	lib-events lib-engines lib-settings lib-game ${LIB_DGM} ${LIB_SFML} ${LIB_TGUI} ${LIB_DGM_FSM}
)

autoset_target_compile_options ( ${PROJECT_NAME} FALSE )
