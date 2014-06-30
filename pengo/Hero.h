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

        void setCoordinates(float, float, float);

        void rotateRight();
        void rotateLeft();
        void walkForward();

        void update();

    protected:
    private:
        bool rotatingRight;
        bool rotatingLeft;
};

#endif // HERO_H
