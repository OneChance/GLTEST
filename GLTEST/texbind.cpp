#include "stdafx.h"
#include<glew.h>
#include<glut.h>
#include<math.h>
#include <iostream>

using namespace std;

#define imgW  64
#define imgH  64

GLubyte checkImg[imgW][imgH][4];
GLubyte otherImg[imgW][imgH][4];

GLuint texName[2];

void makeImgs(void){
	int i, j, c;

	for (i = 0; i < imgH; i++){
		for (j = 0; j < imgW; j++){
			c = (((i & 0x08) == 0) ^ ((j & 0x08) == 0)) * 255;
			checkImg[i][j][0] = (GLubyte)c;
			checkImg[i][j][1] = (GLubyte)c;
			checkImg[i][j][2] = (GLubyte)c;
			checkImg[i][j][3] = (GLubyte)255;

			c = (((i & 0x10) == 0) ^ ((j & 0x10) == 0)) * 255;
			otherImg[i][j][0] = (GLubyte)c;
			otherImg[i][j][1] = (GLubyte)0;
			otherImg[i][j][2] = (GLubyte)0;
			otherImg[i][j][3] = (GLubyte)255;
		}
	}
}

void initTB(void){
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	makeImgs();
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	glGenTextures(2,texName);
	glBindTexture(GL_TEXTURE_2D,texName[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,imgW,imgH,0,GL_RGBA,GL_UNSIGNED_BYTE,checkImg);

	
	glBindTexture(GL_TEXTURE_2D, texName[1]);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgW, imgH, 0, GL_RGBA, GL_UNSIGNED_BYTE, otherImg);

	glEnable(GL_TEXTURE_2D);
}

void displayTB(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D,texName[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
	glTexCoord2f(0.0, 4.0); glVertex3f(-2.0, 1.0, 0.0);
	glTexCoord2f(4.0, 4.0); glVertex3f(0.0, 1.0, 0.0);
	glTexCoord2f(4.0, 0.0); glVertex3f(0.0, -1.0, 0.0);
	glEnd();

	
	glBindTexture(GL_TEXTURE_2D, texName[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
	glTexCoord2f(0.0, 4.0); glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(4.0, 4.0); glVertex3f(2.41421, 1.0, -1.41421);
	glTexCoord2f(4.0, 0.0); glVertex3f(2.41421, -1.0, -1.41421);
	glEnd();
	glFlush();
}