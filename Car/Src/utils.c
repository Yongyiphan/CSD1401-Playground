#include "cprocessing.h"
#include <mainmenu.h>
#include <math.h>

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	//return 0 if true, else false;
	int xLeftLimit = area_center_x, xRightLimit = area_center_x + area_width;
	int yTopLimit = area_center_y, yBtmLimit = area_center_y + area_height;

	if (xLeftLimit < click_x && click_x < xRightLimit && yTopLimit < click_y && click_y < yBtmLimit ) {
		return 0;
	}
	return 1;
}



int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	// TODO
	//return 0 if true, else 1;
	//circle origin point (x, y) = (circle_center_x, circle_center_y)
	//get distance from origin to mouse
	double dist = pow(click_x - circle_center_x, 2) + pow(click_y - circle_center_y, 2);
	if (dist <= pow(diameter / 2,2) ) {
		return 0;
	}
	return 1;
}

CP_Vector AngleToVector(float radian_angle)
{
	double rad = fmod(radian_angle, 6.28);
	double x = cosf(rad), y = sinf(rad);
	return  CP_Vector_Set(x, y);
	
	// TODO 
    //CP_Vector ret;
    //return ret;
}

Car CreateCar(Circle circle, char *startPoint, CP_Color circleC, CP_Color triC) {
	Coor P1, P2, P3;
	double angle = 2.25;
	double tRad = 6.28 , lRad, rRad, modMax = 6.28;
	//btm of triangle
	double btm = circle.rad * 4 / 5;
	if (strcmp(startPoint, "Left") == 0) {
		tRad += 0;
		lRad = tRad + angle;
		rRad = tRad - angle;
	}
	if (strcmp(startPoint, "Up") == 0) {
		tRad += 1.57;
		lRad = tRad + angle;
		rRad = tRad - angle;
	}
	else if (strcmp(startPoint, "Right") == 0) {
		tRad += 3.14;
		lRad = tRad + angle;
		rRad = tRad - angle;
	}
	else if (strcmp(startPoint, "Down") == 0) {
		tRad += 4.71;
		lRad = tRad + angle;
		rRad = tRad - angle;
	}
	double a = fmod(tRad, modMax);
	double b = fmod(lRad, modMax);
	double c = fmod(rRad, modMax);
	P1 = (Coor){ abs(circle.rad * cosf(a) + circle.coor.x), abs(circle.rad * sinf(a) - circle.coor.y) };
	P2 = (Coor){ abs(btm * cosf(b) + circle.coor.x), abs(btm * sinf(b) - circle.coor.y) };
	P3 = (Coor){ abs(btm * cosf(c) + circle.coor.x), abs(btm * sinf(c) - circle.coor.y) };
	Triangle T = { P1, P2, P3, tRad, angle, btm };
	Car obj = { circle, T , circleC, triC};
	
	return obj;
}
void DrawCar(Car*car) {
	CP_Settings_Fill(car->circleColor);
	CP_Graphics_DrawCircle( car->circle.coor.x, car->circle.coor.y, car->circle.rad *2);
	CP_Settings_Fill(car->triColor);
	CP_Graphics_DrawTriangle(car->triangle.P1.x, car->triangle.P1.y, car->triangle.P2.x, car->triangle.P2.y, car->triangle.P3.x, car->triangle.P3.y);
}

void UpdateCarRotation(Car* car) {

	double a = fmod(car->triangle.rot, 6.28);
	double b = fmod(car->triangle.rot + car->triangle.angle, 6.28);
	double c = fmod(car->triangle.rot - car->triangle.angle, 6.28);

	car->triangle.P1.x = abs(car->circle.rad * cosf(a) + car->circle.coor.x);
	car->triangle.P1.y = abs(car->circle.rad * sinf(a) - car->circle.coor.y);
	
	car->triangle.P2.x = abs(car->triangle.btm * cosf(b) + car->circle.coor.x);
	car->triangle.P2.y = abs(car->triangle.btm * sinf(b) - car->circle.coor.y);

	car->triangle.P3.x = abs(car->triangle.btm * cosf(c) + car->circle.coor.x);
	car->triangle.P3.y = abs(car->triangle.btm * sinf(c) - car->circle.coor.y);
	
}

int CarSelection(Car* CarArr[], int totalCars, float Mouse_Input_x, float Mouse_Input_y) {
	for (int i = 0; i < totalCars; i++) {
		Car cCar = *CarArr[i];
		if (IsCircleClicked(cCar.circle.coor.x, cCar.circle.coor.y, cCar.circle.rad * 2, Mouse_Input_x, Mouse_Input_y) == 0) {
			return i;
		}
	}
	return totalCars;

}


