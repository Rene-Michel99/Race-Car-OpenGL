//
// Created by renmichel on 10/10/22.
//
#include <cmath>
#include <GL/gl.h>

#include "light_pole.h"


LightPole::LightPole(glm::vec3 position, float height, float radius)
{
    this->position = position;
    this->height = height;
    this->radius = radius;
}

void LightPole::draw()
{
    float x              = 0.0;
    float y              = 0.0;
    float angle          = 0.0;
    float angle_stepsize = 0.1;
    float PI =  3.1415927;

    glBegin(GL_QUAD_STRIP);
    glColor3f(0.67, 0.67, 0.67);
    while( angle < 2*PI )
    {
        x = this->radius * cos(angle);
        y = this->radius * sin(angle);
        glVertex3f(x, y , this->height);
        glVertex3f(x, y , 0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(this->radius, y, this->height);
    glVertex3f(this->radius, y, this->height);
    glEnd();
}