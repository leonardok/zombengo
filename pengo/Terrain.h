#ifndef TERRAIN_H
#define TERRAIN_H

#include <windows.h>

#include <GL/glut.h>

class Terrain
{
    public:
        /** Default constructor */
        Terrain();
        /** Default destructor */
        virtual ~Terrain();

        void Render();
    protected:
    private:
};

#endif // TERRAIN_H
