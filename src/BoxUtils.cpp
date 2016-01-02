#include "BoxUtils.h"
#include "Logger.h"
extern Logger logger;

std::ostream& operator<<(std::ostream& os, const Box& box)
{
    os << box.name << ": x1: " << box.x1 << " y1: " << box.y1 << " x2: " << box.x2 << " y2: " << box.y2;
    return os;
}

bool get_boxes(std::vector<Box> & boxes, Box *parent_box, tinyxml2::XMLElement *start_node, int window_width, int window_height)
{
    namespace xml = tinyxml2;

    Box box;
    bool succeeded = false;
    xml::XMLElement *info_node = nullptr;

    int x1, y1, x2, y2;
    int off_x1, off_y1, off_x2, off_y2;
    float perc_x1, perc_x2, perc_y1, perc_y2;

    box.name = start_node->Attribute("name");
    info_node = start_node->FirstChildElement("position");
    if (info_node)
    {
        info_node->QueryIntAttribute("x1", &x1);
        info_node->QueryIntAttribute("y1", &y1);
        info_node->QueryIntAttribute("x2", &x2);
        info_node->QueryIntAttribute("y2", &y2);

        if (x1 == -1) { x1 = 0; }
        if (y1 == -1) { y1 = 0; }
        if (x2 == -1) { x2 = window_width; }
        if (y2 == -1) { y2 = window_height; }
        box.x1 = x1;
        box.x2 = x2;
        box.y1 = y1;
        box.y2 = y2;
        succeeded = true;
    }
    info_node = start_node->FirstChildElement("offset");
    if (info_node && parent_box)
    {
        info_node->QueryIntAttribute("off_x1", &off_x1);
        info_node->QueryIntAttribute("off_y1", &off_y1);
        info_node->QueryIntAttribute("off_x2", &off_x2);
        info_node->QueryIntAttribute("off_y2", &off_y2);
        //std::cout << off_x1<< off_y1<< off_x2<< off_y2 << std::endl;
        box.x1 = parent_box->x1 + off_x1;
        box.y1 = parent_box->y1 + off_y1;
        box.x2 = parent_box->x2 - off_x2;
        box.y2 = parent_box->y2 - off_y2;
        succeeded = true;
    }
    info_node = start_node->FirstChildElement("percentage");
    if (info_node && parent_box)
    {
        info_node->QueryFloatAttribute("perc_x1", &perc_x1);
        info_node->QueryFloatAttribute("perc_y1", &perc_y1);
        info_node->QueryFloatAttribute("perc_x2", &perc_x2);
        info_node->QueryFloatAttribute("perc_y2", &perc_y2);
        //std::cout << perc_x1<< perc_x2<< perc_y1<< perc_y2 << std::endl;
        int parent_width = parent_box->x2 - parent_box->x1;
        int parent_height = parent_box->y2 - parent_box->y1;
        box.x1 = (int)(parent_box->x1 + perc_x1 * parent_width);
        box.y1 = (int)(parent_box->y1 + perc_y1 * parent_height);
        box.x2 = (int)(parent_box->x2 - perc_x2 * parent_width);
        box.y2 = (int)(parent_box->y2 - perc_y2 * parent_height);
        succeeded = true;
    }
    if (!succeeded) 
    { 
        logger.log("problem in box name", box.name);
        return false; 
    }
    boxes.push_back(box);
    for (xml::XMLElement *node = start_node->FirstChildElement("box"); node; node = node->NextSiblingElement("box"))
    {
        if (!get_boxes(boxes, &box, node, window_width, window_height))
        {
            return false;
        }
    }
    return true;
}

std::vector<Box> make_boxes_from_config(std::string layout_file_path, int window_width, int window_height)
{
    namespace xml = tinyxml2;
    xml::XMLDocument doc;
    doc.LoadFile(layout_file_path.c_str());
    if (doc.ErrorID() != 0)
    {
        logger.log("couldn't load", layout_file_path);
    }

    std::vector<Box> boxes;
    //TODO: stop hardcoding window sizes!
    if (!get_boxes(boxes, nullptr, doc.FirstChildElement("box"), window_width, window_height))
    {
        logger.log("Bad xml format in", layout_file_path);
    }
    return boxes;
}