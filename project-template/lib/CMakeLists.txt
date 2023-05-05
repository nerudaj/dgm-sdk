cmake_minimum_required ( VERSION 3.19 )

file (
	COPY "${CMAKE_BINARY_DIR}/.clang-format"
	DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}"
)

project ( game-lib )

set ( SOURCE_CODE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/src" )

configure_file (
	"${SOURCE_CODE_ROOT}/core/GameTitle.hpp.in"
	"${SOURCE_CODE_ROOT}/core/GameTitle.hpp"
)

file ( GLOB_RECURSE HDRS_SRCS "${SOURCE_CODE_ROOT}**/*.[ch]pp" )
source_group ( TREE "${SOURCE_CODE_ROOT}" FILES ${HDRS_SRCS})

add_library ( ${PROJECT_NAME} STATIC
	${HDRS_SRCS}
	"${CMAKE_CURRENT_SOURCE_DIR}/.clang-format"
)

target_include_directories ( ${PROJECT_NAME}
	PUBLIC "${SOURCE_CODE_ROOT}"
	PUBLIC "${DGM_FOLDER}/include"
	PUBLIC "${DGM_FSM_FOLDER}/include"
	PUBLIC "${SFML_FOLDER}/include"
	PUBLIC "${TGUI_FOLDER}/include"
	PUBLIC "${DSH_FOLDER}/include"
)

target_link_libraries ( ${PROJECT_NAME}
	${LIB_DGM} ${LIB_SFML} ${LIB_TGUI} ${LIB_DGM_FSM}
)

target_compile_features( ${PROJECT_NAME}
	INTERFACE ${MY_CXX_COMPILE_FEATURES}
)

target_compile_options ( ${PROJECT_NAME}
	PRIVATE /MP
)

target_precompile_headers ( ${PROJECT_NAME}
	PRIVATE
		<vector>
		<format>
		<map>
		<unordered_map>
		<array>
		<optional>
		<expected>
		<fstream>
		<filesystem>
		<functional>
		<concepts>
		<memory>
		<string>
		<cstdint>
		<variant>
		<DGM/dgm.hpp>
		<TGUI/tgui.hpp>
)

if ( ${ENABLE_BENCHMARKS} )
	add_subdirectory ( benchmarks )
endif()

if ( NOT ${DISABLE_TESTING} )
	add_subdirectory ( tests )
endif()
