# This doesn't work with VS2015 RC, but will with VS2013

cmake_minimum_required(VERSION 3.1)

# Solution name
project(Bens_Game)

# add warnings to all projects
if(MSVC)
    add_compile_options(/W4 /wd4100)
else(MSVC)
    add_compile_options(-std=c++1y -Wall -Wextra -pedantic -Wno-unused-parameter)
endif(MSVC)

# set output for all projects
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)

# Find dynamic libraries
# include dynamic libraries with:
# include_directories(<target_name> ${<dynamic_library_name>_INCLUDE_DIR})
# link dynamic libraries with:
# target_link_libraries(<target_name> ${<dynamic_library_name>_INCLUDE_DIR})

#Set places to look for dynamic libraries
set(SDL2_WIN "${CMAKE_SOURCE_DIR}/lib/SDL2-devel-2.0.3-VC/SDL2-2.0.3")
set(SDL2_IMAGE_WIN "${CMAKE_SOURCE_DIR}/lib/SDL2_image-devel-2.0.0-VC/SDL2_image-2.0.0")
set(SDL2_MIXER_WIN "${CMAKE_SOURCE_DIR}/lib/SDL2_mixer-devel-2.0.0-VC/SDL2_mixer-2.0.0")
set(SDL2_TTF_WIN "${CMAKE_SOURCE_DIR}/lib/SDL2_ttf-devel-2.0.12-VC/SDL2_ttf-2.0.12")

set(SDL2_INCLUDE_MAC "/usr/local/include/SDL2")
set(SDL_LIB_MAC "/usr/local/lib")

set(SDL2_INCLUDE_LINUX "/usr/include/SDL2")
set(SDL2_LIB_LINUX "/usr/lib/x86_64-linux-gnu")

# When finding the headers, I want the Windows path to be on the bottom.
# It's better that mac and linux find their system headers

# Find SDL2
find_path(SDL2_INCLUDE_DIR SDL.h
    PATHS
    "${SDL2_INCLUDE_MAC}"
    "${SDL2_INCLUDE_LINUX}"
	"${SDL2_WIN}/include"
)
find_library(SDL2_LIBRARY NAMES SDL2
    PATHS
    "${SDL2_LIB_MAC}"
    "${SDL2_LIB_LINUX}"
    "${SDL2_WIN}/lib/x86/"
)
find_library(SDL2MAIN_LIBRARY NAMES SDL2main
    PATHS
    "${SDL2_LIB_MAC}"
    "${SDL2_LIB_LINUX}"
	"${SDL2_WIN}/lib/x86/"
)

# SDL2_image
find_path(SDL2_IMAGE_INCLUDE_DIR SDL_image.h
    PATHS
    "${SDL2_INCLUDE_MAC}"
    "${SDL2_INCLUDE_LINUX}"
    "${SDL2_IMAGE_WIN}/include"
)
find_library(SDL2_IMAGE_LIBRARY NAMES SDL2_image
    PATHS
    "${SDL2_LIB_MAC}"
    "${SDL2_LIB_LINUX}"
    "${SDL2_IMAGE_WIN}/lib/x86"
)

# SDL2_mixer
find_path(SDL2_MIXER_INCLUDE_DIR SDL_mixer.h
    PATHS
    "${SDL2_INCLUDE_MAC}"
    "${SDL2_INCLUDE_LINUX}"
    "${SDL2_MIXER_WIN}/include"
)
find_library(SDL2_MIXER_LIBRARY NAMES SDL2_mixer
    PATHS
    "${SDL2_LIB_MAC}"
    "${SDL2_LIB_LINUX}"
    "${SDL2_MIXER_WIN}/lib/x86"
)

# SDL2_ttf
find_path(SDL2_TTF_INCLUDE_DIR SDL_ttf.h
    PATHS
    "${SDL2_INCLUDE_MAC}"
    "${SDL2_INCLUDE_LINUX}"
    "${SDL2_TTF_WIN}/include"
)
find_library(SDL2_TTF_LIBRARY NAMES SDL2_ttf
    PATHS
    "${SDL2_LIB_MAC}"
    "${SDL2_LIB_LINUX}"
    "${SDL2_TTF_WIN}/lib/x86"
)

# Set up static libraries. Doing it in the root CMakeLists.txt instead of sub-files
# and `add_library` gets rid of the separate projects.

set(SDL2_gfx_HOME ${CMAKE_SOURCE_DIR}/lib/SDL2_gfx-1.0.1/SDL2_gfx-1.0.1)
include_directories(${CMAKE_SOURCE_DIR}/lib/SDL2_gfx-1.0.1)
set(SDL2_gfx 
    ${SDL2_gfx_HOME}/SDL2_framerate.c
    ${SDL2_gfx_HOME}/SDL2_framerate.h
    ${SDL2_gfx_HOME}/SDL2_gfxPrimitives.c
    ${SDL2_gfx_HOME}/SDL2_gfxPrimitives.h
    ${SDL2_gfx_HOME}/SDL2_gfxPrimitives_font.h
    ${SDL2_gfx_HOME}/SDL2_imageFilter.c
    ${SDL2_gfx_HOME}/SDL2_imageFilter.h
    ${SDL2_gfx_HOME}/SDL2_rotozoom.c
    ${SDL2_gfx_HOME}/SDL2_rotozoom.h
)

include_directories(${CMAKE_SOURCE_DIR}/lib/tinyxml2-master)
set(tinyxml2_HOME ${CMAKE_SOURCE_DIR}/lib/tinyxml2-master/tinyxml2-master)
set(tinyxml2 
    ${tinyxml2_HOME}/tinyxml2.h
    ${tinyxml2_HOME}/tinyxml2.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/lib/tinyxml)
set(tinyxml_HOME ${CMAKE_SOURCE_DIR}/lib/tinyxml/tinyxml)
set(tinyxml
	${tinyxml_HOME}/tinystr.h
	${tinyxml_HOME}/tinyxml.h
	${tinyxml_HOME}/tinystr.h
	${tinyxml_HOME}/tinyxml.cpp
	${tinyxml_HOME}/tinyxmlerror.cpp
	${tinyxml_HOME}/tinyxmlparser.cpp
)

# add assets folder
add_subdirectory(assets)

add_subdirectory(config)
# Add Project Folder
add_subdirectory(src)

# Add config gonna have to change this because config is now in assets
# add_subdirectory(Config)
