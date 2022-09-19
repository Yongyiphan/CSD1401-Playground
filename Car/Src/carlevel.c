#include "cprocessing.h"
#include "mainmenu.h"
#include <utils.h>
#include <stdio.h>


int cRad = 150, lineGap = 10, a = 255, currentCar, totalCars;
double rotationSpeed = 0.1, accelerationSpeed = 10;
//init starting x,y for all three circle /cars
int swidth, sheight;
Car one, two, three;
Car* CarArr[3];

void Car_Level_Init()
{
	printf("Im in car\n");
	CP_System_SetWindowSize(1080, 800);
	swidth = CP_System_GetWindowWidth();
	sheight = CP_System_GetWindowHeight();
	//Init car structs
	CP_Color triC = CP_Color_Create(150, 150, 150, a);
	CP_Settings_EllipseMode(CP_POSITION_CENTER);
	currentCar = 1;

	one = CreateCar((Circle) { cRad, swidth / 2, sheight / 2 }, "Up", CP_Color_Create(200, 0, 0, a), triC);
	two = CreateCar((Circle) { cRad, swidth / 4, sheight / 4 }, "Down", CP_Color_Create(0, 200, 0, a), triC);
	three = CreateCar((Circle) { cRad, swidth * 3 / 4, sheight / 4 }, "Left", CP_Color_Create(0, 0, 200, a), triC);


	CarArr[0] = &one;
	CarArr[1] = &two;
	CarArr[2] = &three;
	totalCars = 3;
}

void Car_Level_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(150, 150, 150, 255));
	totalCars = (sizeof(CarArr) / sizeof(&CarArr[0]));
	//Unecessary #Start
	CP_Settings_Save();
	CP_Settings_StrokeWeight(1.0f);
	for (int i = 0; i <= swidth / lineGap; i++) {
		//Draw X lines
		CP_Graphics_DrawLine(i * lineGap, 0, i * lineGap, sheight);
	}
	for (int i = 0; i <= sheight / lineGap; i++) {
		//Draw Y lines
		CP_Graphics_DrawLine(0, i * lineGap, swidth, i * lineGap);
	}
	//Unecessary #End

	//Circle default origin = center;
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		currentCar = CarSelection(&CarArr,totalCars, CP_Input_GetMouseX(), CP_Input_GetMouseY());
	}
	if (currentCar < totalCars) {
		Car* cCar = &*CarArr[currentCar];
		CP_Settings_StrokeWeight(2.0f);
		if (CP_Input_KeyDown(KEY_D)) {
			cCar->triangle.rot -= rotationSpeed;
		}
		else if (CP_Input_KeyDown(KEY_A)) {
			cCar->triangle.rot += rotationSpeed;
		}

		else if (CP_Input_KeyDown(KEY_W)) {
			CP_Vector vec = AngleToVector(cCar->triangle.rot);
			float nx = cCar->circle.coor.x + (vec.x * accelerationSpeed);
			float ny = cCar->circle.coor.y - (vec.y * accelerationSpeed);
			if (nx + cCar->circle.rad <= swidth && nx - cCar->circle.rad >= 0 && ny + cCar->circle.rad <= sheight && ny - cCar->circle.rad >= 0) {
				cCar->circle.coor.x += vec.x * accelerationSpeed;
				cCar->circle.coor.y -= vec.y * accelerationSpeed;
			}

		}
		else if (CP_Input_KeyDown(KEY_S)) {
			CP_Vector vec = AngleToVector(cCar->triangle.rot);
			float nx = cCar->circle.coor.x - (vec.x * accelerationSpeed);
			float ny = cCar->circle.coor.y + (vec.y * accelerationSpeed);
			if (nx + cCar->circle.rad <= swidth && nx - cCar->circle.rad >= 0 && ny + cCar->circle.rad <= sheight && ny - cCar->circle.rad >= 0) {
				cCar->circle.coor.x -= vec.x * accelerationSpeed;
				cCar->circle.coor.y += vec.y * accelerationSpeed;
				}
			}

		UpdateCarRotation(cCar);
	}
	for (int i = 0; i < totalCars; i++) {
		DrawCar(&*CarArr[i]);
	}


	if (CP_Input_KeyDown(KEY_M)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		printf("Bye bye car\n");
	}

}

void Car_Leve_Exit()
{
}

