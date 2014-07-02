#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include <gl/glut.h>

//openal (sound lib)
#include <al/alut.h>

#include "config.h"

#include "Hero.h"
#include "Entity.h"
#include "Enemy.h"
#include "Wall.h"
#include "Crate.h"

//bitmap class to load bitmaps for textures
#include "bitmap.h"
#include "Stage.h"
//handle for the al.obj model
//#include "ModelAl.h"

//handle generic obj models
#include "3DObject.h"

#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "alut.lib")

#define PI 3.14159265

// sound stuff
#define NUM_BUFFERS 1
#define NUM_SOURCES 1
#define NUM_ENVIRONMENTS 1

#define SMOOTH 0
#define SMOOTH_MATERIAL 1
#define SMOOTH_MATERIAL_TEXTURE 2

void mainInit();
void initSound();
void initTexture();
void initModel();
void initLight();
void enableFog();
void createGLUI();
void mainRender();
void mainCreateMenu();
void onMouseButton(int button, int state, int x, int y);
void onMouseMove(int x, int y);
void onKeyDown(unsigned char key, int x, int y);
void onKeyUp(unsigned char key, int x, int y);
void onGLUIEvent(int id);
void onWindowReshape(int x, int y);
void mainIdle();
int main(int argc, char **argv);
void setWindow();
void setViewport(GLint left, GLint right, GLint bottom, GLint top);
void updateState();
void renderFloor();
void updateCam();
void setTextureToOpengl();

/**
Characters
*/
Enemy e;
Hero *hero;
Wall *w1;
Crate *c1;
std::vector<Crate *> crates;

Stage *stage;
std::vector<Enemy *> enemies;
int ** map_matrix;

/**
Screen dimensions
*/
int windowWidth = 600;
int windowHeight = 480;

/**
Screen position
*/
int windowXPos = 100;
int windowYPos = 150;

int mainWindowId = 0;

double xOffset = -1.9;
double yOffset = -1.3;
int mouseLastX = 0;
int mouseLastY = 0;

float roty = 0.0f;
float rotx = 90.0f;

bool rightPressed = false;
bool leftPressed = false;
bool upPressed = false;
bool downPressed = false;

bool spacePressed = false;

float speedX = 0.0f;
float speedY = 0.0f;
float speedZ = 0.0f;

float posX = 0.0f;
float posY = 4.0f;
float posZ = 4.0f;

/*
variavel auxiliar pra dar variação na altura do ponto de vista ao andar.
*/
float headPosAux = 0.0f;

float maxSpeed = 0.25f;

float planeSize = 20.0f;

// more sound stuff (position, speed and orientation of the listener)
ALfloat listenerPos[]={0.0,0.0,4.0};
ALfloat listenerVel[]={0.0,0.0,0.0};
ALfloat listenerOri[]={0.0,0.0,1.0,
						0.0,1.0,0.0};

// now the position and speed of the sound source
ALfloat source0Pos[]={ -2.0, 0.0, 0.0};
ALfloat source0Vel[]={ 0.0, 0.0, 0.0};

// buffers for openal stuff
ALuint  buffer[NUM_BUFFERS];
ALuint  source[NUM_SOURCES];
ALuint  environment[NUM_ENVIRONMENTS];
ALsizei size,freq;
ALenum  format;
ALvoid  *data;



// parte de código extraído de "texture.c" por Michael Sweet (OpenGL SuperBible)
// texture buffers and stuff
int i;                       /* Looping var */
BITMAPINFO	*info;           /* Bitmap information */
GLubyte	    *bits;           /* Bitmap RGB pixels */
GLubyte     *ptr;            /* Pointer into bit buffer */
GLubyte	    *rgba;           /* RGBA pixel buffer */
GLubyte	    *rgbaptr;        /* Pointer into RGBA buffer */
GLubyte     temp;            /* Swapping variable */
GLenum      type;            /* Texture type */
GLuint      texture;         /* Texture object */
GLubyte    *mapa;






bool crouched = false;
bool running = false;
bool jumping = false;
float jumpSpeed = 0.06;
float gravity = 0.004;
float heightLimit = 0.2;
float posYOffset = 0.2;

float backgrundColor[4] = {0.0f,0.0f,0.0f,1.0f};

C3DObject cObj;


void setWindow() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)windowWidth/(GLfloat)windowHeight,0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posX,posY + 0.025 * std::abs(sin(headPosAux*PI/180)),posZ,
		posX + sin(roty*PI/180),posY + 0.025 * std::abs(sin(headPosAux*PI/180)) + cos(rotx*PI/180),posZ -cos(roty*PI/180),
		0.0,1.0,0.0);
}

/**
Atualiza a posição e orientação da camera
*/
void updateCam()
{
    float posX = hero->getX();
    float posZ = hero->getZ();
    float heroAngle = hero->getRotation();

    float distance = 20.0;      // Straight line distance between the camera and look at point

    // Calculate the camera position using the distance and angles
    float camX = posX + distance * -cosf(heroAngle * (M_PI/180));
    float camY = posY;
    float camZ = posZ + distance * -sinf(heroAngle * (M_PI/180));

    /**
       void gluLookAt( GLdouble eyeX,      \
                       GLdouble eyeY,       |- Camera position
                       GLdouble eyeZ,      /
                       GLdouble centerX,   \
                       GLdouble centerY,    |- Where the camera is pointing to
                       GLdouble centerZ,   /
                       GLdouble upX,       \
                       GLdouble upY,        |- Up vector
                       GLdouble upZ )      /
     */
	gluLookAt(camX,
           camY,
           camZ,
           posX + cos(hero->getRotation()*PI/180),
           posY + 0.5,
           posZ + sin(hero->getRotation()*PI/180),
           0.0,
           1.5,
           0.0);

    GLfloat light_position1[] = {0.0,2.0,0.0, 0.5 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
}

void initLight() {
    glEnable(GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable( GL_LIGHT1 );

	GLfloat light_ambient[] = {1.0f, 1.0f, 1.0f ,0.5 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 0.5 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 0.5 };
	GLfloat light_position0[] = {0.0, 0.0, 0.0, 0.5 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	GLfloat light_position1[] = {0.0, 0.0, 0.0, -5.5 };

    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

}

void setViewport(GLint left, GLint right, GLint bottom, GLint top) {
	glViewport(left, bottom, right - left, top - bottom);
}


/**
Initialize
*/
void mainInit() {
	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0f,0.0f,0.0f);
	setWindow();
	setViewport(0, windowWidth, 0, windowHeight);

	// habilita remocao de faces ocultas

	glFrontFace (GL_CCW);

	glEnable(GL_CULL_FACE);

	// habilita o z-buffer
	glEnable(GL_DEPTH_TEST);

    initTexture();

	//initModel();

	initLight();

    // hero
    hero = new Hero();
    hero->setCoordinates(0, 1, 0);
    hero->setScale(0.6, 0.6, 0.6);
    hero->setModelPath(hero_model);

	printf("w - andar \n");
	printf("s - ir pra tras \n");
	printf("mouse - direcao \n");
	printf("r - correr \n");
	printf("c - abaixar \n");
	printf("espaco - pular \n");

}

void initModel() {
	printf("Loading models.. \n");
	cObj.Init();
	cObj.Load("penguin.obj");
	//modelAL = CModelAl();
	//modelAL.Init();
	printf("Models ok. \n \n \n");
}

/**
Initialize the texture using the library bitmap
*/
void initTexture(void)
{
    printf ("\nLoading texture..\n");
    // Load a texture object (256x256 true color)
    bits = LoadDIBitmap(".\\res\\tiledbronze.bmp", &info);
    if (bits == (GLubyte *)0) {
		printf ("Error loading texture!\n\n");
		return;
	}
    // Figure out the type of texture
    if (info->bmiHeader.biHeight == 1)
      type = GL_TEXTURE_1D;
    else
      type = GL_TEXTURE_2D;

    // Create and bind a texture object
    glGenTextures(1, &texture);
	glBindTexture(type, texture);

    // Create an RGBA image
    rgba = (GLubyte *)malloc(info->bmiHeader.biWidth * info->bmiHeader.biHeight * 4);

    i = info->bmiHeader.biWidth * info->bmiHeader.biHeight;
    for( rgbaptr = rgba, ptr = bits;  i > 0; i--, rgbaptr += 4, ptr += 3)
    {
            rgbaptr[0] = ptr[2];     // windows BMP = BGR
            rgbaptr[1] = ptr[1];
            rgbaptr[2] = ptr[0];
            rgbaptr[3] = (ptr[0] + ptr[1] + ptr[2]) / 3;
    }

    glTexImage2D(type, 0, 4, info->bmiHeader.biWidth, info->bmiHeader.biHeight,
                  0, GL_RGBA, GL_UNSIGNED_BYTE, rgba );


    printf("Textura %d\n", texture);
	printf("Textures ok.\n\n", texture);
}



void renderCrates()
{
    int i;
    for(i = 0; i < crates.size(); i++)
    {
        crates[i]->Draw();
    }
}


void renderWalls()
{
    w1 = new Wall();
    //w1->model.Load("res/objs/wall/mauerwerk.obj");
    w1->setCoordinates(20.0, 0.0, 10.0);

    glBegin(GL_QUADS);
        glVertex3f(-20.0, 0.0, 20.0);
        glVertex3f(-20.0, 3.0, 20.0);
        glVertex3f( 20.0, 3.0, 20.0);
        glVertex3f( 20.0, 0.0, 20.0);

        glVertex3f( 20.0, 0.0,  20.0);
        glVertex3f( 20.0, 3.0,  20.0);
        glVertex3f( 20.0, 3.0, -20.0);
        glVertex3f( 20.0, 0.0, -20.0);

        glVertex3f(-20.0, 0.0, -20.0);
        glVertex3f(-20.0, 3.0, -20.0);
        glVertex3f(-20.0, 3.0, 20.0);
        glVertex3f(-20.0, 0.0, 20.0);

        glVertex3f( 20.0, 3.0, -20.0);
        glVertex3f( 20.0, 0.0, -20.0);
        glVertex3f(-20.0, 0.0, -20.0);
        glVertex3f(-20.0, 3.0, -20.0);
    glEnd();
}

void renderFloor() {
	// i want some nice, smooth, antialiased lines
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

	// set things up to render the floor with the texture
	glShadeModel(GL_FLAT);
	glEnable (type);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(0.4f,0.4f,0.4f,1.0f);

	glPushMatrix();

	float textureScaleX = 10.0;
	float textureScaleY = 10.0;

	glBegin(GL_QUADS);
		glTexCoord2f(textureScaleX, 0.0f);   // coords for the texture
		glVertex3f(0.0f, 0.0f, planeSize);

		glTexCoord2f(0.0f, 0.0f);  // coords for the texture
		glVertex3f(planeSize, 0.0f, planeSize);

		glTexCoord2f(0.0f, textureScaleY);  // coords for the texture
		glVertex3f(planeSize, 0.0f, 0.0f);

		glTexCoord2f(textureScaleX, textureScaleY);  // coords for the texture
		glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

    //renderWalls();


    glDisable(type);

    /**
     * Draw lines on the floor
     * They have an y offset to avoid z-fighting
     */
    glColor4f(0.0f,0.0f,0.0f,1.0f);
	glBegin(GL_LINES);
	for (int i = 0; i <= planeSize; i++) {
		glVertex3f(0.0f, 0.001f, i);
		glVertex3f(planeSize, 0.001f, i);
	}
	for (int i = 0; i <= planeSize; i++) {
		glVertex3f(i, 0.001f, 0);
		glVertex3f(i, 0.001f, planeSize);
	}
	glEnd();

	glPopMatrix();

}

void renderScene() {
	glClearColor(0.8,0.8,0.8,0.8);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // limpar o depth buffer

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	updateCam();

	renderFloor();
	renderCrates();

    for(int i = 0 ;i < enemies.size();i++)
    {
        enemies[i]->movement();
        enemies[i]->Draw();
    }

    hero->Draw();
}

void updateState() {
	if (upPressed) {
		// efeito de "sobe e desce" ao andar
		/*
		headPosAux += 7.0f;
		if (headPosAux > 180.0f) {
			headPosAux = 0.0f;
		}
		*/

        hero->walkForward();

	} else {
		// parou de andar, para com o efeito de "sobe e desce"
		headPosAux = fmod(headPosAux, 90) - 1 * headPosAux / 90;
		headPosAux -= 4.0f;
		if (headPosAux < 0.0f) {
			headPosAux = 0.0f;
		}
	}

}

/**
Render scene
*/
void mainRender() {
	updateState();

    // update hero position (rotation...)
	hero->update();

	renderScene();

	glFlush();
	glutPostRedisplay();
	Sleep(30);
}

/**
Handles events from the mouse right button menu
*/
void mainHandleMouseRightButtonMenuEvent(int option) {
	switch (option) {
		case 1 :
			exit(0);
			break;
		default:
			break;
	}
}

/**
Create mouse button menu
*/
void mainCreateMenu() {
	glutCreateMenu(mainHandleMouseRightButtonMenuEvent);
	glutAddMenuEntry("Quit", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/**
Mouse button event handler
*/
void onMouseButton(int button, int state, int x, int y) {
	//printf("onMouseButton button: %d \n", button);
	glutPostRedisplay();
}

/**
Mouse move while button pressed event handler
*/
void onMouseMove(int x, int y) {

	/*mouseLastX = x;
	mouseLastY = y;*/

	glutPostRedisplay();
}

/**
Mouse move with no button pressed event handler
*/
void onMousePassiveMove(int x, int y) {

	roty += (x - mouseLastX);

	rotx -= (y - mouseLastY);

	if (rotx < -128.0) {
		rotx = -128.0;
	}

	if (rotx > -45.0) {
		rotx = -45.0;
	}

	mouseLastX = x;
	mouseLastY = y;

	//glutPostRedisplay();
}

/**
Key press event handler
*/
void onKeyDown(unsigned char key, int x, int y) {
	//printf("%d \n", key);
	switch (key) {
		case 32: //space
			if (!spacePressed && !jumping) {
				jumping = true;
				speedY = jumpSpeed;
			}
			spacePressed = true;
			break;
		case 119: //w
			if (!upPressed) {
				alSourcePlay(source[0]);
			}
			upPressed = true;
			break;
		case 115: //s
			downPressed = true;
			break;
		case 97: //a
			hero->rotateLeft();
			break;
		case 100: //d
			hero->rotateRight();
			break;
		case 99: //c
			crouched = true;
			break;
		case 114: //r
			running = true;
			break;
		default:
			break;
	}

	//glutPostRedisplay();
}

/**
Key release event handler
*/
void onKeyUp(unsigned char key, int x, int y) {
	switch (key) {
		case 32: //space
			spacePressed = false;
			break;
		case 119: //w
			if (upPressed) {
				alSourceStop(source[0]);
			}
			upPressed = false;
			break;
		case 115: //s
			downPressed = false;
			break;
		case 99: //c
			crouched = false;
			break;
		case 114: //r
			running = false;
			break;
		case 27:
			exit(0);
			break;
		default:
			break;
	}

	//glutPostRedisplay();
}

void onWindowReshape(int x, int y) {
	windowWidth = x;
	windowHeight = y;
	setWindow();
	setViewport(0, windowWidth, 0, windowHeight);

}

/**
Glut idle funtion
*/
void mainIdle() {
	/**
	Set the active window before send an glutPostRedisplay call
	so it wont be accidently sent to the glui window
	*/

	glutSetWindow(mainWindowId);
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
    config_debug = true;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitWindowPosition(windowXPos,windowYPos);

	/**
	Store main window id so that glui can send it redisplay events
	*/
	mainWindowId = glutCreateWindow("FPS");

	glutDisplayFunc(mainRender);

	glutReshapeFunc(onWindowReshape);

	/**
	Register mouse events handlers
	*/
	glutMouseFunc(onMouseButton);
	glutMotionFunc(onMouseMove);
	//glutPassiveMotionFunc(onMousePassiveMove);

	/**
	Register keyboard events handlers
	*/
	glutKeyboardFunc(onKeyDown);
	glutKeyboardUpFunc(onKeyUp);


    stage = new Stage(32, 32);
    map_matrix = stage->readImageMap("res/mapa.bmp");

    int mapx, mapz;
    for(mapx = 0; mapx < 32; mapx++)
    {
        for(mapz = 0; mapz < 32; mapz++)
        {
            if(map_matrix[mapx][mapz] == 0)
            {
                //std::cout << "Found a rock!\n";

                Crate *c = new Crate();

                c->model.Load("res/objs/ice/Killer_Frost_Ice_Block.obj");
                c->setCoordinates(mapx - 16, 1, mapz - 16);
                c->setScale(0.6, 0.8, 0.6);
                crates.push_back(c);
            }
            if(map_matrix[mapx][mapz] == 1 && mapz%2 == 1 && mapx%2 == 1)
            {
                Enemy* e = new Enemy();
                e->model.Load("res/objs/zombie/Lambent_Female.obj");
                e->setCoordinates(mapx - 16, 1, mapz - 16);
                e->setScale(0.6, 0.8, 0.6);
                e->setRotation(90.0);
                enemies.push_back(e);
            }
            if(map_matrix[mapx][mapz] == 1 && mapz%2 == 1 && mapx%2 == 0)
            {
                Enemy* e = new Enemy();
                e->model.Load("res/objs/zombie/Lambent_Female.obj");
                e->setCoordinates(mapx - 16, 1, mapz - 16);
                e->setScale(0.6, 0.8, 0.6);
                enemies.push_back(e);
            }

            if(map_matrix[mapx][mapz] == 1 && mapz%2 == 0 && mapx%2 == 0)
            {
                Enemy* e = new Enemy();
                e->model.Load("res/objs/zombie2/Lambent_Male.obj");
                e->setCoordinates(mapx - 16, 1, mapz - 16);
                e->setScale(0.6, 0.8, 0.6);
                e->setRotation(180.0);
                enemies.push_back(e);
            }
            if(map_matrix[mapx][mapz] == 1 && mapz%2 == 0 && mapx%2 == 1)
            {
                Enemy* e = new Enemy();
                e->model.Load("res/objs/zombie2/Lambent_Male.obj");
                e->setCoordinates(mapx - 16, 1, mapz - 16);
                e->setScale(0.6, 0.8, 0.6);
                e->setRotation(270.0);
                enemies.push_back(e);
            }
        }
    }


   //-------------------------------------
    //'e' é do tipo Enemy
    e.model.Load("res/objs/penguin.obj");
    e.moving = true;
    e.setCoordinates(16.0, 0.4, 16.0);
    e.setCellX((int)(posX));
    e.setCellZ((int)(posZ));
    e.setScale(0.6, 0.4, 0.6);
    //e.turnRight();

    //-------------------------------------

	mainInit();

	glutMainLoop();

    return 0;
}
