#include "stdafx.h"
#include<glew.h>
#include<glut.h>
#include<math.h>
#include <iostream>

using namespace std;

#define checkImageWidth 256
#define checkImageHeight 256
GLubyte checkImage[checkImageHeight][checkImageWidth][3];

void makeCheckImage(void){
	int i, j, c;

	for (i = 0; i < checkImageHeight;i++){
		for (j = 0; j < checkImageWidth; j++){
			c = (((i&0x10)==0)^((j&0x10)==0)) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
		}
	}
}

void initImage(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	makeCheckImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
}

void displayImage(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(0,0);
	glDrawPixels(checkImageWidth,checkImageHeight,GL_RGB,GL_UNSIGNED_BYTE,checkImage);
	glFlush();
}