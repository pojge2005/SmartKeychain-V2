#pragma once

class Battery {
public:
    void begin();
    int readRaw();
};

extern Battery battery;
