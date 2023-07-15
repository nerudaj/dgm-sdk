cmake_minimum_required ( VERSION 3.22 )

project ( examples-shared-code )

file (
	GLOB HEADER_FILES
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

file (
	GLOB SOURCE_FILES
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library ( ${PROJECT_NAME} STATIC
    ${HEADER_FILES} ${SOURCE_FILES}
)

target_link_libraries ( ${PROJECT_NAME}
    ${LIB_SFML_MAIN} ${LIB_SFML_SYSTEM} ${LIB_SFML_GRAPHICS} ${LIB_SFML_WINDOW} ${LIB_SFML_AUDIO} ${LIB_DGM} ${LIB_LVLD} ${LIB_DGM_FSM} xinput.lib
)

target_include_directories ( ${PROJECT_NAME}
	PRIVATE  "${SFML_FOLDER}/include"
	PRIVATE  "${DGM_FOLDER}/include"
	PRIVATE  "${DGM_FOLDER}/include/include"
	PRIVATE  "${DGM_FSM_FOLDER}/include"
	PRIVATE  "${DSH_FOLDER}"
)

target_compile_features ( ${PROJECT_NAME}
	INTERFACE ${MY_CXX_COMPILE_FEATURES}
)

target_compile_options ( ${PROJECT_NAME}
	PRIVATE /W4 /MP
)
