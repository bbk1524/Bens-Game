#include <iostream>
#include <string>

#include "tinyxml2-master/tinyxml2.h"
#include "Definitions.h"

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
}

