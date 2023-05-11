cmake_minimum_required ( VERSION 3.19 )

get_latest_clang_format()

project ( lib-events )

file ( GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include**/*.hpp" )
source_group ( TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADERS})

add_library (
	${PROJECT_NAME} INTERFACE
	${HEADERS}
	"${CMAKE_CURRENT_SOURCE_DIR}/.clang-format"
)

target_include_directories ( ${PROJECT_NAME}
	INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_compile_features( ${PROJECT_NAME}
	INTERFACE ${MY_CXX_COMPILE_FEATURES}
)
