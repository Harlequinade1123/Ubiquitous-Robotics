#include "sketch.h"

Sketch::Sketch() : PSketch()
{
    size(800, 800, P3D);
    this->arm = FourAxisArm(this->links);
}

void Sketch::setup()
{
    stroke(255, 255, 255);
    arm.calcForward(this->angles);
    arm.getPoseFK(this->pose);
}

void Sketch::draw()
{
    if (glfwGetKey(this->window, GLFW_KEY_UP))
    {
        this->pose[1]++;
        this->arm.calcInverse(this->pose);
        this->arm.getAnglesIK(this->angles);
    }
    if (glfwGetKey(this->window, GLFW_KEY_DOWN))
    {
        this->pose[1]--;
        this->arm.calcInverse(this->pose);
        this->arm.getAnglesIK(this->angles);
    }
    if (glfwGetKey(this->window, GLFW_KEY_RIGHT))
    {
        this->pose[0]--;
        this->arm.calcInverse(this->pose);
        this->arm.getAnglesIK(this->angles);
    }
    if (glfwGetKey(this->window, GLFW_KEY_LEFT))
    {
        this->pose[0]++;
        this->arm.calcInverse(this->pose);
        this->arm.getAnglesIK(this->angles);
    }
    if (glfwGetKey(this->window, GLFW_KEY_Q))
    {
        this->pose[2] -= M_PI / 180;
        this->arm.calcInverse(this->pose);
        this->arm.getAnglesIK(this->angles);
    }
    if (glfwGetKey(this->window, GLFW_KEY_E))
    {
        this->pose[2] += M_PI / 180;
        this->arm.calcInverse(this->pose);
        this->arm.getAnglesIK(this->angles);
    }

    background(200);
    stroke(100);
    for (int i = -8; i <= 8; i++)
    {
        line(-400, 50 * i, 400, 50 * i);
        line(50 * i, -400, 50 * i, 400);
    }
    fill(255,0,0);
    stroke(10);
    rectMode(CENTER);
    this->drawRobot();
}

void Sketch::drawRobot()
{
    pushMatrix();
    
    rotateZ(this->base_angle);

    translate(0, 0, this->links[0] / 2);
    box(10, 10, this->links[0]);
    translate(0, 0, this->links[0] / 2);

    rotateY(-this->angles[0]);

    translate(0, 0, this->links[1] / 2);
    box(10, 10, this->links[1]);
    translate(0, 0, this->links[1] / 2);

    rotateY(this->angles[1]);

    translate(0, 0, this->links[2] / 2);
    box(10, 10, this->links[2]);
    translate(0, 0, this->links[2] / 2);

    rotateY(this->angles[2]);

    translate(0, 0, this->links[3] / 2);
    box(10, 10, this->links[3]);
    translate(0, 0, this->links[3] / 2);

    popMatrix();
}

void Sketch::keyEvent(int key, int action)
{
    
}

void Sketch::mouseButtonEvent(int button, int action)
{
    if (action == GLFW_PRESS)
    {
        std::cout << "Button Pressed" << std::endl;
    }
}

void Sketch::cursorPosEvent(double xpos, double ypos)
{
    if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        this->camera_angle -= (MOUSEX - old_MOUSEX) / 2 * M_PI / 180;
        if (this->camera_angle < -2 * M_PI)
        {
            this->camera_angle += 2 * M_PI;
        }
        else if (2 * M_PI < this->camera_angle)
        {
            this->camera_angle -= 2 * M_PI;
        }
        else
        {
            this->camera_distance -= old_MOUSEY - MOUSEY;
        }
        if (this->camera_distance < 0.1)
        {
            this->camera_distance = 0.1;
        }
        if (1000 < this->camera_distance)
        {
            this->camera_distance = 1000;
        }
        if (this->camera_height < 10)
        {
            this->camera_height = 10;
        }
        if (1000 < this->camera_height)
        {
            this->camera_height = 1000;
        }
        this->setCamera(this->camera_distance, this->camera_height, this->camera_angle);
    }
    old_MOUSEX = MOUSEX;
    old_MOUSEY = MOUSEY;
}

void Sketch::scrollEvent(double xoffset, double yoffset)
{
    translateCamera(yoffset * 50, yoffset * 50);
}