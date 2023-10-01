cmake_minimum_required ( VERSION 3.26 )

project ( lib-game )

get_latest_clang_format()
glob_sources_and_headers ( HEADERS SOURCES )

add_library ( ${PROJECT_NAME} STATIC
	${SOURCES} ${HEADERS}
	"${CMAKE_CURRENT_SOURCE_DIR}/.clang-format"
)

target_include_directories ( ${PROJECT_NAME}
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
	PUBLIC "${DGM_FOLDER}/include"
	PUBLIC "${DGM_FSM_FOLDER}/include"
	PUBLIC "${SFML_FOLDER}/include"
	PUBLIC "${ENTT_FOLDER}/single_include"
	PUBLIC "${DSH_FOLDER}/include"
)

target_link_libraries ( ${PROJECT_NAME}
	lib-memory lib-settings Dep_sfml Dep_dgm Dep_dgm_fsm
)

autoset_target_compile_options ( ${PROJECT_NAME} FALSE )
