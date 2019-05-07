#ifndef _PANCHO_XML_PARSER_
#define _PANCHO_XML_PARSER_

#include <vector>
#include <string>

#include <pancho/Entity/Alarm.hpp>
#include <pancho/Entity/Train.hpp>

namespace XMLParser
{
    std::vector<Alarm>& getLecturesFromXML(const std::string& path);
    std::vector<Train>& getTrainsFromXML(const std::string& path);
}


#endif