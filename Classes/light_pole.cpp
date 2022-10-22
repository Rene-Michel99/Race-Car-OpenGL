//
// Created by renmichel on 10/10/22.
//
#include <cmath>
#include <GL/gl.h>

#include "light_pole.h"

const float PI =  3.1415927;


void drawArm(float height, float width)
{
    float z              = 0.0;
    float y              = 0.0;
    float angle          = 0.0;
    float angle_stepsize = 0.1;
    float radius = 0.3;
    float y_pos = 0.5;

    glBegin(GL_QUAD_STRIP);
    while( angle < 2*PI )
    {
        z = radius * cos(angle) + height;
        y = radius * sin(angle) + y_pos;
        glVertex3f(width, y , z);
        glVertex3f(0, y , z);
        angle = angle + angle_stepsize;
    }
    glVertex3f(0, y, radius + height);
    glVertex3f(width, y, radius + height);
    glEnd();
}


void drawSphere(double radius, int lats, int longs, float height, float posX) {
    int i, j;
    glColor3f(1, 1, 0);
    for(i = 0; i <= lats; i++) {
        double lat0 = PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++) {
            double lng = 2 * PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3f(x * zr0, y * zr0, z0 + height);
            glVertex3f((radius * x * zr0) + posX, radius * y * zr0, radius * z0 + height);
            glNormal3f(x * zr1, y * zr1, z1 + height);
            glVertex3f((radius * x * zr1) + posX, radius * y * zr1, radius * z1 + height);
        }
        glEnd();
    }
}



LightPole::LightPole(glm::vec3 position, float height, float radius, bool isLeft)
{
    this->position = position;
    this->height = height;
    this->radius = radius;
    this->isLeft = isLeft;
}

void LightPole::drawMode(int mode, glm::vec3 color, float widthArm)
{
    glPolygonMode(GL_FRONT_AND_BACK, mode);

    float x              = 0.0;
    float y              = 0.0;
    float angle          = 0.0;
    float angle_stepsize = 0.1;
    float PI =  3.1415927;

    glBegin(GL_QUAD_STRIP);
    glColor3f(color.r, color.g, color.b);
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

    drawArm(this->height-1, widthArm);
    drawSphere(0.6, 16, 16, this->height-1, widthArm);
}


void LightPole::draw(){
    float widthArm = 2.5;
    if(!this->isLeft) widthArm = -2.5;
    drawMode(GL_FILL, glm::vec3(0.67, 0.67, 0.67), widthArm);
}