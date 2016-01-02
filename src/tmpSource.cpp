#include <iostream>
#include <string>

#include "tinyxml2-master/tinyxml2.h"
#include "Definitions.h"

void print_elements(tinyxml2::XMLElement *root_node)
{
    //if (!root_node) { return; }
    namespace xml = tinyxml2;
    std::cout << root_node->Attribute("name") << std::endl;

    xml::XMLElement *info_node = nullptr;
    int x1, y1, x2, y2;
    int off_x1, off_y1, off_x2, off_y2;
    float perc_x1, perc_x2, perc_y1, perc_y2;

    info_node = root_node->FirstChildElement("position");
    if (info_node)
    {
#define FILL_INT_POSITIONS(name) info_node->QueryIntAttribute(#name,&name)
        info_node->QueryIntAttribute("x1", &x1);
        FILL_INT_POSITIONS(y1);
        FILL_INT_POSITIONS(x2);
        FILL_INT_POSITIONS(y2);
        std::cout << x1<< y1<< x2<< y2 << std::endl;;
    }
    info_node = root_node->FirstChildElement("offset");
    if (info_node)
    {
        FILL_INT_POSITIONS(off_x1);
        FILL_INT_POSITIONS(off_y1);
        FILL_INT_POSITIONS(off_x2);
        FILL_INT_POSITIONS(off_y2);
        std::cout << off_x1<< off_y1<< off_x2<< off_y2 << std::endl;
    }
#undef FILL_INT_POSITIONS
    info_node = root_node->FirstChildElement("percentage");
    if (info_node)
    {
#define FILL_FLOAT_POSITIONS(name) info_node->QueryFloatAttribute(#name, &name)
        FILL_FLOAT_POSITIONS(perc_x1);
        FILL_FLOAT_POSITIONS(perc_y1);
        FILL_FLOAT_POSITIONS(perc_x2);
        FILL_FLOAT_POSITIONS(perc_y2);
        std::cout << perc_x1<< perc_x2<< perc_y1<< perc_y2 << std::endl;

#undef FILL_FLOAT_POSITIONS
    }
    for (xml::XMLElement *node = root_node->FirstChildElement("box"); node; node = node->NextSiblingElement("box"))
    {
        print_elements(node);
    }
}

#undef main
int main()
{
    namespace xml = tinyxml2;
    xml::XMLDocument doc;
    std::string filepath = base_path + "config/layout.xml";
    doc.LoadFile(filepath.c_str());
    if(doc.ErrorID() != 0)
    {
        std::cout << "couldn't load" << std::endl;
    }
    //xml::XMLElement* element = doc.FirstChildElement("box");
    //std::cout << element->Attribute("name") << std::endl;
    print_elements(doc.FirstChildElement("box"));
}

