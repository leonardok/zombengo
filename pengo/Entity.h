#ifndef ENTITY_H
#define ENTITY_H

#include <math.h>

#include "3DObject.h"

enum entity_codes
{
    WALL = 0,
    HERO = 2,
    ENEMY = 3,
    EMPTY = 4,
};

class Entity
{
public:
    Entity();
    int moving;
    void movement();

    void rotate(int degrees);
    void turnLeft();
    void turnBack();
    void turnRight();
    float getRotation();

    void Draw();
    void setOrigin(float x, float z);

    //getters and setters
    float getSpeed(void);
    void setSpeed(float speed);

    void setScale(float, float, float);
    void setCoordinates(float, float, float);
    void setRotation(float);
    void setX(float);
    void setY(float);
    void setZ(float);
    float getX(void);
    float getY(void);
    float getZ(void);

    void setCellX(int x);
    void setCellZ(int Y);
    int getCellX(void);
    int getCellZ(void);

    float speed;
    int cellX, cellZ;
    float posX, posY, posZ;
    float scaleX, scaleY, scaleZ;
    float rotateangle;

    C3DObject model;
    char *model_file_path;

};


#endif // ENTITY_H
