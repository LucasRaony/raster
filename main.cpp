#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include <stddef.h>
#include <conio.h>
#include "main.h"
using namespace std;

/*
REFERÊNCIAS
http://www.univasf.edu.br/~jorge.cavalcanti/comput_graf04_prim_graficas2.pdf
https://www.codeproject.com/Articles/82091/OpenGL-Color-Interpolation
*/



//-----------------------------------------------------------------------------
void MyGlDraw(void){
	
	Point ponto1, ponto2, ponto3, ponto4;
	ponto1.color.r = 255; ponto1.color.g = 0; ponto1.color.b = 0;// ponto1 é vermelho
	ponto2.color.r = 0; ponto2.color.g = 255; ponto2.color.b = 0;// ponto2 é verde
	ponto3.color.r = 0; ponto3.color.g = 0; ponto3.color.b = 255;// ponto3 é azul
	ponto4.color.r = 255; ponto4.color.g = 255; ponto4.color.b = 255;
	
	ponto1.x = 256;
	ponto1.y = 0;
	ponto2.x = 512;
	ponto2.y = 256;
	ponto3.x = 0;
	ponto3.y = 256;
	ponto4.x = 256;
	ponto4.y = 270;
	
	//putPixel(ponto1);
	//putPixel(ponto2);
	//putPixel(ponto3);
	//putPixel(ponto4);
	//algoritmoImediato(ponto1,ponto2);
	//drawLine(ponto1, ponto2);
	drawTriangle(ponto1, ponto2, ponto3);
	
	


}

//-----------------------------------------------------------------------------
int main(int argc, char **argv){
	
	
	
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

