#include "Entity.h"

Entity::Entity()
{
    rotateangle = 00.0;
    posY = 2.0;
}

float Entity::getSpeed(void)
{
    return speed;
}

void Entity::setSpeed(float s)
{
    speed = s;
}

void Entity::setCoordinates(float x, float y, float z)
{
    this->setX(x);
    this->setY(y);
    this->setZ(z);
}

void Entity::setX(float x)
{
    posX = x;
}

void Entity::setY(float y)
{
    posY = y;
}

void Entity::setZ(float z)
{
    posZ = z;
}

float Entity::getX(void)
{
    return posX;
}

float Entity::getY(void)
{
    return posY;
}

float Entity::getZ(void)
{
    return posZ;
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

void Entity::rotate(int degrees)
{
    rotateangle += degrees;
    rotateangle = fmod(rotateangle, 360);
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

    glTranslatef(posX, 1, posZ);
    glRotatef(getRotation() - 90, 0,-1,0);

    model.Draw(2);
    glPopMatrix();
}
