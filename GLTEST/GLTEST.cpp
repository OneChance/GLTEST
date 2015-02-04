#include<windows.h>
#include "stdafx.h"
#include<glut.h>
#include "glMethods.h"
#include <iostream>

using namespace std;


void main(int argc, char* argv[]){


	glutInit(&argc, argv);

	/*--------------------------draw a block
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(200, 200);

	glutCreateWindow("Test1");

	glutDisplayFunc(DrawBlock);

	*/

	/*--------------------------light move
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display2);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	*/

	/*--------------------------gl color material 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	initMethod();
	glutDisplayFunc(displayMethod);
	glutReshapeFunc(reshapeMethod);
	glutMouseFunc(mouseMethod);
	glutMainLoop(); */

	/*--------------------------gl blend
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	initBlend();
	glutDisplayFunc(displayBlend);
	glutReshapeFunc(reshapeMethod);
	glutKeyboardFunc(keyboardBlend);
	*/

	/*--------------------------gl alpha 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	initAlpha();
	glutDisplayFunc(displayAlpha);
	glutReshapeFunc(reshapeMethod);
	glutKeyboardFunc(keyboardAlpha);*/

	/*--------------------------gl alpha3d 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	initA3();
	glutDisplayFunc(displayA3);
	glutReshapeFunc(reshapeMethod);
	glutKeyboardFunc(keyboardA3);*/

	/*--------------------------gl anti-aliasing rgb
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(200, 200);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	initAAR();
	glutDisplayFunc(displayAAR);
	glutReshapeFunc(reshapeMethod);
	glutKeyboardFunc(keyboardAAR);  */

	/*--------------------------gl anti-aliasing index
	glutInitDisplayMode(GLUT_SINGLE | GLUT_INDEX);
	glutInitWindowSize(200, 200);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	initAAI();
	glutDisplayFunc(displayAAI);
	glutReshapeFunc(reshapeMethod);
	glutKeyboardFunc(keyboardAAI); */

	/*--------------------------gl multi sample  -_-! do not suppot multi sample
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(200, 200);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	initMS();
	glutDisplayFunc(displayMethod);
	glutReshapeFunc(reshapeMethod);
	glutKeyboardFunc(keyboardAAI); */


	/*--------------------------gl fog  
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	initFog();
	glutDisplayFunc(displayFog);
	glutReshapeFunc(reshapeMethod);
	glutKeyboardFunc(keyboardFog);*/

	/*--------------------------gl fog coord 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	initFC();
	glutDisplayFunc(displayFC);
	glutReshapeFunc(reshapeMethod);
	glutKeyboardFunc(keyboardFC);*/

	/*--------------------------gl view list 1 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	initVL();
	glutDisplayFunc(displayVL);
	glutReshapeFunc(reshapeVL);
	glutKeyboardFunc(keyboardVL);*/

	/*--------------------------gl view list 2
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(440, 120);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	initStroke();
	glutDisplayFunc(displayStroke);
	glutReshapeFunc(reshapeStroke);
	glutKeyboardFunc(keyboardStroke);*/

	/*--------------------------gl bitmap draw f 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(400, 100);
	glutCreateWindow(argv[0]);
	initDrawf();
	glutDisplayFunc(displayDrawf);
	glutReshapeFunc(reshapeStroke);*/

	//cout <<"byte value:"<< ((GLubyte)0) << "\n";

	/*--------------------------gl draw image 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(256, 256);
	glutInitWindowPosition(400, 100);
	glutCreateWindow(argv[0]);
	initImage();
	glutDisplayFunc(displayImage);
	glutReshapeFunc(reshapeImage);
	glutKeyboardFunc(keyboardImage);
	glutMouseFunc(mouseImage);*/

	/*--------------------------gl map test 1
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(400, 100);
	glutCreateWindow(argv[0]);
	initM1();
	glutDisplayFunc(displayM1);
	glutReshapeFunc(reshapeM1);
	glutKeyboardFunc(keyboardM1);*/

	/*--------------------------gl mipmap test
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(400, 100);
	glutCreateWindow(argv[0]);
	initMM();
	glutDisplayFunc(displayMM);
	glutReshapeFunc(reshapeMM);*/

	/*--------------------------gl map texture bind 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(400, 100);
	glutCreateWindow(argv[0]);
	initTB();
	glutDisplayFunc(displayTB);
	glutReshapeFunc(reshapeM1);*/

	/*--------------------------gl tex gen
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(256, 256);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	initTG();
	glutDisplayFunc(displayTG);
	glutReshapeFunc(reshapeTG);
	glutKeyboardFunc(keyboardTG); */

	/*--------------------------gl stencil
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 200);
	glutCreateWindow(argv[0]);
	initSTENCIL();
	glutDisplayFunc(displaySTENCIL);
	glutReshapeFunc(reshapeSTENCIL);

	glutMainLoop();*/

	/*--------------------------gl my_stencil_test 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 200);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(displayMySDT);*/

	/*--------------------------gl my_stencil_test*/
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(displayTess);
	glutReshapeFunc(reshapeTess);

	glutMainLoop();

}
