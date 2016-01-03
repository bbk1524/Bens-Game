#include "Config.h"
#include "tinyxml2-master/tinyxml2.h"
#include "Logger.h"
extern Logger logger;

Config::Config(std::string config_file_path)
{
    namespace xml = tinyxml2;
    xml::XMLDocument doc;
    doc.LoadFile(config_file_path.c_str());
    if (doc.ErrorID() != 0)
    {
        logger.log("couldn't load", config_file_path);
    }
    xml::XMLElement *root = doc.FirstChildElement("game");
    xml::XMLElement *field;
    auto log_field_error = [&](std::string field_name) { logger.check(field, "field not found:", field_name); };
    
    field = root->FirstChildElement("title");
    log_field_error("title");
    this->title = field->GetText();


    field = root->FirstChildElement("layout_file");
    log_field_error("layout_file");
    this->layout_file = field->GetText();

    field = root->FirstChildElement("fps");
    log_field_error("fps");
    field->QueryIntText(&fps);

    field = root->FirstChildElement("window_width");
    log_field_error("window_width");
    field->QueryIntText(&window_width);

    field = root->FirstChildElement("window_height");
    log_field_error("window_height");
    field->QueryIntText(&window_height);

}

std::ostream & operator<<(std::ostream & os, const Config & c)
{
    os << "title: " << c.title << " fps: " << c.fps << " window_width: " << c.window_width << " window_height: " << c.window_height << " layout_file: " << c.layout_file;
    return os;
}
