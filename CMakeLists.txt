cmake_minimum_required(VERSION 4.2.1)

# Options
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

# Main project
project(Gojo)

# Propagate functionality
function(GojoSensei Target FolderName)
	if(TARGET ${Target})
		set_target_properties(${Target} PROPERTIES FOLDER ${FolderName})
	endif()
endfunction()

# GojoEngine and related projects
include(GNUInstallDirs) 		# makes available install variables
add_subdirectory(GojoEngine)	# builds GojoEngine
add_subdirectory(Projects)		# builds all projects that use GojoEngine
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT GraphicsEditor)

# Install
install(TARGETS GojoEngine 
				GraphicsEditor 
		DESTINATION 
				${CMAKE_INSTALL_BINDIR}
)