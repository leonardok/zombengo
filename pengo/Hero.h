#ifndef HERO_H
#define HERO_H

#include <iostream>
#include <math.h>

#include "Entity.h"

extern bool config_debug;

class Hero : public Entity
{
    public:
        Hero();
        virtual ~Hero();

        void rotateRight();
        void rotateLeft();
        bool checkForCollisions();
        void walkForward();

        void setModelPath(char *);

        void update();

    protected:
    private:
        bool rotatingRight;
        bool rotatingLeft;

        // Track old position. We empty it when stop walking
        int oldX, oldZ;
};

#endif // HERO_H
