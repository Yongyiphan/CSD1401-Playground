#include <stdio.h>
#include "cprocessing.h"
#include <utils.h>


#define GOL_GRID_COLS 30
#define GOL_GRID_ROWS 30
#define GOL_GRID_BUFFERS 2

#define GOL_ALIVE 1
#define GOL_DEAD 0

#define TRUE 1
#define FALSE 0



int gIsPaused;
int gGrids[GOL_GRID_BUFFERS][GOL_GRID_ROWS][GOL_GRID_COLS];

//width and height of each cell
int windowW, windowH, cellW, cellH;
CP_Color DeadColor, AliveColor;

/* Feel free to declare your own variables here */


void game_init(void)
{   
    DeadColor = CP_Color_Create(100, 100, 100, 255);
    AliveColor = CP_Color_Create(200, 200, 200, 255);
    /* Set every grids' cells as 'dead' */
    for (int row = 0; row < GOL_GRID_ROWS; ++row) {
        for (int col = 0; col < GOL_GRID_COLS; ++col) {
            for (int i = 0; i < GOL_GRID_BUFFERS; ++i) {
                gGrids[i][row][col] = GOL_DEAD;
            }
        }
    }

    windowW = CP_System_GetWindowWidth();
    windowH = CP_System_GetWindowHeight();
    cellW = windowW / GOL_GRID_COLS;
    cellH = windowH / GOL_GRID_ROWS;


    /*********************************************************
    *  Let's start with gGrids[0] as the 'reference grid'
    *  and gGrids[1] as the 'displaying grid'.
    *
    *  We initialize gGrids[0] with a simple 'glider'.
    *********************************************************/

    gGrids[0][1][2] = GOL_ALIVE;
    gGrids[0][2][3] = GOL_ALIVE;
    gGrids[0][3][1] = GOL_ALIVE;
    gGrids[0][3][2] = GOL_ALIVE;
    gGrids[0][3][3] = GOL_ALIVE;

    /* We start unpaused */
    gIsPaused = FALSE;

    /* Initialization of your other variables here */
}

void game_update(void)
{
    //Cal Cells
    //Draw Grid;
    int cgrid = 0;
    for (int r = 0; r < GOL_GRID_ROWS; r++) {
        for (int c = 0; c < GOL_GRID_COLS; c++) {
            if (gGrids[cgrid][r][c] == GOL_DEAD) {
                CP_Settings_Fill(DeadColor);
            }
            else if (gGrids[cgrid][r][c] == GOL_ALIVE) {
                CP_Settings_Fill(AliveColor);
            }
            
            CP_Graphics_DrawRect(r * cellW, c * cellH, cellW, cellH);
        }
    }
}

void game_exit(void)
{
}
