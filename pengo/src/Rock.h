#ifndef ROCK_H
#define ROCK_H


#include "glm.h"
#include <string>
#include <stdio.h>

class Rock
{
    public:
        /** Default constructor */
        Rock();
        /** Default destructor */
        virtual ~Rock();

        bool LoadObject();
        void Draw();

    protected:

    private:
        std::string resource_name = "res/stones/rock1/Rock1.obj";
        GLMmodel *m_poModel;
};

#endif // ROCK_H
