#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy: public Entity
{
public:
   Enemy();
   void movement();
   bool centerblock();
   bool collision();
   void mov();
   int state; //1 - checking 2 - moving 3 - turning
};

#endif // ENEMY_H
