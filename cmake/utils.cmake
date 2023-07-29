function (copy_dlls_to_build_folders)
	message ( "Copying DLLs to build folders" )
	message ( "${SFML_FOLDER}" )

	file (GLOB DEBUG_SFML_DLLS   ${SFML_FOLDER}/bin/*-d-2.dll)
	file (GLOB RELEASE_SFML_DLLS ${SFML_FOLDER}/bin/*[oskmw]-2.dll)
	set ( OPENAL_DLL 			 ${SFML_FOLDER}/bin/openal32.dll )

	file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Debug" "${CMAKE_CURRENT_BINARY_DIR}/Release" )

	configure_file (
		${OPENAL_DLL} ${CMAKE_CURRENT_BINARY_DIR}/Debug/ COPYONLY
	)

	configure_file (
		${OPENAL_DLL} ${CMAKE_CURRENT_BINARY_DIR}/Release/ COPYONLY
	)

	foreach ( DLL ${DEBUG_SFML_DLLS} )
		configure_file ( ${DLL} ${CMAKE_CURRENT_BINARY_DIR}/Debug/ COPYONLY )
	endforeach ( DLL )

	foreach ( DLL ${RELEASE_SFML_DLLS} )
		configure_file ( ${DLL} ${CMAKE_CURRENT_BINARY_DIR}/Release/ COPYONLY )
	endforeach ( DLL )
endfunction (copy_dlls_to_build_folders)

# Looks into current source dir / include and recursively globs headers
# Looks into current source dir / src and recursively globs sources
# Then writes them into hdr_outvarname and src_outvarname
function ( glob_sources_and_headers src_outvarname hdr_outvarname )
    file ( GLOB_RECURSE LOCAL_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include**/*.hpp" )
	file ( GLOB_RECURSE LOCAL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src**/*.cpp" )
	source_group ( TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LOCAL_HEADERS})
	source_group ( TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LOCAL_SOURCES})
	set ( ${hdr_outvarname} "${LOCAL_HEADERS}" PARENT_SCOPE )
	set ( ${src_outvarname} "${LOCAL_SOURCES}" PARENT_SCOPE )
endfunction ()

function ( glob_sources src_outvarname )
	file ( GLOB_RECURSE LOCAL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src**/*.cpp" )
	source_group ( TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LOCAL_SOURCES})
	set ( ${src_outvarname} "${LOCAL_SOURCES}" PARENT_SCOPE )
endfunction()

function ( glob_modules src_outvarname )
	file ( GLOB_RECURSE LOCAL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src**/*.ixx" )
	source_group ( TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LOCAL_SOURCES})
	set ( ${src_outvarname} "${LOCAL_SOURCES}" PARENT_SCOPE )
endfunction()

function ( autoset_target_compile_options target_name is_headeronly )
	target_compile_features ( ${target_name}
		INTERFACE ${MY_CXX_COMPILE_FEATURES}
	)

	if ( NOT ${is_headeronly} )
		target_compile_options ( ${target_name}
			PRIVATE /W4 /MP
		)
	endif()
endfunction()

function ( get_latest_clang_format )
	file (
		COPY "${CMAKE_BINARY_DIR}/.clang-format"
		DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}" )
endfunction()
