#include "cprocessing.h"
#include "carlevel.h"
#include "utils.h"
#include <stdio.h>
#include <mainmenu.h>

int swidth, sheight;
Rect Start, End;
CP_Color red;

void Main_Menu_Init()
{
	swidth = 800;
	sheight = 600;
	CP_System_SetWindowSize(swidth, sheight);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	
}


void Main_Menu_Update()
{

	CP_Graphics_ClearBackground(CP_Color_Create(100, 100, 100, 255));
	int rectW = 100, rectH = 50, rectWOff = rectW / 2, rectHOff = rectH / 2;
	int centeroffset = 100;
	//Y ++ = down
	//X ++ = right
	////Unecessary #Start
	//CP_Settings_Save();
	//CP_Settings_StrokeWeight(1.0f);
	//CP_Graphics_DrawLine(0, sheight / 2, swidth, sheight / 2);
	//for (int i = 0; i <= 20; i++) {
	//	CP_Graphics_DrawLine(swidth / 2 - rectWOff + i*5 , 0, swidth / 2 - rectWOff + i*5, sheight);
	//}
	////Unecessary #End

	//CP_Settings_StrokeWeight(1.0f);
	//CP_Settings_Restore();
	CP_Settings_Fill(CP_Color_Create(255, 100, 100, 255));
	
	Start = (Rect){ .w = rectW, .h = rectH, { swidth / 2, sheight / 2}, "Start" };
	End   = (Rect){ .w = rectW, .h = rectH, {swidth / 2, sheight / 2 + centeroffset}, "End" };

	CP_Graphics_DrawRect(Start.coor.x, Start.coor.y, Start.w, Start.h);
	CP_Graphics_DrawRect(End.coor.x, End.coor.y, End.w, End.h);
	
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(30);
	CP_Font_DrawText(&*Start.name, Start.coor.x, Start.coor.y);
	CP_Font_DrawText(&*End.name, End.coor.x, End.coor.y);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		if (IsAreaClicked(Start.coor.x - rectWOff, Start.coor.y - rectHOff, Start.w, Start.h, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 0) {
			CP_Engine_SetNextGameState(Car_Level_Init, Car_Level_Update, Car_Leve_Exit);
			printf("Legoo Car\n");
		}
		if (IsAreaClicked(End.coor.x - rectWOff, End.coor.y - rectHOff, End.w, End.h, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 0) {
			CP_Engine_Terminate();
		}
	}

	
	if (CP_Input_KeyDown(KEY_C)) {
		CP_Engine_SetNextGameState(Car_Level_Init, Car_Level_Update, Car_Leve_Exit);
		printf("Legoo Car\n");
		//CP_Engine_Run();
	}
	if (CP_Input_KeyDown(KEY_K)) {
		CP_Engine_Terminate();
	}
}

void Main_Menu_Exit()
{
	
}



