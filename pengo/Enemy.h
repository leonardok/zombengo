#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy: public Entity
{
public:
    Enemy();
    //void movement();
    //bool centerblock();
    //bool collision();
    //void mov();

    void checkForCollisions();
    void walk();
    void turn();
    void update();

    /**
     * State description
     * 0 - checking for collisions
     * 2 - walking
     * 3 - turning
     */
    int state;

    // Track old position. We empty it when stop walking
    int oldX, oldZ;
};

#endif // ENEMY_H
