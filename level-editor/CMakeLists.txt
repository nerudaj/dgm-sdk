cmake_minimum_required ( VERSION 3.22 )

project ( level-editor )

set ( DGM_LVEDIT_VERSION "2.0.1" )
set ( DGM_LVEDIT_FILENAME "dgm-level-editor-project-${DGM_LVEDIT_VERSION}-windows-x64.zip" )
set ( DGM_LVEDIT_URL "https://github.com/nerudaj/DGM-Level-Editor/releases/download/v${DGM_LVEDIT_VERSION}/${DGM_LVEDIT_FILENAME}" )

include ( FetchContent )

string ( TOLOWER ${PROJECT_NAME} lname )

FetchContent_Declare (   ${PROJECT_NAME}
	URL                  ${DGM_LVEDIT_URL}
	DOWNLOAD_NO_PROGRESS FALSE
	DOWNLOAD_NO_EXTRACT  FALSE
)

FetchContent_GetProperties ( ${PROJECT_NAME} )

if ( NOT "${${PROJECT_NAME}_POPULATED}" )
	FetchContent_Populate ( ${PROJECT_NAME} )
	set ( "${PROJECT_NAME}_POPULATED" TRUE )
endif ()

install (
	DIRECTORY   "${${lname}_SOURCE_DIR}/"
	DESTINATION "level-editor"
)