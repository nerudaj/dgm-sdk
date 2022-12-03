cmake_minimum_required ( VERSION 3.19 )

project ( example-simple-ai )
copy_dlls_to_build_folders()

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

add_executable ( ${PROJECT_NAME} WIN32
	 ${HEADER_FILES} ${SOURCE_FILES}
)

target_link_libraries ( ${PROJECT_NAME}
	examples-shared-code
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
