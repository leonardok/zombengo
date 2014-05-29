#include "rock.h"

Rock::Rock()
{
    //ctor
}

bool Rock::LoadObject()
{
    char aszFilename[256];
    strcpy(aszFilename, this->resource_name.c_str());

    printf("Loading Rock...\n");

    if (this->m_poModel) {
        free(this->m_poModel);
        this->m_poModel = NULL;
    }

    m_poModel = glmReadOBJ(aszFilename);
    if (!this->m_poModel)
        return false;

    glmUnitize(this->m_poModel);
    //glmScale(m_poModel,sFactor); // USED TO SCALE THE OBJECT

    glmFacetNormals(this->m_poModel);
    glmVertexNormals(this->m_poModel, 90.0);

    return true;
}


void Rock::Draw()
{
    if (this->m_poModel)
    {
        glmDraw(this->m_poModel, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
    }
}

Rock::~Rock()
{
    //dtor
}
