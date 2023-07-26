#pragma once

//77
//85
//95
//140
#include <math.h>
#include <iostream>

class FourAxisArm
{
    public:
    FourAxisArm();
    FourAxisArm(double *links);
    ~FourAxisArm();
    void calcForward(double *angles);
    void calcInverse(double *pose);
    void getPoseFK(double *pose);
    void getAnglesIK(double *angles);
    private:
    double links_[4];
    double pose_FK_[3];
    double angles_IK_[3];
};