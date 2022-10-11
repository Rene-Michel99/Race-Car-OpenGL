#include <GL/glut.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <stdio.h>
#include <random>

#include "Classes/car.h"
#include "Classes/road.h"
#include "Classes/light_pole.h"


float FRICTION = 0.0023;
float FPS = 60;
int NUM_CARS = 10;
int NUM_OBSTACLES = 10;

Car car(
        glm::vec3(1,1,0),
        glm::vec3(0,0,0),
        0.005,
        2.7,
        5);
Road road(250);

glm::vec3 camPos(0,-30,4);         //posição inicial da câmera
glm::vec3 roadPos(0, 100, 0);

Car *poolCars = new Car[NUM_CARS];
LightPole *poolObstacles = new LightPole[NUM_OBSTACLES];

//função para desenhar os eixos cartesianos do sistema de coordenadas global (ou de mundo, ou de cenário)
void eixos()
{
    glBegin(GL_LINES);
    //eixo x em vermelho
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(100,0,0);
    //eixo y em verde
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,100,0);
    //eixo z em azul
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,100);
    glEnd();
}


void drawGround()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
        glColor3f(0, 0.45, 0);
        glVertex3f(-100,-250, -1.5);
        glVertex3f(-100,250,-1.5);
        glVertex3f(100,250,-1.5);
        glVertex3f(100,-250,-1.5);
    glEnd();
}


void generateRandomCars()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distColor(0, 1);
    std::uniform_real_distribution<> distPosX(-2, 2);
    std::uniform_real_distribution<> distPosY(-100, -2);
    std::uniform_real_distribution<> distAcc(0.0055, -0.00001);
    std::uniform_real_distribution<> distMaxVel(1, 5);
    for(int i=0; i<5; i++)
    {
        poolCars[i] = Car(
                glm::vec3(distColor(gen), distColor(gen), distColor(gen)),
                glm::vec3(distPosX(gen),distPosY(gen),0),
                distAcc(gen),
                distMaxVel(gen),
                5
                );
    }
}


void generateRandomObstacles()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distHeight(5, 10);
    std::uniform_real_distribution<> distPosX(-5, -3);
    std::uniform_real_distribution<> distPosY(-100, 200);
    for(int i=0; i<5; i++)
    {
        poolObstacles[i] = LightPole(
                glm::vec3(distPosX(gen),distPosY(gen),0),
                distHeight(gen),
                0.5
        );
    }
}


void init()
{
    glClearColor(0.0, 0.0, 0.45, 1.0); //cor de fundo (preto)
    glEnable(GL_DEPTH_TEST); //habilitando a remoção de faces que estejam atrás de outras (ocultas)
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glLineWidth(3);                   //largura de todas as linhas desenhadas
    glEnable(GL_MULTISAMPLE);         //habilita um tipo de antialiasing (melhora serrilhado)

    generateRandomCars();
    generateRandomObstacles();
}


float calcDisplacement()
{
    if(roadPos.y > -55) roadPos.y -= (car.velocity * car.time);
    else roadPos.y = 100;
}


void inputKeyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'x': camPos.x -= 1; break; //alterando a coordenada x da câmera
        case 'X': camPos.x += 1; break;
        case 'y': camPos.y -= 1; break; //alterando a coordenada y da câmera
        case 'Y': camPos.y += 1; break;
        case 'z': camPos.z -= 1; break; //alterando a coordenada z da câmera
        case 'Z': camPos.z += 1; break;
        case 'a': if (roadPos.x < 2.8) roadPos.x += 0.1; break;
        case 'd': if (roadPos.x > -2.8) roadPos.x -= 0.1; break;
        case 'w': car.increaseVelocity(); break;
        case 's': car.decreaseVelocity(FRICTION * 10); break;
    }

    glutPostRedisplay(); //atualiza o desenho
}

void timer(int v)
{
    glutTimerFunc(1000.0/FPS, timer, 0);
    car.decreaseVelocity(FRICTION/10);
    calcDisplacement();
    glutPostRedisplay();
}

void handleEnemies()
{
    glm::mat4 I = glm::mat4(1.0f);
    for(int i=0; i<5; i++)
    {
        glPushMatrix();
        glm::mat4 t_enemy = glm::translate(I,glm::vec3(poolCars[i].position.x + roadPos.x,poolCars[i].position.y,0.0));
        glMultMatrixf(glm::value_ptr(t_enemy));
        poolCars[i].draw();
        glPopMatrix();

        poolCars[i].increaseVelocity();
        poolCars[i].position.y += ((poolCars[i].velocity * poolCars[i].time)) - ((car.velocity * car.time));
        if(poolCars[i].position.y > 500)
        {
            poolCars[i].position.y = -100;
            poolCars[i].velocity *= 0.5;
        }
    }
}


void handleObstacles()
{
    glm::mat4 I = glm::mat4(1.0f);
    for(int i=0; i<5; i++)
    {
        glPushMatrix();
        glm::mat4 t_obstacle = glm::translate(I,glm::vec3(poolObstacles[i].position.x + roadPos.x,roadPos.y,0.0));
        glMultMatrixf(glm::value_ptr(t_obstacle));
        poolObstacles[i].draw();
        glPopMatrix();
    }
}


void draw()
{
    //limpando o frame buffer, mas também o depth buffer (buffer usado pra remoção de faces ocultas)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //definindo o tipo de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1,1,-1,1,7,250); //projeção em perspectiva: glFrustum(left,right,bottom,top,near,far)

    //definindo o posicionamento da câmera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::mat4 matrizCamera = glm::lookAt(camPos,            //eye = posição da câmera
                                         glm::vec3(0,3,1),  //at  = para onde a câmera aponta
                                         glm::vec3(0,0,1)); //up  = para onde o topo da câmera aponta
    glMultMatrixf(glm::value_ptr(matrizCamera)); //criada a matriz usando GLM, deve-se enviá-la para OpenGL*/

    drawGround();

    glPushMatrix();
    glm::mat4 I = glm::mat4(1.0f);
    glm::mat4 t_road = glm::translate(I,glm::vec3(roadPos.x,0,0.0));
    glMultMatrixf(glm::value_ptr(t_road));
    road.drawRoad();
    glPopMatrix();

    glPushMatrix();
    glm::mat4 t_strips = glm::translate(I,glm::vec3(roadPos.x,roadPos.y,0.0));
    glMultMatrixf(glm::value_ptr(t_strips));
    road.drawStrips();
    glPopMatrix();

    handleEnemies();
    handleObstacles();

    car.draw();
    eixos();

    //atualizando o desenho na tela
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_MULTISAMPLE | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(500,500);
    glutInitWindowSize(1080,720);
    glutCreateWindow("Camera e Visualizacao 3D");

    init();

    glutDisplayFunc(draw);
    glutKeyboardUpFunc(inputKeyboard);
    glutTimerFunc(1000.0/FPS, timer, 0);

    glutMainLoop();

    return 0;
}