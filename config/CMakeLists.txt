project(config)

add_custom_target(config
	SOURCES
	layout.xml
)

# Recompile the game to re-copy this to the game directory