#ifndef HERO_H
#define HERO_H

#include <Entity.h>


class Hero : public Entity
{
    public:
        Hero();
        virtual ~Hero();

        void rotateRight();
        void rotateLeft();

    protected:
    private:
        bool rotatingRight;
        bool rotatingLeft;
};

#endif // HERO_H
