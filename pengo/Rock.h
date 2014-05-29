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
        std::string resource_name = "res/objs/ball.obj";
        GLMmodel *m_poModel;
};

#endif // ROCK_H
