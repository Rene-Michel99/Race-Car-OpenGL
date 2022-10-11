//
// Created by renmichel on 09/10/22.
//

#ifndef TEST_ROAD_H
#define TEST_ROAD_H

#include <glm/vec3.hpp>


class Road {
private:
    int width;
    glm::vec3 road_vertexes[4];
    glm::vec3 details_vertexes[4];
    glm::vec3 strip_vertexes[4];

public:
    Road(int width);
    void drawRoad();
    void drawStrips();
};


#endif //TEST_ROAD_H
