#ifndef STAGE_H
#define STAGE_H

#include<vector>

#include "Entity.h"
#include "EmptyCell.h"


class Stage
{
    float stagesizeX, stagesizeY;

public:
    std::vector<std::vector<Entity> > stage;
    Stage(float x, float y);
    void setStagesize(float x, float y);
    float getStagesizeX();
    float getStagesizeY();

/*
Caso as colisões sejam tradadas pelo Stage

void collide(Block block0, Block block1);
void collide(Block block, Item item);
void collide(Item item, Block block );
void collide(Block block, Enemy enemy);
void collide( Enemy enemy,Block block);
void collide(Block block, MainChar mc);
void collide(MainChar mc,Block block);
void collide(Item item, Enemy enemy);
void collide( Enemy enemy, Item item);
void collide(Item item, MainChar mc);
void collide(MainChar mc, Item item);
void collide(Enemy enemy, MainChar mc);
void collide(MainChar mc, Enemy enemy);
void collide(Enemy enemy0, Enemy enemy1);
*/

};

#endif // STAGE_H
