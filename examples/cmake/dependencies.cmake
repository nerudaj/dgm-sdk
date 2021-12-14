set ( DGM_LIB_VERSION "1.3.0" )
set ( SFML_VERSION    "2.5.1" )

set ( DGM_LIB_URL "https://github.com/nerudaj/dgm-lib/releases/download/v${DGM_LIB_VERSION}/dgm-lib-${DGM_LIB_VERSION}-windows-vc16-x64.zip" )
set ( SFML_URL    "https://github.com/SFML/SFML/releases/download/${SFML_VERSION}/SFML-${SFML_VERSION}-windows-vc15-64-bit.zip" )

include ( FetchContent )

function ( fetch_dependency name url headeronly )
	string ( TOLOWER ${name} lname )

	if ( ${headeronly} )	
		FetchContent_Declare ( ${name}
			URL                  ${url}
			DOWNLOAD_NO_PROGRESS TRUE
			DOWNLOAD_NO_EXTRACT  TRUE
		)
	else ()
		FetchContent_Declare ( ${name}
			URL ${url}
		)
	endif ()
	
	FetchContent_GetProperties ( ${name} )
	if ( NOT "${${name}_POPULATED}" )
		message ( "Populating ${name}" )
		FetchContent_Populate ( ${name} )
		set ( "${name}_POPULATED" TRUE PARENT_SCOPE )
	endif ()
	
	set ( "${name}_FOLDER" "${${lname}_SOURCE_DIR}" PARENT_SCOPE )
endfunction ()

# Download dependencies
fetch_dependency ( SFML ${SFML_URL}    FALSE )
fetch_dependency ( DGM  ${DGM_LIB_URL} FALSE )

# Verify folder paths
message ( "Dependencies downloaded to: " )
message ( "  DGM:  ${DGM_FOLDER}" )
message ( "  SFML: ${SFML_FOLDER}" )

# Make libraries visible to cmake linker
link_directories("${DGM_FOLDER}/lib")
link_directories("${SFML_FOLDER}/lib")

# Create symbols for linking libcfg, libstrings, libleveld and SFML

message ( "Looking for libdgm" )
find_library(LIB_DGM_D libdgm-d  NAMES libdgm-d.lib  HINTS "${DGM_FOLDER}/lib")
if ( "${LIB_DGM_D}" EQUAL "LIB_DGM_D-NOTFOUND" )
	message ( FATAL_ERROR "Cannot find libdgm-d.lib" )
endif()

find_library(LIB_DGM_R libdgm  NAMES libdgm.lib  HINTS "${DGM_FOLDER}/lib")
if ( "${LIB_DGM_R}" EQUAL "LIB_DGM_R-NOTFOUND" )
	message ( FATAL_ERROR "Cannot find libdgm.lib" )
endif()

set(LIB_DGM optimized ${LIB_DGM_R} debug ${LIB_DGM_D})
message ( "OK" )

message ( "Looking for SFML" )
find_library ( LIB_SFML_MAIN_D "sfml-main-d" NAMES "sfml-main-d.lib" HINTS "${SFML_FOLDER}/lib" )
find_library ( LIB_SFML_SYSTEM_D "sfml-system-d" NAMES "sfml-system-d.lib" HINTS "${SFML_FOLDER}/lib" )
find_library ( LIB_SFML_GRAPHICS_D "sfml-graphics-d" NAMES "sfml-graphics-d.lib" HINTS "${SFML_FOLDER}/lib" )
find_library ( LIB_SFML_WINDOW_D "sfml-window-d" NAMES "sfml-window-d.lib" HINTS "${SFML_FOLDER}/lib" )
find_library ( LIB_SFML_AUDIO_D "sfml-audio-d" NAMES "sfml-audio-d.lib" HINTS "${SFML_FOLDER}/lib" )
find_library ( LIB_SFML_NETWORK_D "sfml-network-d" NAMES "sfml-network-d.lib" HINTS "${SFML_FOLDER}/lib" )

find_library ( LIB_SFML_MAIN_R "sfml-main" NAMES "sfml-main.lib" HINTS "${SFML_FOLDER}/lib" )
find_library ( LIB_SFML_SYSTEM_R "sfml-system" NAMES "sfml-system.lib" HINTS "${SFML_FOLDER}/lib" )
find_library ( LIB_SFML_GRAPHICS_R "sfml-graphics" NAMES "sfml-graphics.lib" HINTS "${SFML_FOLDER}/lib" )
find_library ( LIB_SFML_WINDOW_R "sfml-window" NAMES "sfml-window.lib" HINTS "${SFML_FOLDER}/lib" )
find_library ( LIB_SFML_AUDIO_R "sfml-audio" NAMES "sfml-audio.lib" HINTS "${SFML_FOLDER}/lib" )
find_library ( LIB_SFML_NETWORK_R "sfml-network" NAMES "sfml-network.lib" HINTS "${SFML_FOLDER}/lib" )

set ( LIB_SFML_MAIN optimized ${LIB_SFML_MAIN_R} debug ${LIB_SFML_MAIN_D} )
set ( LIB_SFML_SYSTEM optimized ${LIB_SFML_SYSTEM_R} debug ${LIB_SFML_SYSTEM_D} )
set ( LIB_SFML_GRAPHICS optimized ${LIB_SFML_GRAPHICS_R} debug ${LIB_SFML_GRAPHICS_D} )
set ( LIB_SFML_WINDOW optimized ${LIB_SFML_WINDOW_R} debug ${LIB_SFML_WINDOW_D} )
set ( LIB_SFML_AUDIO optimized ${LIB_SFML_AUDIO_R} debug ${LIB_SFML_AUDIO_D} )
set ( LIB_SFML_NETWORK optimized ${LIB_SFML_NETWORK_R} debug ${LIB_SFML_NETWORK_D} )
message ( "OK" )
