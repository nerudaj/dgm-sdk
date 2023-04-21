cmake_minimum_required ( VERSION 3.19 )

file (
	COPY "${CMAKE_BINARY_DIR}/.clang-format"
	DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}"
)

project ( lib-tests )

set ( SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp"
	
	"${CMAKE_CURRENT_SOURCE_DIR}/src/Example.cpp"
)

add_executable ( ${PROJECT_NAME}
	${SOURCES}
	"${CMAKE_CURRENT_SOURCE_DIR}/.clang-format"
) 

target_include_directories ( ${PROJECT_NAME}
	PRIVATE "${CATCH_FOLDER}"
)

target_link_libraries( ${PROJECT_NAME}
	game-lib
)
