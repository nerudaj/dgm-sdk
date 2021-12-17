cmake_minimum_required ( VERSION 3.19 )

project ( game-lib )

set ( APP_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/app/AppStateBootstrap.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/app/AppStateIngame.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/app/AppStateMainMenu.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/app/AppStateMenuOptions.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/app/AppStatePaused.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/app/GuiBuilder.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/app/GuiState.hpp"
)

set ( APP_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/app/AppStateBootstrap.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/app/AppStateIngame.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/app/AppStateMainMenu.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/app/AppStateMenuOptions.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/app/AppStatePaused.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/app/GuiBuilder.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/app/GuiState.cpp"
)

set ( CORE_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/core/AudioPlayer.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/core/Settings.hpp"
)

set ( CORE_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/core/AudioPlayer.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/core/Settings.cpp"
)

set ( EVENTS_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/events/Events.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/events/EventQueue.hpp"
)

set ( EVENTS_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/events/Events.cpp"
)

set ( GAME_HEADERS
	"${CMAKE_CURRENT_SOURCE_DIR}/game/EntityTable.hpp"
)

source_group ( "App States" FILES ${APP_HEADERS} ${APP_SOURCES} )
source_group ( "Core" FILES ${CORE_HEADERS} ${CORE_SOURCES} )
source_group ( "Events" FILES ${EVENTS_HEADERS} ${EVENTS_SOURCES} )
source_group ( "Game" FILES ${GAME_HEADERS} )

add_library ( ${PROJECT_NAME} STATIC
	${APP_HEADERS} ${APP_SOURCES}
	${CORE_HEADERS} ${CORE_SOURCES}
	${EVENTS_HEADERS} ${EVENTS_SOURCES}
	${GAME_HEADERS}
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

add_subdirectory ( benchmarks )
add_subdirectory ( tests )
