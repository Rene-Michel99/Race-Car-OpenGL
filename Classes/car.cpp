//
// Created by renmichel on 08/10/22.
//

#include <GL/gl.h>
#include <cmath>

#include "car.h"

GLvoid drawCircle(const GLfloat radius,const GLuint num_vertex)
{
    GLfloat vertex[4];
    GLfloat texcoord[2];

    const GLfloat delta_angle = 2.0*M_PI/num_vertex;

    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,texID);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glBegin(GL_TRIANGLE_FAN);

    //draw the vertex at the center of the circle
    texcoord[0] = 0.5;
    texcoord[1] = 0.5;
    glTexCoord2fv(texcoord);

    vertex[0] = vertex[1] = vertex[2] = 0.0;
    vertex[3] = 1.0;
    glVertex4fv(vertex);

    for(int i = 0; i < num_vertex ; i++)
    {
        texcoord[0] = (std::cos(delta_angle*i) + 1.0)*0.5;
        texcoord[1] = (std::sin(delta_angle*i) + 1.0)*0.5;
        glTexCoord2fv(texcoord);

        vertex[0] = std::cos(delta_angle*i) * radius;
        vertex[1] = std::sin(delta_angle*i) * radius;
        vertex[2] = 0.0;
        vertex[3] = 1.0;
        glColor3f(1, 0, 0);
        glVertex4fv(vertex);
    }

    texcoord[0] = (1.0 + 1.0)*0.5;
    texcoord[1] = (0.0 + 1.0)*0.5;
    glTexCoord2fv(texcoord);

    vertex[0] = 1.0 * radius;
    vertex[1] = 0.0 * radius;
    vertex[2] = 0.0;
    vertex[3] = 1.0;
    glVertex4fv(vertex);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


GLvoid drawBase()
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

GLvoid drawRoof()
{
    glBegin(GL_QUADS);
        glVertex3f(-0.8,-2, 1.31);
        glVertex3f(-0.8,-3,1.31);
        glVertex3f(0.9,-3,1.31);
        glVertex3f(0.9,-2,1.31);
    glEnd();
}


GLvoid drawFrontLights()
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


GLvoid drawFrontRear()
{
    glBegin(GL_QUADS);
        glColor3f(0.2, 0.2, 0.2);
        glVertex3f(-0.8,0, -1);
        glVertex3f(-0.8,0,-0.31);
        glVertex3f(0.9,0,-0.31);
        glVertex3f(0.9,0,-1);
    glEnd();
}


GLvoid drawFront()
{
    glBegin(GL_QUADS);
        glVertex3f(-0.8,0, -0.3);
        glVertex3f(-0.8,0,0.4);
        glVertex3f(0.9,0,0.4);
        glVertex3f(0.9,0,-0.3);
    glEnd();
}


GLvoid drawFrontWindow()
{
    glBegin(GL_QUADS);
        glColor3f(0, 1, 1);
        glVertex3f(-0.8,-2, 1.3);
        glVertex3f(-0.8,-1,0.4);
        glVertex3f(0.9,-1,0.4);
        glVertex3f(0.9,-2,1.3);
    glEnd();
}


GLvoid drawBackRear()
{
    glBegin(GL_QUADS);
        glColor3f(0.2, 0.2, 0.2);
        glVertex3f(-0.8,-4, -1);
        glVertex3f(-0.8,-4,-0.31);
        glVertex3f(0.9,-4,-0.31);
        glVertex3f(0.9,-4,-1);
    glEnd();
}

GLvoid drawBack()
{
    glBegin(GL_QUADS);
        glVertex3f(-0.8,-4, -0.3);
        glVertex3f(-0.8,-4,0.4);
        glVertex3f(0.9,-4,0.4);
        glVertex3f(0.9,-4,-0.3);
    glEnd();
}


GLvoid drawBackLights()
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


GLvoid drawBackWindow()
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

GLvoid drawLaterals()
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

    //drawCircle(1.0, 25);
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

void Car::setColor(glm::vec3 color){
    this->color = color;
}

void Car::draw(){
    drawMode(GL_FILL, color);
    drawMode(GL_LINE, glm::vec3(0));
}