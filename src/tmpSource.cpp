#include "Config.h"
#include <iostream>
#include "Definitions.h"

#undef main
int omain()
{
    Config config(base_path + "config/config.xml");
    std::cout << config << std::endl;
    return 0;
}