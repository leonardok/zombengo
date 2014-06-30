#ifndef ENTITY_H
#define ENTITY_H

#include <math.h>

#include "3DObject.h"

class Entity
{
public:
    Entity();

    int movement();

    void rotate(int degrees);
    void rotateLeft();
    void rotateBack();
    void rotateRight();
    float getRotation();

    void Draw();
    void setOrigin(float x, float z);

    //getters and setters
    float getSpeed(void);
    void setSpeed(float speed);

    void setX(float);
    void setY(float);
    void setZ(float);
    float getX(void);
    float getY(void);
    float getZ(void);

    void setCellX(int x);
    void setCellY(int Y);
    int getCellX(void);
    int getCellY(void);

    float speed;
    int cellX, cellY;
    float posX, posY, posZ;
    float rotateangle;
    float originX, originY , originZ;
    float deslX, deslZ;

    C3DObject model;
    char *model_file_path;

};


#endif // ENTITY_H
