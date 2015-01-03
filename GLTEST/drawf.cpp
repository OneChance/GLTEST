#include "stdafx.h"
#include<glew.h>
#include<glut.h>
#include<math.h>
#include <iostream>

using namespace std;

GLubyte rasters[24] = {
	0xc0, 0x00, 
	0xc0, 0x00,
	0xc0, 0x00,
	0xc0, 0x00,
	0xc0, 0x00,
	0xff, 0x00,
	0xff, 0x00,
	0xc0, 0x00,
	0xc0, 0x00,
	0xff, 0xc0,
	0xff, 0xc0,
};

void initDrawf(void){
	//ÏñËØ¶ÔÆë  1×Ö½Ú
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glClearColor(0.0,0.0,0.0,0.0);
}

void displayDrawf(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(.0,1.0,.0);
	glRasterPos2i(150,150);
	glColor3f(.0, 0.0, 1.0);
	glBitmap(10,12,0.0,0.0,11.0,0.0,rasters);
	glFlush();
}