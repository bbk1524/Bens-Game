#pragma once

#include <string>
#include <iostream>

struct Config
{
    Config(std::string config_file_path);
    std::string title;
    std::string layout_file;
    int fps;
    int window_width;
    int window_height;

    friend std::ostream& operator<<(std::ostream& os, const Config& config);
};

std::ostream& operator<<(std::ostream& os, const Config& config);