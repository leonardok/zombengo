#include "Hero.h"

extern int **map_matrix;

Hero::Hero()
{
    this->rotatingLeft = false;
    this->rotatingRight = false;
}

Hero::~Hero()
{
    //dtor
}

void Hero::setModelPath(char *file_path)
{
    this->model_file_path = file_path;
    this->model.Load(this->model_file_path);
}

/**
 * void Enemy::checkForCollisions()
 *
 * We only check for collisions when we are still, so no need to round
 * positions
 *
 * Returns true if collide!
 */
bool Hero::checkForCollisions()
{
    float radians = this->getRotation() * M_PI / 180;

    // Get new position based on the current angle
    int newX = this->posX + round(cos(radians));
    int newZ = this->posZ + round(sin(radians));

    std::cout << "Checking collisions at " << newX << " " << newZ << std::endl;

    if(map_matrix[newX][newZ] != EMPTY)
    {
        std::cout << "Not empty cell, it has " << map_matrix[newX][newZ] << ".\n";
        if(map_matrix[newX][newZ] == ENEMY)
        {
            exit(0);
        }
        return true;
    }

    return false;
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

    if(checkForCollisions() == true)
    {
        std::cout << "Hero::walkForward - Collided!\n";
        return;
    }

    this->posX += round(cos(radians));
    this->posZ += round(sin(radians));

    this->setCoordinates(this->posX, this->posY, this->posZ);
    map_matrix[(int)this->posX][(int)this->posY] = HERO;


    /**
     * LOSE!!!
     */
    int newX = this->posX;
    int newZ = this->posZ;
    if(map_matrix[newX][newZ] == HERO)
    {
        exit(0);
    }

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

        this->rotate(5);

        if(fmod(this->getRotation(), 90) == 0)
        {
            this->rotatingRight = false;
        }
    }
    else if(this->rotatingLeft)
    {
        if(config_debug)
            std::cout << "Hero::update - rotating left - " << this->getRotation() << "\n";

        this->rotate(-5);

        if(fmod(this->getRotation(), 90) == 0)
        {
            this->rotatingLeft = false;
        }
    }
}
