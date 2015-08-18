# Websites of libraries
- https://code.google.com/p/box2d/downloads/detail?name=Box2D_v2.3.0.7z&can=2&q=
- https://github.com/google/liquidfun/releases
- http://cms.ferzkopp.net/index.php/software/13-sdl-gfx
- https://www.libsdl.org/projects/SDL_image/
- https://www.libsdl.org/projects/SDL_mixer/
- https://www.libsdl.org/projects/SDL_ttf/
- https://www.libsdl.org/download-2.0.php
- http://sourceforge.net/projects/tinyxml/files/latest/download

# Dynamic Libraries
- SDL2_image-devel-2.0.0-VC.zip
- SDL2_mixer-devel-2.0-VC.zip
- SDL2_ttf-devel-2.0.12-VC.zip
- SDL2-devel-2.0.3-VC.zip

Unzip each of them into a directory of it's name. For example, you would unzip `SDL2-devel-2.0.3-VC.zip` into `SDL2-devel-2.0.3-VC.zip`.

# Static Libraries
- tinyxml_2_6_2.zip
- SDL2_gfx-1.0.1.zip
- liquidfun-1.1.0

Unzip each of these the same way.
Add CMakeLists.txt files to include the library:

```
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
```

```
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
```

liquidfun already has a CMakeLists.txt file. However, it's borked on Windows.
Fix by adding the line `FindPackage(Threads)` beneath `project(Box2D)` to 
liquidfun-1.1.0/liquidfun/Box2D/CMakeLists.txt` to make it work.

