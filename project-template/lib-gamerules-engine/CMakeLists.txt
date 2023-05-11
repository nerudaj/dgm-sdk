cmake_minimum_required ( VERSION 3.19 )

get_latest_clang_format()

project ( lib-gamerules-engine )

file ( GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include**/*.hpp" )
file ( GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src**/*.cpp" )
source_group ( TREE "${CMAKE_CURRENT_SOURCE_DIR}/include" FILES ${HEADERS})
source_group ( TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" FILES ${SOURCES})

add_library ( ${PROJECT_NAME} STATIC
	${SOURCES} ${HEADERS}
	"${CMAKE_CURRENT_SOURCE_DIR}/.clang-format"
)

target_link_libraries ( ${PROJECT_NAME}
	lib-events ${LIB_DGM} ${LIB_SFML} ${LIB_TGUI}
)

target_include_directories ( ${PROJECT_NAME}
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
	PUBLIC "${DGM_FOLDER}/include"
	PUBLIC "${SFML_FOLDER}/include"
	PUBLIC "${TGUI_FOLDER}/include"
)

autoset_target_compile_options ( ${PROJECT_NAME} FALSE )