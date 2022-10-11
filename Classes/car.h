#ifndef CAR_H
#define CAR_H

#include <glm/vec3.hpp>

class Car{
private:
    glm::vec3 vertexes[5];
    void drawMode(int mode, glm::vec3 color);
public:
    glm::vec3 color;
    float acceleration;
    float maxVelocity;
    float velocity = 0;
    glm::vec3 position = glm::vec3(0, 0, 0);
    float time = 10;
    Car(
            glm::vec3 color = glm::vec3(1.0f),
            glm::vec3 position=glm::vec3(0,0,0),
            float acceleration = 0.15,
            float maxVelocity = 60,
            float time = 5);
    void increaseVelocity();
    void decreaseVelocity(float value);
    void setColor(glm::vec3 color);
    void draw();
};

#endif // CAR_H