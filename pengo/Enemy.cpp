#include "Enemy.h"
#include<iostream>
Enemy::Enemy()
{
    model.Init();
    //model.Load("./penguin.obj");
    model.Draw(2);
}

