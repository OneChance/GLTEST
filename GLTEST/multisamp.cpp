#include "stdafx.h"
#include<glew.h>
#include<glut.h>

int bgtoggle = 1;

void initMS(void){
	GLint buf, sbuf;
	int i,j;

	glClearColor(0.0,0.0,0.0,0.0);

	glGetIntegerv(GL_SAMPLE_BUFFERS,&buf);
	printf("number of sample buffers is %d \n",buf);
	glGetIntegerv(GL_SAMPLER,&sbuf);
	printf("number of samples is %d \n",sbuf);
}