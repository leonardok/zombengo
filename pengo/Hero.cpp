#include "Hero.h"

Hero::Hero()
{
    this->rotatingLeft = false;
    this->rotatingRight = false;
}

Hero::~Hero()
{
    //dtor
}

void Hero::setCoordinates(float x, float y, float z)
{
    this->setX(x);
    this->setY(y);
    this->setZ(z);
}

/**
 * Hero::walkForward
 *
 * As there will be always only 4 angles: 0, 90, 180 and 270
 * we can just sum the current position with the result of:
 *     cos(0): 1 and sin(0): 0 - walk in the 0 degrees direction,
 *     cos(90): 0 and sin(90): 1 - walk in 90 degrees direction,
 *     and so on.
 */
void Hero::walkForward()
{
    float radians = this->getRotation() * M_PI / 180;

    this->posX += round(cos(radians));
    this->posZ += round(sin(radians));

    if(config_debug)
        std::cout << "Hero::walkForward - angle:" << this->getRotation() << " degrees\n";
        std::cout << "Hero::walkForward - angle:" << radians << " radians\n";
        std::cout << "Hero::walkForward - for x:" << round(cos(radians)) << "\n";
        std::cout << "Hero::walkForward - for z:" << round(sin(radians)) << "\n";
        std::cout << "Hero::walkForward - (X, Z): " << this->getX() << ", " << this->getZ() << "\n";
}

void Hero::rotateRight()
{
    if(config_debug)
        std::cout << "Hero::rotateRight - true\n";

    this->rotatingRight = true;
}

void Hero::rotateLeft()
{
    if(config_debug)
        std::cout << "Hero::rotateLeft - true\n";

    this->rotatingLeft = true;
}

void Hero::update()
{
    if(this->rotatingRight)
    {
        if(config_debug)
            std::cout << "Hero::update - rotating right - " << this->getRotation() << "\n";

        this->rotate(-5);

        if(fmod(this->getRotation(), 90) == 0)
        {
            this->rotatingRight = false;
        }
    }
    else if(this->rotatingLeft)
    {
        if(config_debug)
            std::cout << "Hero::update - rotating left - " << this->getRotation() << "\n";

        this->rotate(5);

        if(fmod(this->getRotation(), 90) == 0)
        {
            this->rotatingLeft = false;
        }
    }
}
