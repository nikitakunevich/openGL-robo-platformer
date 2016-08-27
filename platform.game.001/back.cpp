#include <iostream>
#include <GL/freeglut.h>
#include <IL/il.h>

using namespace std;

struct Coord
{
	GLfloat X, Y;
};

//screen constants
const int WIDTH		=	500;
const int HEIGHT	=	500;
const int SCREEN_FPS =	60;

//game field
const int FIELD_W = 10;
const int FIELD_H = 10;
const GLfloat CELL_W = (GLfloat)WIDTH/FIELD_W;
const GLfloat CELL_H = (GLfloat)HEIGHT/FIELD_H;

//player constants
GLfloat plColor[3] = {0.66f,0.2f,0.0f};
const float plSpeed = 0.1f;//CELL_W/(1000 / SCREEN_FPS);

//player
Coord plCoord = {3*CELL_W/2, 3*CELL_H/2};
const float DEG2RAD = 3.14159/180;


char field[FIELD_W][FIELD_H] = {	{'B','B','B','B','B','B','B','B','B','B'},
									{'B','W','W','W','W','W','W','W','W','B'},
									{'B','W','B','W','W','W','W','W','W','B'},
									{'B','W','B','W','W','B','B','B','W','B'},
									{'B','W','B','W','W','B','W','B','W','B'},
									{'B','W','B','W','W','B','W','B','B','B'},
									{'B','W','W','W','W','B','W','B','W','B'},
									{'B','W','B','B','W','W','W','B','W','B'},
									{'B','W','W','W','W','B','W','W','W','B'},
									{'B','B','B','B','B','B','B','B','B','B'},
							   };
void init()
{
	glClearColor(0.f,0.5f,1.f,0.f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.f,WIDTH,HEIGHT,0.f,1.f,-1.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//Pop default matrix onto current matrix
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();

    //Save default matrix again
    glPushMatrix();

	for(int i = 0; i < FIELD_H; i++)
	{
		for(int j = 0; j < FIELD_W; j++)
		{
			if(field[i][j] == 'B')
			{
				glColor3f(1.f,1.f,1.f);
			}
			else if(field[i][j] == 'W')
			{
				glColor3f(0.f,0.f,0.f);
			}
			glRecti(j * CELL_W, i * CELL_H, (j+1) * CELL_W, (i+1) * CELL_H);
		}
	}
	glColor3fv(plColor);
	
	GLUquadricObj * obj;
	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj,GL_FILL);
	glTranslatef(plCoord.X,plCoord.Y,0.f);
	gluDisk(obj,0.f,CELL_H/2,24,1);
	glutSwapBuffers();
}

void runMainLoop( int val )
{
    //Frame logic
    display();

    //Run frame one more time
    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, val );
}

void keyboard(unsigned char Ch, int x, int y)
{
	switch(Ch)
	{
	case 'w':
		plCoord.Y -= plSpeed * (1000 / SCREEN_FPS);
		break;
	case 's':
		plCoord.Y += plSpeed * (1000 / SCREEN_FPS);
		break;
	case 'a':
		plCoord.X -= plSpeed * (1000 / SCREEN_FPS);
		break;
	case 'd':
		plCoord.X += plSpeed * (1000 / SCREEN_FPS);
		break;
	case 27:
		exit(1);
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitContextVersion(2, 1);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("game");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	//Set main loop
    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, 0 );

    //Start GLUT main loop
    glutMainLoop();

	return 0;
}