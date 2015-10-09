#include "Definitions.h"

std::string get_base_path()
{
	char * base_path_tmp = SDL_GetBasePath();
	if (base_path_tmp)
	{
		std::string new_base_path(base_path_tmp);
		SDL_free(base_path_tmp);
		return new_base_path;
	}
	else
	{
		std::string new_base_path("base path undetermined");
		return new_base_path;
	}
}