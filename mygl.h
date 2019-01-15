#ifndef _MYGL_H_
#define _MYGL_H_

#include <conio.h>
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


#include "definitions.h"
/*
QUANTIDADE DE PIXELS = WIDTH * HEIGHT;
-ALGORITMO IMEDIATO
-ALGORITMO DE BRESENHAM

*/
typedef struct Color{
    unsigned int r=255;
    unsigned int g=255;
    unsigned int b=255;
    unsigned int a=255;
} Color;


typedef struct Point{
    int x;
    int y;

    struct Color color;

} Point;

void interpolaCor(Point arrayPoint[], int N);
void drawLine(Point pointA,  Point pointB);
void putPixel(Point point);
unsigned int offset(Point point);
void algoritmoImediato(Point ponto1, Point ponto2);
void drawTriangle(Point ponto1, Point ponto2, Point ponto3);
/******************************************************/
/*******  RETORNA A POSICAO NO COLOR_BUFFER DE  *******/
/*******        ACORDO COM AS COORDENADAS       *******/
/******************************************************/

unsigned int offset(Point point){
    return point.x * 4 + point.y * IMAGE_WIDTH * 4;
}


void putPixel(Point point){	// coloca um ponto na tela
	FBptr[ offset(point) + 0 ] = point.color.r;//A PRIMEIRA POSIÇÃO DO COLORBUFFER RECEBE INTENSIDADE DE COR VERMELHA
	FBptr[ offset(point) + 1 ] = point.color.g;//A SEGUNDA  POSIÇÃO DO COLORBUFFER RECEBE INTENSIDADE DE COR VERDE
	FBptr[ offset(point) + 2 ] = point.color.b;//A TERCEIRA POSIÇÃO DO COLORBUFFER RECEBE INTENSIDADE DE COR AZUL
	FBptr[ offset(point) + 3 ] = point.color.a;//A QUARTA   POSIÇÃO DO COLORBUFFER RECEBE A TRANSPARÊNCIA QUE SERÁ NULA
}


/* ----------------ALGORITMO IMEDIADO--------------------------
	y = m * x + b;
	m = (y2 - y1)/(x2 - x1);
	b = y1 - m * x1;
	
	Fazendo X variar entre X1 e X2 por incrementos de uma unidade, o valor de Y
	calculado será um valor real que deve ser arredondado para o inteiro mais próximo
	dessa forma -->  point(x0,round(m*x+b);
	
*/
void algoritmoImediato(Point ponto1, Point ponto2){
	float m , b, dx, dy;
	//Evita coordenadas negativas
	if(ponto1.x < 0){ponto1.x *= -1;}
	if(ponto1.y < 0){ponto1.y *= -1;}
	if(ponto2.x < 0){ponto2.x *= -1;}
	if(ponto2.y < 0){ponto2.y *= -1;}
	
	if((ponto1.x == ponto2.x) && (ponto1.y == ponto2.y)){ //SE SÃO O MESMO PONTO É SÓ PLOTAR
		printf("Pontos iguais\n");
		putPixel(ponto1);
		putPixel(ponto2);
		return;
	}
	if(ponto2.x < ponto1.x){
		printf("Entrou na recursividade\n");
		algoritmoImediato(ponto2,ponto1);
		return;
	}
	
	
	dx = ponto2.x - ponto1.x;
	dy = ponto2.y - ponto1.y;
	
	if(dx == 0){// reta vertical
		printf("Reta vertical\n");
		if(ponto1.y < ponto2.y){            
			while (ponto1.y <= ponto2.y){
        		putPixel(ponto1);           
            	ponto1.y++;                  
        	}
		}else{
			while (ponto1.y >= ponto2.y){
        		putPixel(ponto1);          
            	ponto1.y--;                 
        	}
		}
		
		return;
	}
	if(dy == 0){ //reta horizontal
		printf("Reta horizontal\n");	
		if(ponto1.x < ponto2.x){            // SE Y1 < Y2, DESENHA DE Y1 ATÉ Y2
			while (ponto1.x <= ponto2.x){
        		putPixel(ponto1);           // O X VAI CONTINUAR O MESMO, JÁ QUE X1 = X2
            	ponto1.x++;                 // O Y VAI AUMENTAR 
        	}
        	return;
		}
		if(ponto1.x > ponto2.x){
			while (ponto1.x >= ponto2.x){
        		putPixel(ponto1);           // O X VAI CONTINUAR O MESMO, JÁ QUE X1 = X2
            	ponto1.x--;                 // O Y VAI AUMENTAR 
        	}
		}
		
		return;
		
		
	}
	if(dx > dy){  // reta crescente no plano cartesiano
		printf("Reta decrescente\n");
        m = dy / dx;
        b = ponto1.y - ( m * ponto1.x );
        while (ponto1.x < ponto2.x){
            putPixel(ponto1);
			ponto1.x++;
            ponto1.y = round( ( m * ponto1.x ) + b );
    	}
    }
	else{    // reta decrescente no plano cartesiano
		printf("Reta crescente\n");
		m = dx / dy;
        b = ponto1.x - ( m * ponto1.y );
		while (ponto1.y < ponto2.y){
			putPixel(ponto1);
			ponto1.y++;
            ponto1.x = round( (m * ponto1.y) + b ) ;
			
        }
    }

}

// Bresenham ou Ponto Médio
void drawLine(Point pointA, Point pointB){
	float dy, dx, p, xf;
	dx = pointB.x - pointA.x;
	dy = pointB.y - pointA.y;
	int N=0;
	Point arrayPoint[512];
	if (pointA.x > pointB.x){
		printf("Entrou na recursividade\n");
		/*CASO NÃO USE A FUNÇÃO DE INTERPOLAR COR, ESSES 3 COMANDOS ABAIXO DEVEM SER ATIVADOS*/
		//Color corAux = pointA.color;
		//pointA.color = pointB.color;
		//pointB.color = corAux;
		drawLine(pointB, pointA);
		return;
	}
	
	if(abs(dx) >= abs(dy)){  //Reta decrescente
		if(dy > 0){ 
			int d_new = 2*dy - dx;  // Valor de decisão inicial
        	int inc_E = 2*dy;	// Valor incremental caso vá para o leste
        	int inc_NE = 2*dy - 2*dx;// Valor incremental caso vá para o nordeste

        	while(pointA.x <= pointB.x){
            	//putPixel(pointA);		// Coloca o primeiro pixel
            	arrayPoint[N] = pointA;
            	pointA.x++;
            	N++;
				if (d_new < 0){
					d_new += inc_E;
				}
            	else{
                	d_new += inc_NE;
                	pointA.y ++;
            	}
            	
        	}
    	}else{ //PRIMEIRO OCTANTE
			int d_new = 2 * dy + dx;
        	int inc_E = 2 * dy;
        	int inc_NE = 2 * dy + 2 * dx;
			while(pointA.x <= pointB.x){
				//putPixel(pointA);
				arrayPoint[N] = pointA;
            	pointA.x++;
            	N++;
				if (d_new > 0){
					d_new += inc_E;
				}else{
                	d_new += inc_NE;
                	pointA.y--;
				}
				
			}
    	}	
	}
	else{		// Reta crescente
		if(dy >= 0){
        	int d_new = dy - 2* dx;
        	int inc_E = -2*dx;
        	int inc_NE = 2*dy - 2*dx;
			while(pointA.y <= pointB.y){
				//putPixel(pointA);
				arrayPoint[N] = pointA;
            	pointA.y++;
            	N++;
				if (d_new > 0){
					d_new += inc_E;
				}else{
                	d_new += inc_NE;
                	pointA.x++;
            	}
            	
        	}

    	}else{
			int d_new = dy + 2*dx;
        	int inc_E = 2*dx;
        	int inc_NE = 2*dy + 2*dx;
        	while(pointA.y >= pointB.y){
            	//putPixel(pointA);
            	arrayPoint[N] = pointA;
            	pointA.y--;
            	N++;
            	if (d_new < 0){
            		d_new += inc_E;
            	}else{
                	d_new += inc_NE;
                	pointA.x ++;
            	}
				
        	}
		}
	}
	
	arrayPoint[N-1].color = pointB.color; //IMPORTANTÍSSIMO 
	interpolaCor(arrayPoint, N);
}
void interpolaCor(Point arrayPoint[], int N){
	int i;
	float aux;
	//float distanciaTotal, distanciaParcial, p;
	//distanciaTotal = sqrt( (arrayPoint[N-1].x - arrayPoint[0].x)*(arrayPoint[N-1].x - arrayPoint[0].x) + (arrayPoint[N-1].y - arrayPoint[0].y)*(arrayPoint[N-1].y - arrayPoint[0].y));
	
	for(i=0; i <= N-1; i++){
		aux = (float)i/(N - 1);
		//distanciaParcial = sqrt( (arrayPoint[N-1].x - arrayPoint[i].x)*(arrayPoint[N-1].x - arrayPoint[i].x) + (arrayPoint[N-1].y - arrayPoint[i].y)*(arrayPoint[N-1].y - arrayPoint[i].y));
		//p = distanciaParcial / distanciaTotal;
		//arrayPoint[i].color.r =  arrayPoint[0].color.r * p + (1-p) * arrayPoint[N-1].color.r ; 
		//arrayPoint[i].color.g =  arrayPoint[0].color.g * p + (1-p) * arrayPoint[N-1].color.g ;
		//arrayPoint[i].color.b =  arrayPoint[0].color.b * p + (1-p) * arrayPoint[N-1].color.b ;
		//arrayPoint[i].color.a =  arrayPoint[0].color.a * p + (1-p) * arrayPoint[N-1].color.a ;
		
		arrayPoint[i].color.r =  arrayPoint[0].color.r * (1-aux) + aux * arrayPoint[N-1].color.r ; 
		arrayPoint[i].color.g =  arrayPoint[0].color.g * (1-aux) + aux * arrayPoint[N-1].color.g ;
		arrayPoint[i].color.b =  arrayPoint[0].color.b * (1-aux) + aux * arrayPoint[N-1].color.b ;
		arrayPoint[i].color.a =  arrayPoint[0].color.a * (1-aux) + aux * arrayPoint[N-1].color.a ;
			
		putPixel(arrayPoint[i]);
	}
	
	
	
}

void drawTriangle(Point ponto1, Point ponto2, Point ponto3){
	//algoritmoImediato(ponto1, ponto2);
	//algoritmoImediato(ponto2, ponto3);
	//algoritmoImediato(ponto3, ponto1);
	drawLine(ponto1, ponto2);
	drawLine(ponto2, ponto3);
	drawLine(ponto3, ponto1);
}

#endif // _MYGL_H_

