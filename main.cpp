#include <GL/glut.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <random>
#include <vector>

#include "Classes/car.h"
#include "Classes/road.h"
#include "Classes/light_pole.h"


float FRICTION = 0.0023;
float FPS = 60;
int NUM_CARS = 10;
int NUM_OBSTACLES = 10;
const float MAX_DIR = 2.5, MAX_LEFT = -2.5;

Car car(
        glm::vec3(1,1,0),
        glm::vec3(0,0,0),
        0.007,
        2.7,
        5);
Road road(250);

glm::vec3 camPos(0,-30,4);
glm::vec3 at(0,3,1);
glm::vec3 roadPos(0, 100, 0);

Car *poolCars = new Car[NUM_CARS];
LightPole *poolObstacles = new LightPole[NUM_OBSTACLES];


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
    std::uniform_real_distribution<> distPosY(-250, 0);
    //std::uniform_real_distribution<> distAcc(0.0055, -0.00001);
    //std::uniform_real_distribution<> distMaxVel(1, 5);
    for(int i=0; i<NUM_CARS; i++)
    {
        poolCars[i] = Car(
                glm::vec3(distColor(gen), distColor(gen), distColor(gen)),
                glm::vec3(distPosX(gen),distPosY(gen),0),
                0.0045,
                1.5,
                5
                );
    }
}


void generateRandomObstacles()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distHeight(5, 10);
    std::uniform_real_distribution<> distPosY(0, 350);
    for(int i=0; i<NUM_OBSTACLES; i++)
    {
        double posY = distPosY(gen);
        double posX = 0;
        bool isLeft = true;
        if (i % 2 == 0) //será colocado na posição da esquerda
        {
            std::uniform_real_distribution<> distPosX(-5, -3);
            posX = distPosX(gen);
        }
        else //será colocado na posição da direita
        {
            std::uniform_real_distribution<> distPosX(3, 5);
            posX = distPosX(gen);
            isLeft = false;
        }
        poolObstacles[i] = LightPole(
                glm::vec3(posX,posY,0),
                float(distHeight(gen)),
                0.25,
                isLeft
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


void calcDisplacement()
{
    // cálculo da velocidade baseada no cálculo de deslocamento ignorando a posição
    if(roadPos.y > -55) roadPos.y -= car.velocity * car.time;
    else roadPos.y = 100;
}


void inputKeyboard(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            if (car.position.x > MAX_LEFT){
                car.moveHorizontal(-0.1);
                camPos.x -= 0.1;
                at.x -= 0.1;
            }
            break;
        case GLUT_KEY_RIGHT:
            if (car.position.x < MAX_DIR){
                car.moveHorizontal(0.1);
                camPos.x += 0.1;
                at.x += 0.1;
            } break;
        case GLUT_KEY_UP: car.increaseVelocity(); break;
        case GLUT_KEY_DOWN: car.decreaseVelocity(FRICTION * 10); break;
        default: break;
    }

    glutPostRedisplay();
}


void timer(int v)
{
    glutTimerFunc(1000.0/FPS, timer, 0);
    car.decreaseVelocity(FRICTION/2); //decrementa um pouco velocidade do carro sendo inferior a aceleração
    calcDisplacement();
    glutPostRedisplay();
}


void handleEnemies()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distPosX(-2, 2);
    glm::mat4 I = glm::mat4(1.0f);
    for(int i=0; i<NUM_OBSTACLES; i++)
    {
        glPushMatrix();
        glm::mat4 t_enemy = glm::translate(I,glm::vec3(poolCars[i].position.x,poolCars[i].position.y,0.0));
        glMultMatrixf(glm::value_ptr(t_enemy));
        poolCars[i].draw();
        glPopMatrix();

        poolCars[i].increaseVelocity();
        // subtrai a velocidade do jogador na velocidade do adversário fazendo assim que seja possível a ultrapassagem
        poolCars[i].position.y += ((poolCars[i].velocity * poolCars[i].time)) - ((car.velocity * car.time));
        if(poolCars[i].position.y < -250) // se o adversário passou muito da tela coloque-o atrás da câmera
        {
            poolCars[i].position.y = 500;
            poolCars[i].position.x = distPosX(gen);
        }
    }
}


void handleObstacles()
{
    glm::mat4 I = glm::mat4(1.0f);
    for(int i=0; i<NUM_CARS; i++)
    {
        glPushMatrix();
        glm::vec3 new_position = glm::vec3(
                poolObstacles[i].position.x,
                poolObstacles[i].position.y,
                0.0);
        glm::mat4 t_obstacle = glm::translate(I,new_position);
        glMultMatrixf(glm::value_ptr(t_obstacle));
        poolObstacles[i].draw();
        glPopMatrix();

        // soma a velocidade do carro do jogador para "ir em sua direção na mesma velocidade"
        poolObstacles[i].position.y -= car.velocity * car.time;
        if(poolObstacles[i].position.y < -150)
            poolObstacles[i].position.y = 200;
    }
}


void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //definindo o tipo de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1,1,-1,1,7,250);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::mat4 matrizCamera = glm::lookAt(camPos,
                                         at,
                                         glm::vec3(0,0,1));
    glMultMatrixf(glm::value_ptr(matrizCamera));

    drawGround();

    // translação da pista
    glPushMatrix();
    glm::mat4 I = glm::mat4(1.0f);
    glm::mat4 t_road = glm::translate(I,glm::vec3(roadPos.x,0,0.0));
    glMultMatrixf(glm::value_ptr(t_road));
    road.drawRoad();
    glPopMatrix();

    //translação das faixas do meio da pista
    glPushMatrix();
    glm::mat4 t_strips = glm::translate(I,glm::vec3(roadPos.x,roadPos.y,0.0));
    glMultMatrixf(glm::value_ptr(t_strips));
    road.drawStrips();
    glPopMatrix();

    handleEnemies();    // função para tratar a movimentação dos adversários
    handleObstacles();  // função para tratar a movimentação dos obstáculos

    glPushMatrix();
    car.draw();         // desenha o carro do jogador
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_MULTISAMPLE | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(500,500);
    glutInitWindowSize(1080,720);
    glutCreateWindow("F1 RACE");

    init();

    glutDisplayFunc(draw);
    glutSpecialUpFunc(inputKeyboard);
    glutTimerFunc(1000.0/FPS, timer, 0);

    glutMainLoop();

    return 0;
}
