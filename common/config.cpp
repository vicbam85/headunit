#include <stdio.h>
#include <fstream>

#include "hu_uti.h"
#include "hu_aap.h"

//#include "outputs.h"

#include "config.h"

//default settings
std::string config::configFile = "/tmp/mnt/data_persist/dev/bin/headunit.json";
bool config::launchOnDevice = true;
bool config::carGPS = true;
HU_TRANSPORT_TYPE config::transport_type = HU_TRANSPORT_TYPE::USB;

void config::parseJson(json config_json)
{
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
    printf("json config parsed\n");
}

void config::readConfig()
{
    std::ifstream ifs(config::configFile);
    //config file exists, read it
    if(ifs.good())
    {
        json config_json(ifs);
        ifs.close();

        config::parseJson(config_json);
        printf("config file read\n");
    }
}

void config::writeConfig(json config_json)
{
    std::ofstream out_file(config::configFile);
    out_file << std::setw(4) << config_json << std::endl;
    printf("config file written\n");
}

void config::updateConfigString(std::string parameter, std::string value)
{
    std::ifstream ifs(config::configFile);
    printf("updating parameter [%s] = [%s]\n", parameter.c_str(), value.c_str());
    //config file exists, read it
    if(ifs.good())
    {
        json config_json(ifs);
        ifs.close();

        config_json[parameter]=value;
        writeConfig(config_json);
        config::parseJson(config_json);
    }
}

void config::updateConfigBool(std::string parameter, bool value)
{
    std::ifstream ifs(config::configFile);
    printf("updating parameter [%s] = [%s]\n", parameter.c_str(), value ? "true" : "false");
    //config file exists, read it
    if(ifs.good())
    {
        json config_json(ifs);
        ifs.close();

        config_json[parameter]=value;
        writeConfig(config_json);
        config::parseJson(config_json);
    }
}

