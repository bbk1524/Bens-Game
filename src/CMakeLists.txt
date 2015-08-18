# Name the Project and give files
project(${PROJECT_NAME})

# Usage: create_unmade <file1>...
# creates files if they don't exist. Starts looking in the directory of the CMakeLists.txt file it's called in
function(create_unmade)
    foreach(word ${ARGV}) # ${ARGV} expands to all arguments
        if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${word})
            message("---- creating: ${word} ----")
            file(WRITE ${word} "")
        endif()
    endforeach()
endfunction()

set(Misc_Files
	Source.cpp
	Box.h
	Box.cpp
	Game.h
	Game.cpp
	GraphicsSystem.h
	GraphicsSystem.cpp
	Definitions.h
	Screen.h
	Screen.cpp
	InputSystem.h
	InputSystem.cpp
	Texture.h
	Texture.cpp
	DisableWarningsStart.h
	DisableWarningsEnd.h
)

create_unmade(${Misc_Files})

SOURCE_GROUP(Misc_Files FILES ${Misc_Files})
source_group(lib\\SDL2_gfx FILES ${SDL2_gfx})
SOURCE_GROUP(lib\\tinyxml FILES ${tinyxml})
source_group(lib\\tinyxml2 FILES ${tinyxml2})

add_executable(${PROJECT_NAME}
	${Misc_Files}
	${SDL2_gfx}
	${tinyxml}
	${tinyxml2}
)

target_compile_definitions(${PROJECT_NAME} PUBLIC TIXML_USE_STL)

# Includes..
include_directories(
	${SDL2_INCLUDE_DIR}
	${SDL2_IMAGE_INCLUDE_DIR}
	${SDL2_MIXER_INCLUDE_DIR}
	${SDL2_TTF_INCLUDE_DIR}
#	${Box2D_SOURCE_DIR}
)

# What it should link against
target_link_libraries(${PROJECT_NAME}
	${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY}
	${SDL2_IMAGE_LIBRARY}
	${SDL2_MIXER_LIBRARY}
	${SDL2_TTF_LIBRARY}
)


# These copies need to be run every time the game is compiled in case something changed
ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/config ${CMAKE_SOURCE_DIR}/bin/config/
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_SOURCE_DIR}/bin/assets/
)

if(MSVC)
	# Find and copy 32-bit DLLs to Game folder
	file(GLOB X86_DLL_FILES
			${SDL2_WIN}/lib/x86/*.dll
			${SDL2_IMAGE_WIN}/lib/x86/*.dll
			${SDL2_MIXER_WIN}/lib/x86/*.dll
			${SDL2_TTF_WIN}/lib/x86/*.dll
	)
	
	# Important to note that this happens at the cmake step, not the games compilation.
	# If you remove these, re-run cmake to get them back.
	file(COPY ${X86_DLL_FILES} DESTINATION ${CMAKE_SOURCE_DIR}/bin)
endif()
