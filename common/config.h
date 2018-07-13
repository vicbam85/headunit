#pragma once

class config {
public:
        static void readConfig();

        static bool launchOnDevice;
        static bool carGPS;
        static HU_TRANSPORT_TYPE transport_type;
};

