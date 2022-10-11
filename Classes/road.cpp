//
// Created by renmichel on 09/10/22.
//

#include <GL/gl.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "road.h"

Road::Road(int width) {
    this->width = width;
}

void Road::drawStrips()
{
    glColor3f(1, 1, 1);
    float posY = 250;
    for(int i=0; i < 25; i++)
    {
        glBegin(GL_QUADS);
            glVertex3f(-0.25, posY, -1.38);
            glVertex3f(-0.25, posY-10, -1.38);
            glVertex3f(0.25, posY-10, -1.38);
            glVertex3f(0.25, posY, -1.38);
        glEnd();
        posY -= 20;
    }
}

void Road::drawRoad()
{
    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
        glVertex3f(-4,this->width*-1, -1.4);
        glVertex3f(-4,this->width,-1.4);
        glVertex3f(4,this->width,-1.4);
        glVertex3f(4,this->width*-1,-1.4);
    glEnd();

    //faixas laterais
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
        glVertex3f(-4,this->width*-1, -1.39);
        glVertex3f(-4,this->width,-1.39);
        glVertex3f(-3.7,this->width,-1.39);
        glVertex3f(-3.7,this->width*-1,-1.39);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(4,this->width*-1, -1.39);
        glVertex3f(4,this->width,-1.39);
        glVertex3f(3.7,this->width,-1.39);
        glVertex3f(3.7,this->width*-1,-1.39);
    glEnd();
}
