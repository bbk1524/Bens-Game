# Use with:
# include_directories(${tinyxml_SOURCE_DIR})
# and, to include the library in your solution:
# target_link_libraries(tinyxml) #no ${}
project(tinyxml)

include_directories(./tinyxml)

add_library(tinyxml STATIC
	tinyxml/tinystr.h
	tinyxml/tinyxml.h
	tinyxml/tinystr.cpp
	tinyxml/tinyxml.cpp
	tinyxml/tinyxmlerror.cpp
	tinyxml/tinyxmlparser.cpp
)

# define TIXML_USE_STL in this target
target_compile_definitions(tinyxml PUBLIC TIXML_USE_STL)

project(SDL2_gfx)
include_directories(./SDL2_gfx-1.0.1 ${SDL2_INCLUDE_DIR})
add_library(SDL2_gfx STATIC
	SDL2_gfx-1.0.1/SDL2_framerate.c
	SDL2_gfx-1.0.1/SDL2_framerate.h
	SDL2_gfx-1.0.1/SDL2_gfxPrimitives.c
	SDL2_gfx-1.0.1/SDL2_gfxPrimitives.h
	SDL2_gfx-1.0.1/SDL2_gfxPrimitives_font.h
	SDL2_gfx-1.0.1/SDL2_imageFilter.c
	SDL2_gfx-1.0.1/SDL2_imageFilter.h
	SDL2_gfx-1.0.1/SDL2_rotozoom.c
	SDL2_gfx-1.0.1/SDL2_rotozoom.h
)

project(tinyxml2)
include_directories(./tinyxml2-master)
add_library(tinyxml2 STATIC
	tinyxml2-master/tinyxml2.cpp
	tinyxml2-master/tinyxml2.h
)

add_subdirectory(Box2D-master/Box2D)
