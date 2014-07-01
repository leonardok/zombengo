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

void Stage::printStageIntMap(int ** stage_map)
{
    for(int i = 0;i<32;i++)
    {
        for(int j = 0;j<32;j++)
        {
            std::cout<<stage_map[i][j]<< " ";
        }
        std::cout<<std::endl;
    }
}


int ** Stage::readImageMap(char *image_path)
{
    int i;
    int **st;
    int aux[32*32];
    mapa = LoadDIBitmap(image_path, &info);

    st = (int**) malloc(sizeof(int) * 32 * 32);

    for (i = 0; i<3*32*32 ;i+=3)
    {
        if((int)mapa[i] == 0&&(int)mapa[i+1] == 0&& (int)mapa[i+2] == 0)
        {
            aux[i/3] = 0;
        }
        if((int)mapa[i] == 0&&(int)mapa[i+1] == 0&& (int)mapa[i+2] != 0)
        {
            aux[i/3] = 1;
        }
        if((int)mapa[i] == 0&&(int)mapa[i+1] != 0&& (int)mapa[i+2] == 0)
        {
            aux[i/3] = 2;
        }
        if((int)mapa[i] != 0&&(int)mapa[i+1] == 0&& (int)mapa[i+2] == 0)
        {
            aux[i/3] = 3;
        }
        if((int)mapa[i] == 255&&(int)mapa[i+1] == 255&& (int)mapa[i+2] == 255)
        {
            aux[i/3] = 4;
        }
    }

    int k = 0 ;
    for(int i = 31;i>=0;i--)
    {
        st[i] = (int*) malloc(sizeof(int) * 32);
        for(int j = 0;j<32;j++, k++)
        {
            st[i][j] = aux[k];
        }
    }

    this->printStageIntMap(st);
    this->stage_int_map = st;
    return st;
}
