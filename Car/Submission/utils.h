#pragma once
#include <mainmenu.h>


int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
union CP_Vector AngleToVector(float radian_angle);
Car CreateCar(Circle, char[]);
void DrawCar(Car* car);
void UpdateCarRotation(Car* car);
int CarSelection(Car* CarArr[],int, float, float);
