#include "Entity.h"

    float Entity::getSpeed(void)
    {
    return speed;
    }
    void Entity::setSpeed(float s)
    {
        speed = s;
    }
    void Entity::setPosX(float x)
    {
    posX = x;
    }
    void Entity::setPosY(float y)
    {
    posY = y;
    }
    float Entity::getPosX(void)
    {
    return posX;
    }
    float Entity::getPosY(void)
    {
    return posY;
    }
    void Entity::setCellX(int x)
    {
    cellX = x;
    }
    void Entity::setCellY(int y)
    {
        cellY = y;
    }
    int Entity::getCellX()
    {
        return cellX;
    }
    int Entity::getCellY()
    {
        return cellY;
    }



