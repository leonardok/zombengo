#include "Entity.h"
#include<iostream>
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

void Entity::setCellZ(int z)
{
    cellZ = z;
}

int Entity::getCellX()
{
    return cellX;
}

int Entity::getCellZ()
{
    return cellZ;
}

void Entity::rotate(int degrees)
{
    rotateangle += degrees;
    rotateangle = fmod(rotateangle, 360);
}

void Entity::turnLeft()
{
    rotateangle+=90;
}

void Entity::turnBack()
{
    rotateangle+=180;
}

void Entity::turnRight()
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

void Entity::movement()
{
        int rot = getRotation();
        if(moving)
        {

            switch(rot)
            {
            case 0:
                posX+= 0.1;
                break;
            case 90:
                posZ+=0.1;
                break;
            case 180:
                posX+= -0.1;
                break;
            case 270:
                posZ+= -0.1;
                break;
            }
            cellX = floor(posX);
            cellZ = floor(posZ);

            std::cout<<posX<<" "<<posZ<<std::endl;
        }
}
