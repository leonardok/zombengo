#include "Stage.h"

Stage::Stage(int tam)
{
    EmptyCell e;
    std::vector<Entity> aux(tam, e);
    for(int i = 0;i<tam;i++)
        stage.push_back(aux);
}
