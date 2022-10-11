//
// Created by renmichel on 10/10/22.
//
#include <cmath>
#include <GL/gl.h>

#include "light_pole.h"


LightPole::LightPole(float height, float radius)
{
    float x              = 0.0;
    float y              = 0.0;
    float angle          = 0.0;
    float angle_stepsize = 0.1;
    float PI =  3.1415927;

    glBegin(GL_QUAD_STRIP);
    glColor3f(0.05, 0.05, 0.05);
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y , height);
        glVertex3f(0, y , 0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, y, height);
    glVertex3f(radius, y, height);
    glEnd();
}