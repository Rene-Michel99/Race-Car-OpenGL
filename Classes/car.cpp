//
// Created by renmichel on 08/10/22.
//

#include <GL/gl.h>
#include <cmath>

#include "car.h"


void drawBase()
{
    glBegin(GL_QUADS);
        glVertex3f(-0.8,-4, 0.4);
        glVertex3f(-0.8,0,0.4);
        glVertex3f(0.9,0,0.4);
        glVertex3f(0.9,-4,0.4);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(-0.8,-4, -1);
        glVertex3f(-0.8,0,-1);
        glVertex3f(0.9,0,-1);
        glVertex3f(0.9,-4,-1);
    glEnd();
}

void drawRoof()
{
    glBegin(GL_QUADS);
        glVertex3f(-0.8,-2, 1.31);
        glVertex3f(-0.8,-3,1.31);
        glVertex3f(0.9,-3,1.31);
        glVertex3f(0.9,-2,1.31);
    glEnd();
}


void drawFrontLights()
{
    glBegin(GL_QUADS);
        glColor3f(1, 1, 1);
        glVertex3f(-0.7,0.1, -0.15);
        glVertex3f(-0.7,0.1,0.25);
        glVertex3f(-0.25,0.1,0.25);
        glVertex3f(-0.25,0.1,-0.15);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(0.7,0.1, -0.15);
        glVertex3f(0.7,0.1,0.25);
        glVertex3f(0.25,0.1,0.25);
        glVertex3f(0.25,0.1,-0.15);
    glEnd();
}


void drawFrontRear()
{
    glBegin(GL_QUADS);
        glColor3f(0.2, 0.2, 0.2);
        glVertex3f(-0.8,0, -1);
        glVertex3f(-0.8,0,-0.31);
        glVertex3f(0.9,0,-0.31);
        glVertex3f(0.9,0,-1);
    glEnd();
}


void drawFront()
{
    glBegin(GL_QUADS);
        glVertex3f(-0.8,0, -0.3);
        glVertex3f(-0.8,0,0.4);
        glVertex3f(0.9,0,0.4);
        glVertex3f(0.9,0,-0.3);
    glEnd();
}


void drawFrontWindow()
{
    glBegin(GL_QUADS);
        glColor3f(0, 1, 1);
        glVertex3f(-0.8,-2, 1.3);
        glVertex3f(-0.8,-1,0.4);
        glVertex3f(0.9,-1,0.4);
        glVertex3f(0.9,-2,1.3);
    glEnd();
}


void drawBackRear()
{
    glBegin(GL_QUADS);
        glColor3f(0.2, 0.2, 0.2);
        glVertex3f(-0.8,-4, -1);
        glVertex3f(-0.8,-4,-0.31);
        glVertex3f(0.9,-4,-0.31);
        glVertex3f(0.9,-4,-1);
    glEnd();
}

void drawBack()
{
    glBegin(GL_QUADS);
        glVertex3f(-0.8,-4, -0.3);
        glVertex3f(-0.8,-4,0.4);
        glVertex3f(0.9,-4,0.4);
        glVertex3f(0.9,-4,-0.3);
    glEnd();
}


void drawBackLights()
{
    glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
        glVertex3f(-0.7,-4.1, -0.15);
        glVertex3f(-0.7,-4.1,0.15);
        glVertex3f(-0.25,-4.1,0.15);
        glVertex3f(-0.25,-4.1,-0.15);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(0.7,-4.1, -0.15);
        glVertex3f(0.7,-4.1,0.15);
        glVertex3f(0.25,-4.1,0.15);
        glVertex3f(0.25,-4.1,-0.15);
    glEnd();
}


void drawBackWindow()
{
    glBegin(GL_QUADS);
        glColor3f(0, 1, 1);
        glVertex3f(-0.8,-3, 1.3);
        glVertex3f(-0.8,-4,0.4);
        glVertex3f(0.9,-4,0.4);
        glVertex3f(0.9,-3,1.3);
    glEnd();
}

void drawCylinder(float radius, float width, float end_width, bool is_front)
{
    float z              = 0.0;
    float y              = 0.0;
    float angle          = 0.0;
    float angle_stepsize = 0.1;
    float PI =  3.1415927;
    float z_pos = 0.8, y_pos = 0.5;

    if(!is_front) y_pos = 3.5;

    glBegin(GL_QUAD_STRIP);
    glColor3f(0.05, 0.05, 0.05);
    while( angle < 2*PI )
    {
        z = radius * cos(angle) - z_pos;
        y = radius * sin(angle) - y_pos;
        glVertex3f(end_width, y , z);
        glVertex3f(width, y , z);
        angle = angle + angle_stepsize;
    }
    glVertex3f(width, y, radius - 0.8);
    glVertex3f(end_width, y, radius - 0.8);
    glEnd();
}

void drawLaterals()
{
    glBegin(GL_QUADS);
        glVertex3f(0.9,0, -1);
        glVertex3f(0.9,0,0.4);
        glVertex3f(0.9,-4,0.4);
        glVertex3f(0.9,-4,-1);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(-0.8,0, -1);
        glVertex3f(-0.8,0,0.4);
        glVertex3f(-0.8,-4,0.4);
        glVertex3f(-0.8,-4,-1);
    glEnd();


}

float max(float num1, float num2)
{
    if(num1 > num2) return num1;
    return num2;
}


void Car::increaseVelocity()
{
    if(this->velocity < this->maxVelocity) this->velocity += this->acceleration;
}

void Car::decreaseVelocity(float value)
{
    if(velocity > 0) this->velocity = max(this->velocity-value, 0);
}


void Car::drawMode(int mode, glm::vec3 color)
{
    glPolygonMode(GL_FRONT_AND_BACK, mode);

    // desenha as rodas
    drawCylinder(-0.5, 0.9, 1.3, true);
    drawCylinder(0.5, -0.8, -1.2, true);
    drawCylinder(0.5, -0.8, -1.2, false);
    drawCylinder(-0.5, 0.9, 1.3, false);

    glColor3f(color.r, color.g, color.b);
    drawBase();
    drawLaterals();

    drawFrontLights();
    glColor3f(color.r, color.g, color.b);
    drawFront();
    drawFrontRear();
    drawFrontWindow();

    //TRASEIRA
    glColor3f(color.r, color.g, color.b);
    drawBack();
    drawBackRear();
    drawBackWindow();
    drawBackLights();

    glColor3f(color.r, color.g, color.b);
    drawRoof();
}

Car::Car(glm::vec3 color, glm::vec3 position, float acceleration, float maxVelocity, float time){
    this->color = color;
    vertexes[0] = glm::vec3( 1, 0, 0);
    vertexes[1] = glm::vec3( 0,-1, 0);
    vertexes[2] = glm::vec3(-1, 0, 0);
    vertexes[3] = glm::vec3( 0, 1, 0);
    vertexes[4] = glm::vec3( 0, 0, 1);
    this->position = position;
    this->acceleration = acceleration;
    this->maxVelocity = maxVelocity;
    this->time = time;
}


void Car::draw(){
    drawMode(GL_FILL, color);
    drawMode(GL_LINE, glm::vec3(0));
}