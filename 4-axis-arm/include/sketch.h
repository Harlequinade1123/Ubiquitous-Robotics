#pragma once
#include "psketch.h"
#include "FourAxisArm.h"

class Sketch : public PSketch
{
    private:
    double links[4]   = {77, 85, 95, 140};
    double angles[3]  = {M_PI_2,-M_PI_2,M_PI_2};
    double pose[3];
    double base_angle = 0;

    float old_MOUSEX = 0;
    float old_MOUSEY = 0;

    float camera_angle    =   0.0;
    float camera_distance = 600.0;
    float camera_height   = 250.0;

    FourAxisArm arm;

    public:
    Sketch();
    void setup();
    void draw();
    void keyEvent(int key, int action);
    void mouseButtonEvent(int button, int action);
    void cursorPosEvent(double xpos, double ypos);
    void scrollEvent(double xoffset, double yoffset);
    void drawRobot();
};