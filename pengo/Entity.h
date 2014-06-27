class Entity
{
    float speed;
    int cellX, cellY;
    float posX, posY;

    public:
    //Entity();
    int movement();

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
class Item:Entity
{
    Item();
};

class Enemy:Entity
{
public:
    Enemy();

};


class Block:Entity
{
    Block();
};

class MainChar: public Entity
{
};
class EmptyCell:public Entity
{
};


