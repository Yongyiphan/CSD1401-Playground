#pragma once
#ifndef HEADERFILE_H
#define HEADERFILE_H


typedef struct Coordinates{
	float x;
	float y;
}Coor;


typedef struct ReectObj{
	int w;
	int h;
	Coor coor;
}Rect;

typedef struct CircleObj {
	int rad;
	Coor coor;
}Circle;

typedef struct Triangle {
	//point 1, 2, 3 to draw triangle
	Coor P1;
	Coor P2;
	Coor P3;
	//rotation in % 6.28.
	double rot;
	double angle;
	//btm length of triangle
	double btm;
}Triangle;

typedef struct Car {
	Circle circle;
	Triangle triangle;
	CP_Color circleColor;
	CP_Color triColor;
}Car;


void Main_Menu_Init(void);
void Main_Menu_Update(void);
void Main_Menu_Exit(void);

#endif // 


