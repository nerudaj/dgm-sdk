cmake_minimum_required ( VERSION 3.19 )

file (
	COPY "${CMAKE_BINARY_DIR}/.clang-format"
	DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}"
)

project ( "${SETTINGS_BINARY_NAME}" )
copy_dlls_to_build_folders()

# Copy tgui libs as well
configure_file (
	${TGUI_FOLDER}/bin/tgui-d.dll
	${CMAKE_CURRENT_BINARY_DIR}/Debug/ COPYONLY
)

configure_file (
	${TGUI_FOLDER}/bin/tgui.dll
	${CMAKE_CURRENT_BINARY_DIR}/Release/ COPYONLY
)

# Create final executable
add_executable ( ${PROJECT_NAME} WIN32
	Main.cpp
	"${CMAKE_CURRENT_SOURCE_DIR}/.clang-format"
)

target_link_libraries ( ${PROJECT_NAME}
	game-lib ${LIB_CFG} ${LIB_LVLD}
)

set_target_properties ( ${PROJECT_NAME} PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# Packaging
install (
	FILES       "${CMAKE_CURRENT_BINARY_DIR}/Release/${SETTINGS_BINARY_NAME}.exe"
	DESTINATION "bin"
)

file ( GLOB DLLS "${CMAKE_CURRENT_BINARY_DIR}/Release/*.dll" )

install (
	FILES       ${DLLS}
	DESTINATION "bin"
)
