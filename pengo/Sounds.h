#ifndef SOUNDS_H
#define SOUNDS_H

#include <windows.h>
#include <stdio.h>

//openal (sound lib)
#include <al/alut.h>

#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "alut.lib")

// sound stuff
#define NUM_BUFFERS 1
#define NUM_SOURCES 1
#define NUM_ENVIRONMENTS 1

// more sound stuff (position, speed and orientation of the listener)
extern ALfloat listenerPos[];
extern ALfloat listenerVel[];
extern ALfloat listenerOri[];

// now the position and speed of the sound source
extern ALfloat source0Pos[];
extern ALfloat source0Vel[];

// buffers for openal stuff
extern ALuint  buffer[NUM_BUFFERS];
extern ALuint  source[NUM_SOURCES];
extern ALuint  environment[NUM_ENVIRONMENTS];
extern ALsizei size,freq;
extern ALenum  format;
extern ALvoid  *data;

extern float posX;
extern float posY;
extern float posZ;

class Sounds
{
    public:
        /** Default constructor */
        Sounds();
        /** Default destructor */
        virtual ~Sounds();

        void initSound();
    protected:
    private:
};

#endif // SOUNDS_H
