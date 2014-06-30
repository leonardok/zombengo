#include "Entity.h"

Entity::Entity()
{
    rotateangle = 0.0;
    originY = 1.0;
    deslX = 0.0;
    deslZ = 0.0;
}

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

void Entity::rotateLeft()
{
    rotateangle+=90;
}

void Entity::rotateBack()
{
    rotateangle+=180;
}

void Entity::rotateRight()
{
    rotateangle+=270;
}

float Entity::getRotation()
{
    return rotateangle;
}


void Entity::Draw()
{
    glPushMatrix();
    glRotatef(getRotation(), 0,1,0);
    glTranslatef(originX+deslX, originY, -originZ+deslZ);
    model.Draw(2);
    glPopMatrix();
}

void Entity::setOrigin(float x, float z)
{
    originX = x;
    originZ = z;
}
