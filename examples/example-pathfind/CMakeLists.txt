cmake_minimum_required ( VERSION 3.19 )

project ( example-pathfind )
copy_dlls_to_build_folders()

add_executable ( ${PROJECT_NAME} WIN32
	Main.cpp
)

target_link_libraries ( ${PROJECT_NAME}
	examples-shared-code
)

target_include_directories ( ${PROJECT_NAME}
	PRIVATE  "${SFML_FOLDER}/include"
	PRIVATE  "${DGM_FOLDER}/include"
	PRIVATE  "${DGM_FOLDER}/include/include"
	PRIVATE  "${DSH_FOLDER}"
)

target_compile_features ( ${PROJECT_NAME}
	INTERFACE ${MY_CXX_COMPILE_FEATURES}
)

target_compile_options ( ${PROJECT_NAME}
	PRIVATE /W4 /MP
)
