//
// Created by renmichel on 10/10/22.
//

#ifndef TEST_LIGHT_POLE_H
#define TEST_LIGHT_POLE_H


class LightPole {
private:
    float height;
public:
    LightPole(float height = 3, float radius = 2.5);
    void draw();
};


#endif //TEST_LIGHT_POLE_H
