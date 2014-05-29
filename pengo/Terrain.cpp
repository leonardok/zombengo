#include "Terrain.h"

Terrain::Terrain()
{
    //ctor
}

Terrain::~Terrain()
{
    //dtor
}


void Terrain::Render()
{
    unsigned int GridSizeX = 16;
	unsigned int GridSizeY = 16;
	unsigned int SizeX = 8;
	unsigned int SizeY = 8;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GridSizeX*SizeX,0,GridSizeY*SizeY,-1.0,1.0);

	glBegin(GL_QUADS);
	for (unsigned int x =0;x<GridSizeX;++x)
		for (unsigned int y =0;y<GridSizeY;++y)
		{
			if ((x+y) & 0x00000001) //modulo 2
				glColor3f(1.0f,1.0f,1.0f); //white
			else
				glColor3f(0.0f,0.0f,0.0f); //black

			glVertex2f(    x*SizeX,    y*SizeY);
			glVertex2f((x+1)*SizeX,    y*SizeY);
			glVertex2f((x+1)*SizeX,(y+1)*SizeY);
			glVertex2f(    x*SizeX,(y+1)*SizeY);

		}
	glEnd();

}
