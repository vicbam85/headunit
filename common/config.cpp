#include <stdio.h>
#include <fstream>

#include "hu_uti.h"
#include "hu_aap.h"

//#include "outputs.h"

#include "json/json.hpp"
#include "config.h"
using json = nlohmann::json;

//default settings
bool config::launchOnDevice = true;
bool config::carGPS = true;
HU_TRANSPORT_TYPE config::transport_type = HU_TRANSPORT_TYPE::USB;

void config::readConfig()
{
        std::ifstream ifs("headunit.json");
        //config file exists, read it
        if(ifs.good())
        {
            json config_json(ifs);

            if (config_json["launchOnDevice"].is_boolean())
            {
                config::launchOnDevice = config_json["launchOnDevice"];
            }
            if (config_json["carGPS"].is_boolean())
            {
                config::carGPS = config_json["carGPS"];
            }
            if (config_json["wifiTransport"].is_boolean())
            {
                config::transport_type = config_json["wifiTransport"] ? HU_TRANSPORT_TYPE::WIFI : HU_TRANSPORT_TYPE::USB;
            }
            printf("config file read\n");
        }
}

