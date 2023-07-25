#pragma once

//77
//85
//95
//140
#define _USE_MATH_DEFINES
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
  bool checkInverse(double *pose);
  void getPoseFK(double *pose);
  void getAnglesIK(double *angles);
  void getMotorValues(int *angles);
  double mapFunc(double x, double in_min, double in_max, double out_min, double out_max);

 private:
  double links_[4]     = { 0, 0, 0, 0 };
  double pose_FK_[3]   = { 0, 0, 0 };
  double angles_IK_[3] = { 0, 0, 0 };
};