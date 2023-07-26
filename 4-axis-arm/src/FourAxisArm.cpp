#include "FourAxisArm.h"

FourAxisArm::FourAxisArm()
{}

FourAxisArm::FourAxisArm(double *links)
{
    for (int link_i = 0; link_i < 4; link_i++)
    {
        links_[link_i] = links[link_i];
    }
}

FourAxisArm::~FourAxisArm()
{}

void FourAxisArm::calcForward(double *angles)
{
    double sin_thetas[3] = { sin(-angles[0]), sin(-angles[0] + angles[1]), sin(-angles[0] + angles[1] + angles[2]) };
    double cos_thetas[3] = { cos(-angles[0]), cos(-angles[0] + angles[1]), cos(-angles[0] + angles[1] + angles[2]) };
    pose_FK_[0] =            - sin_thetas[0] * links_[1] - sin_thetas[1] * links_[2] - sin_thetas[2] * links_[3];
    pose_FK_[1] =  links_[1] + cos_thetas[0] * links_[1] + cos_thetas[1] * links_[2] + cos_thetas[2] * links_[3];
    pose_FK_[2] = -angles[0] + angles[1] + angles[2];
}

void FourAxisArm::getPoseFK(double *pose)
{
    for (int pose_i = 0; pose_i < 3; pose_i++)
    {
        pose[pose_i] = pose_FK_[pose_i];
    }
}

void FourAxisArm::calcInverse(double *pose)
{
    double old_angles_IK[3];
    for (int angle_i = 0; angle_i < 3; angle_i++)
    {
        old_angles_IK[angle_i] = angles_IK_[angle_i];
    }
    double length = pose[0] * pose[0] + pose[1] * pose[1];
    double link_sum = links_[0] + links_[1] + pose[2] + links_[3];
    double sin_thetas[3];
    double cos_thetas[3];
    double sin_alpha = sin(pose[2]);
    double cos_alpha = cos(pose[2]);
    double a = - pose[0] - sin_alpha * links_[3];
    double b =   pose[1] - links_[0] - cos_alpha * links_[3];
    cos_thetas[1] = a * a + b * b - links_[1] * links_[1] - links_[2] * links_[2];
    cos_thetas[1] /= 2 * links_[1] * links_[2];
    sin_thetas[1] = -sqrt(1 - cos_thetas[1] * cos_thetas[1]);
    angles_IK_[1] = atan2(sin_thetas[1], cos_thetas[1]);
    double m = links_[1] + cos_thetas[1] * links_[2];
    double n = sin_thetas[1] * links_[2];
    sin_thetas[0] = (- m * a + n * b) / (m * m + n * n);
    cos_thetas[0] = (  n * a + m * b) / (m * m + n * n);
    angles_IK_[0] = atan2(sin_thetas[0], cos_thetas[0]);
    angles_IK_[2] = pose[2] + angles_IK_[0] - angles_IK_[1];
    printf("%lf %lf %lf\n", pose[0], pose[1], pose[2]);
    for (int angle_i = 0; angle_i < 3; angle_i++)
    {
        if (!isfinite(angles_IK_[angle_i]) || angles_IK_[angle_i] < -M_PI || M_PI < angles_IK_[angle_i])
        {
            printf("Invalid Angle IK\n");
            angles_IK_[angle_i] = old_angles_IK[angle_i];
        }
    }
}

double map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void FourAxisArm::getAnglesIK(double *angles)
{
    for (int angle_i = 0; angle_i < 3; angle_i++)
    {
        angles[angle_i] = angles_IK_[angle_i];
    }
}
