#include<iostream>

#include "Enemy.h"
#include "Stage.h"

extern int ** map_matrix;
extern Stage *stage;

enum enemy_state {CHKCOLI, WALKING, TURNING};

Enemy::Enemy()
{
    model.Init();
    //model.Load("./penguin.obj");
    // model.Draw(2);

    // Start as checking for collision
    state = CHKCOLI;
}

/**
 * void Enemy::checkForCollisions()
 *
 * We only check for collisions when we are still, so no need to round
 * positions
 *
 */
void Enemy::checkForCollisions()
{
    float radians = this->getRotation() * M_PI / 180;

    // Get new position based on the current angle
    int newX = this->posX + round(cos(radians));
    int newZ = this->posZ + round(sin(radians));

    if(config_debug) std::cout << "Checking collisions at " << newX << " " << newZ << std::endl;

    if(map_matrix[newX][newZ] != EMPTY)
    {
        if(config_debug) std::cout << "Not empty cell, it has " << map_matrix[newX][newZ] << ". Turning.\n";
        this->state = TURNING;


        if(map_matrix[newX][newZ] == HERO)
        {
            gameOver();
        }
    }
    else
    {
        map_matrix[newX][newZ] = ENEMY;

        // Track our last position
        this->oldX = this->posX;
        this->oldZ = this->posZ;

        this->state = WALKING;
    }

    return;
}


/**
 * void Enemy::walk()
 *
 * The walk movement will go from one coordinate to another in steps
 * It does now calculate collisions as in this step both tiles are mine.
 */
void Enemy::walk()
{
    float radians = this->getRotation() * M_PI / 180;

    float step = 0.1;

    // Get new position based on the current angle
    this->posX += step * round(cos(radians));
    this->posZ += step * round(sin(radians));

    if(config_debug) std::cout << "walked to" << this->posX << " " << this->posZ << std::endl;

    // We need this because there are some float point imprecision in
    // the 0.00001 order
    int rounded_posX = this->posX * 10;
    int rounded_posZ = this->posZ * 10;

    if(rounded_posX % 10 == 0 and rounded_posZ % 10 == 0)
    {
        if(config_debug) std::cout << "Stopped walking" << std::endl;
        map_matrix[this->oldX][this->oldZ] = EMPTY;
        this->state = CHKCOLI;
    }

    //stage->printStageIntMap(stage->stage_int_map);
}

void Enemy::turn()
{
    this->turnLeft();
    this->state = CHKCOLI;
    return;
}

void Enemy::update()
{
    switch(this->state)
    {
        case CHKCOLI: this->checkForCollisions(); break;
        case WALKING: this->walk(); break;
        case TURNING: this->turn(); break;
    }
}
