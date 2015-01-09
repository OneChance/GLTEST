#include "stdafx.h"
#include<glew.h>
#include<glut.h>
#include<math.h>
#include <iostream>

using namespace std;

#define BUFFER_OFFSET(bytes)((GLubyte*)NULL + (bytes))

GLuint pixelBuffer;

#define checkImageWidth 64
#define checkImageHeight 64
GLubyte checkImage[checkImageHeight][checkImageWidth][3];

GLdouble zoomFactor = 1.0;
GLint height;

/*Define convolution filters*/
GLfloat horizontal[3][3] = {
	{0,-1,0}, {0,1,0}, {0,0,0}
};

GLfloat vertical[3][3] = {
	{ 0, 0, 0 }, { -1, 1, 0 }, { 0, 0, 0 }
};

GLfloat laplacian[3][3] = {
	{ -0.125, -0.125, -0.125 }, { -0.125, 1.0, -0.125 }, { -0.125, -0.125, -0.125 }
};

/* color matrix */
GLfloat m[16] = {
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	1.0, 1.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 1.0
};

#define HISTOGRAM_SIZE 256


void makeCheckImage(void){
	int i, j, c;

	for (i = 0; i < checkImageHeight;i++){
		for (j = 0; j < checkImageWidth; j++){
			c = (((i&0x08)==0)^((j&0x08)==0)) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
		}
	}
}

void initImage(void){
	glewInit();
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*color table test*/
	int i;
	GLubyte colorTable[256][3];
	for (i = 0; i < 256; i++){
		colorTable[i][0] = 255 - i;
		colorTable[i][1] = 255 - i;
		colorTable[i][2] = 255 - i;
	}
	glColorTable(GL_COLOR_TABLE, GL_RGB, 256, GL_RGB, GL_UNSIGNED_BYTE, colorTable);
	//glEnable(GL_COLOR_TABLE);  //when enable,color invert

	/*convolution test     horizontal,vertical,laplacian*/
	glConvolutionFilter2D(GL_CONVOLUTION_2D, GL_LUMINANCE, 3, 3, GL_LUMINANCE, GL_FLOAT, vertical);
	//glEnable(GL_CONVOLUTION_2D);


	glShadeModel(GL_FLAT);
	makeCheckImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	//glGenBuffers(1,&pixelBuffer);
	//glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pixelBuffer);
	//glBufferData(GL_PIXEL_UNPACK_BUFFER,3*checkImageWidth*checkImageHeight,checkImage,GL_STATIC_DRAW);

	/*柱状图统计信息*/
	glHistogram(GL_HISTOGRAM,HISTOGRAM_SIZE,GL_RGB,GL_FALSE);
	glEnable(GL_HISTOGRAM);

	/*最小最大像素值*/
	glMinmax(GL_MINMAX,GL_RGB,GL_FALSE);
	glEnable(GL_MINMAX);

}

void displayImage(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(1,1);
	glPixelZoom(3, 3);
	glDrawPixels(checkImageWidth, checkImageHeight, GL_RGB, GL_UNSIGNED_BYTE, checkImage);//checkImage     BUFFER_OFFSET(0)
	

	/*柱状图统计信息
	int i;
	GLushort values [HISTOGRAM_SIZE][3];
	glGetHistogram(GL_HISTOGRAM,GL_TRUE,GL_RGB,GL_UNSIGNED_SHORT,values);


	glBegin(GL_LINE_STRIP);
	glColor3f(1.0,0.0,0.0);
	for (i = 0; i < HISTOGRAM_SIZE; i++){
		cout << "red:" << values[i][0] << "\n";
		glVertex2s(i,values[i][0]);
	}
	glEnd();

	
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 1.0, 0.0);
	for (i = 0; i < HISTOGRAM_SIZE; i++){
		cout << "green:" << values[i][1] << "\n";
		glVertex2s(i, values[i][1]);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 0.0, 1.0);
	for (i = 0; i < HISTOGRAM_SIZE; i++){
		cout << "blue:" << values[i][2] << "\n";
		glVertex2s(i, values[i][2]);
	}
	glEnd();*/

	/*最小最大像素值*/
	GLbyte values[6];
	glGetMinmax(GL_MINMAX,GL_TRUE,GL_RGB,GL_UNSIGNED_BYTE,values);
	
	glFlush();

	cout << "red :min=" << values[0] << " max=" << values[3] << "\n";
	cout << "green :min=" << values[1] << " max=" << values[4] << "\n";
	cout << "blue :min=" << values[2] << " max=" << values[5] << "\n";
}


void reshapeImage(int w, int h){
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	height = (GLint)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void motion(int x, int y){
	GLint screeny;

	screeny = height - (GLint)y;
	glRasterPos2i(x, screeny);
	glPixelZoom(zoomFactor,zoomFactor);
	glCopyPixels(0,0,checkImageWidth,checkImageHeight,GL_COLOR);
	glPixelZoom(1.0, 1.0);
	glFlush();
}

void keyboardImage(unsigned char key, int x, int y){

	static GLboolean sink = GL_FALSE;

	switch (key)
	{
	case 'r':case 'R':
		zoomFactor = 1.0;
		glutPostRedisplay();
		break;
	case 'z':
		if (zoomFactor < 3.0){
			zoomFactor += 0.5;
		}
		break;
	case 'x':
		if (zoomFactor > 0.5){
			zoomFactor -= 0.5;
		}
		break;

	case 's':
		
		sink = !sink;

		glHistogram(GL_HISTOGRAM,HISTOGRAM_SIZE,GL_RGB,sink);
		glutPostRedisplay();

		break;

	default:
		break;
	}
}

void mouseImage(int button, int state, int x, int y){

	
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN){
				motion(x, y);
			}
			break;
		default:
			break;
	}
}