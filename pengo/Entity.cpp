#include "Entity.h"
#include<iostream>

extern int ** map_matrix;

Entity::Entity()
{
    rotateangle = 00.0;
    posY = 1.0;
    scaleX = scaleY = scaleZ = 1.0f;
}

float Entity::getSpeed(void)
{
    return speed;
}

void Entity::setSpeed(float s)
{
    speed = s;
}

void Entity::setScale(float x, float y, float z)
{
    this->scaleX = x;
    this->scaleY = y;
    this->scaleZ = z;
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


    glTranslatef(posX, posY, posZ);
    glRotatef(getRotation() - 90, 0,-1,0);
    glScalef(scaleX, scaleY, scaleZ);

    model.Draw(2);
    glPopMatrix();
}

/**
 * The auto movement
 *
 * The auto movement should be based on a state machine, that has the
 * following states:
 *   - moving forward
 *   - turning
 *   - check for collision
 *   - back to step 1
 *
 * This way, as we have a copy of the map matrix, we can check for collisions
 * before we walk.
 *
 * Also, when is going to walk, after checking for possible collisions on the
 * next tile, if it can walk to the next tile, mark both with this entity code,
 * so while is transitioning, it wont permit another entities to overlap part
 * of the model. - I think the sold overlapping problems we might have.
 */
void Entity::movement()
{
        int rotation = getRotation();
        int x = this->getX();
        int z = this->getZ();
        if(moving)
        {
            switch(rotation)
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
