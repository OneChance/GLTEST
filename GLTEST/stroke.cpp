#include "stdafx.h"
#include<glew.h>
#include<glut.h>
#include<math.h>
#include <iostream>

using namespace std;

#define PT 1
#define STROKE 2
#define END 3

typedef struct charpoint{
	GLfloat x, y;
	int type;
}CP;

CP Adata[] = {
	{ 0, 0, PT }, { 0, 9, PT }, { 1, 10, PT }, {4,10,PT},
	{ 5, 9, PT }, { 5, 0, STROKE }, { 0, 5, PT }, {5,5,END}
};

CP Edata[] = {
	{ 5, 0, PT }, { 0, 0, PT }, { 0, 10, PT }, { 5, 10, STROKE },
	{ 0, 5, PT }, { 4, 5, END }
};

CP Pdata[] = {
	{ 0, 0, PT }, { 0, 10, PT }, { 4, 10, PT }, {5, 9, PT },
	{ 5, 6, PT }, { 4, 5, PT}, { 0, 5, END }
};

CP Rdata[] = {
	{ 0, 0, PT }, { 0, 10, PT }, { 4, 10, PT }, { 5, 9, PT },
	{ 5, 6, PT }, { 4, 5, PT }, { 0, 5, STROKE }, { 3, 5, PT },
	{5,0,END}
};

CP Sdata[] = {
	{ 0, 1, PT }, { 1, 0, PT }, { 4, 0, PT }, { 5, 1, PT },
	{ 5, 4, PT }, { 4, 5, PT }, { 1, 5, PT }, { 0, 6, PT },
	{ 0, 9, PT }, { 1, 10, PT }, { 4, 10, PT }, { 5, 9, END }
};

void drawLetter(CP *l,char c){
	glBegin(GL_LINE_STRIP);

	while (l){
		switch (l->type)
		{
			case PT:
				glVertex2fv(&l->x);
				break;
			case STROKE:
				glVertex2fv(&l->x);
				glEnd();
				glBegin(GL_LINE_STRIP);
				break;
			case END:
				glVertex2fv(&l->x);
				glEnd();
				glTranslated(8.0,0.0,0.0);
				//cout << "draw end \n";
				return;
			default:
				break;
		}

		l++;
	}
}

GLuint base;

void initStroke(void){
	
	glShadeModel(GL_FLAT);
	base = glGenLists(128);
	glNewList(base+'A',GL_COMPILE);
		drawLetter(Adata,'A');
	glEndList();

	glNewList(base + 'E', GL_COMPILE);
		drawLetter(Edata,'E');
	glEndList();

	glNewList(base + 'P', GL_COMPILE);
		drawLetter(Pdata,'P');
	glEndList();

	glNewList(base + 'R', GL_COMPILE);
		drawLetter(Rdata,'R');
	glEndList();

	glNewList(base + 'S', GL_COMPILE);
		drawLetter(Sdata,'S');
	glEndList();

	glNewList(base + ' ', GL_COMPILE);
		glTranslatef(8.0,0.0,0.0);
	glEndList();

}

char *test = "ASPER";

static void printStrokedString(char *s){
	GLsizei len = strlen(s);
	glListBase(base);
	glCallLists(len,GL_BYTE,(GLbyte *)s);
}

void displayStroke(void){

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);

	glPushMatrix();
		glScalef(2.0,2.0,2.0);
		glTranslatef(10.,30.,0.);
		printStrokedString(test);
	glPopMatrix();

	glFlush();
}

void reshapeStroke(int w, int h){
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0,(GLdouble)h);
}

void keyboardStroke(unsigned char key, int x, int y){
	switch (key)
	{
		case ' ':
			glutPostRedisplay();
			break;
	default:
		break;
	}
}