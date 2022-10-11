//
// Created by renmichel on 10/10/22.
//

#ifndef TEST_LIGHT_POLE_H
#define TEST_LIGHT_POLE_H

#include <glm/vec3.hpp>


class LightPole {
private:
    float height;
    float radius;
public:
    glm::vec3 position;
    LightPole(glm::vec3 position = glm::vec3(0,0,0), float height = 3, float radius = 2.5);
    void draw();
};


#endif //TEST_LIGHT_POLE_H
