#include "3DObject.h"
class Entity
{
    float speed;
    int cellX, cellY;
    float posX, posY;
    float rotateangle;
    float originX, originY , originZ;
    float deslX, deslZ;
    public:
    Entity();
    int movement();
    void rotateLeft();
    void rotateBack();
    void rotateRight();
    float getRotation();
    C3DObject model;
    void Draw();
    void setOrigin(float x, float z);
    //getters and setters
    float getSpeed(void);
    void setSpeed(float speed);
    void setPosX(float x);
    void setPosY(float y);
    float getPosX(void);
    float getPosY(void);
    void setCellX(int x);
    void setCellY(int Y);
    int getCellX(void);
    int getCellY(void);

};
class Item: public Entity
{
    Item();
};

class Enemy: public Entity
{
public:
    Enemy();

};


class Block:public Entity
{
    Block();
};

class MainChar: public Entity
{
};
class EmptyCell:public Entity
{
};


