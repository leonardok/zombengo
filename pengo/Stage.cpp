#include "Stage.h"

Stage::Stage(float x, float y)
{
    EmptyCell e;
    setStagesize(x, y);
    std::vector<Entity> aux((int)x, e);
     for(int j = 0;j<(int)y;j++)
        stage.push_back(aux);
}
void Stage::setStagesize(float x, float y)
{
    stagesizeX = x;
    stagesizeY = y;
}
float Stage::getStagesizeX()
{
return stagesizeX;
}
float Stage::getStagesizeY()
{
return stagesizeY;
}
