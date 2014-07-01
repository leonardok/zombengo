#include "Enemy.h"
#include<iostream>

extern int ** map_matrix;s

Enemy::Enemy()
{
    model.Init();
    //model.Load("./penguin.obj");
    model.Draw(2);
}

