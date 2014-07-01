#include "Enemy.h"
#include<iostream>

extern int ** map_matrix;

Enemy::Enemy()
{
    model.Init();
    //model.Load("./penguin.obj");
    model.Draw(2);
    state = 1;

}
bool Enemy::centerblock()
{
   // std::cout<<"TESTA:"<< posX-(int)posX <<" "<<posZ-(int)posZ<<std::endl;
    //if(((posX-0.05)< (int)(posX) && (int)(posY) < posY+0.05) && ((posY-0.05)< (int)(posY) && (int)(posY) < posY+0.05))
    float auxX = posX-(int)posX , auxZ = posZ-(int)posZ ;
    if(-0.05 < auxX && auxX< 0.05  && -0.05 < auxZ && auxZ< 0.05)
    {
        return true;
    }else
        {
            return false;
        }
}


bool Enemy::collision()
{

    //se está nos limites
    if(rotateangle == 270 && cellZ==-15)
        return true;
    if(rotateangle == 180 && cellX == -15)
        return true;
    if(rotateangle == 90 && cellZ == +14)
        return true;
    if(rotateangle == 0 && cellX == +14)
        return true;

    return false;
        //colisões internas
}

void Enemy::mov()
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
            cellX = (int)posX;
            cellZ = (int)posZ;

            std::cout<<posX<<" "<<posZ<<std::endl;
        }
}

void Enemy::movement()
{

    switch(state)
    {
    case 1://checking collision
        if(collision())
        {

            state = 3;
        }else{
                state = 2;
                }
            break;
    case 2://moving
            mov();
            if(centerblock())
            {
                state = 1;

            }else{
                    state = 2;
                }
            break;
    case 3://turning
        turnLeft();
        state = 1;
            break;
    }

}

