function (copy_dlls_to_build_folders )
	message ( "Copying DLLs to build folders" )
	message ( "${SFML_FOLDER}" )

	file (GLOB DEBUG_SFML_DLLS   ${SFML_FOLDER}/bin/*-d-2.dll)
	file (GLOB RELEASE_SFML_DLLS ${SFML_FOLDER}/bin/*[oskmw]-2.dll)
	set ( OPENAL_DLL 			 ${SFML_FOLDER}/bin/openal32.dll )

	file(MAKE_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release" )

	configure_file (
		${OPENAL_DLL} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/ COPYONLY
	)

	configure_file (
		${OPENAL_DLL} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/ COPYONLY
	)

	foreach ( DLL ${DEBUG_SFML_DLLS} )
		configure_file ( ${DLL} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/ COPYONLY )
	endforeach ( DLL )

	foreach ( DLL ${RELEASE_SFML_DLLS} )
		configure_file ( ${DLL} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/ COPYONLY )
	endforeach ( DLL )
endfunction (copy_dlls_to_build_folders)
