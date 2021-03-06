cmake_minimum_required ( VERSION 3.19 )

project ( game-lib )

configure_file (
	"${CMAKE_CURRENT_SOURCE_DIR}/core/Settings.hpp.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/core/Settings.hpp"
)

file (
	GLOB APP_HEADERS
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/app/*.hpp"
)

file (
	GLOB APP_SOURCES
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/app/*.cpp"
)

file (
	GLOB CORE_HEADERS
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/core/*.hpp"
)

file (
	GLOB CORE_SOURCES
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/core/*.cpp"
)

file (
	GLOB EVENTS_HEADERS
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/events/*.hpp"
)

file (
	GLOB EVENTS_SOURCES
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/events/*.cpp"
)

file (
	GLOB GAME_HEADERS
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/game/*.hpp"
)

file (
	GLOB GAME_SOURCES
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/game/*.cpp"
)

source_group (
	TREE
	${CMAKE_CURRENT_SOURCE_DIR}
	FILES
		${APP_HEADERS} ${APP_SOURCES}
		${CORE_HEADERS} ${CORE_SOURCES}
		${EVENTS_HEADERS} ${EVENTS_SOURCES}
		${GAME_HEADERS} ${GAME_SOURCES}
)

add_library ( ${PROJECT_NAME} STATIC
	${APP_HEADERS} ${APP_SOURCES}
	${CORE_HEADERS} ${CORE_SOURCES}
	${EVENTS_HEADERS} ${EVENTS_SOURCES}
	${GAME_HEADERS} ${GAME_SOURCES}
	"${CMAKE_CURRENT_SOURCE_DIR}/.editorconfig"
)

target_include_directories ( ${PROJECT_NAME}
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
	PUBLIC "${DGM_FOLDER}/include/include"
	PUBLIC "${DGM_FOLDER}/include"
	PUBLIC "${SFML_FOLDER}/include"
	PUBLIC "${TGUI_FOLDER}/include"
)

target_link_libraries ( ${PROJECT_NAME}
	${LIB_DGM} ${LIB_SFML} ${LIB_TGUI}
)

target_compile_features( ${PROJECT_NAME}
	INTERFACE ${MY_CXX_COMPILE_FEATURES}
)

target_compile_options ( ${PROJECT_NAME}
	PRIVATE /MP
)

if ( NOT ${DISABLE_BENCHMARKS} )
	add_subdirectory ( benchmarks )
endif()

if ( NOT ${DISABLE_TESTING} )
	add_subdirectory ( tests )
endif()
