#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "tinyxml2-master/tinyxml2.h"
#include "Definitions.h"

struct Box
{
    std::string name;
    int x1, y1, x2, y2;
    friend std::ostream& operator<<(std::ostream& os, const Box& box);
};

std::ostream& operator<<(std::ostream& os, const Box& box);

bool get_boxes(std::vector<Box> & boxes, Box *parent_box, tinyxml2::XMLElement *start_node, int window_width, int window_height);

std::vector<Box> make_boxes_from_config(std::string layout_file_path, int window_width, int window_height);