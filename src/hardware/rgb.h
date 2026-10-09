#pragma once

class Rgb {
public:
    void begin();
    void off();
    void red();
    void green();
    void blue();
    void white();

private:
    void write(bool red, bool green, bool blue);
};

extern Rgb rgb;
