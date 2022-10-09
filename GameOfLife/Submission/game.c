#include <stdio.h>
#include "cprocessing.h"

#define GOL_GRID_COLS 30
#define GOL_GRID_ROWS 30
#define GOL_GRID_BUFFERS 2
#define CELL_LENGTH 15

#define GOL_ALIVE 1
#define GOL_DEAD 0

#define TRUE 1
#define FALSE 0



int gIsPaused;
int gGrids[GOL_GRID_BUFFERS][GOL_GRID_ROWS][GOL_GRID_COLS];

//width and height of each cell
CP_Color DeadColor, AliveColor;
//display grid, reference grid
int rGrid = 0, dGrid = 1;
/* Feel free to declare your own variables here */


void game_init(void)
{  
    CP_System_SetWindowSize(CELL_LENGTH * GOL_GRID_ROWS, CELL_LENGTH * GOL_GRID_COLS);
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
    //CP_Graphics_ClearBackground(DeadColor);
    if (CP_Input_KeyTriggered(KEY_SPACE)) {
        gIsPaused = gIsPaused == FALSE ? TRUE : FALSE;
    }
    if (gIsPaused == TRUE) {
        //allow input
        if (CP_Input_MouseClicked()) {
            int row = CP_Input_GetMouseX() / CELL_LENGTH;
            int col = CP_Input_GetMouseY() / CELL_LENGTH;
            gGrids[dGrid][row][col] = gGrids[dGrid][row][col] == GOL_ALIVE ? GOL_DEAD : GOL_ALIVE;
        }
    }
    else {
        //Draw Grid;
        //using rgrid, check rules
        //modify dgrid. swap rgrid, dgrid values
        //Any live cell with fewer than two live neighbors dies (emulates underpopulation).
        //Any live cell with two or three live neighbors lives on.
        //Any live cell with more than three live neighbors dies (emulates overpopulation).
        //Any dead cell with exactly three live neighbors becomes a live cell (emulates reproduction).
        for (int r = 0; r < GOL_GRID_ROWS; r++) {
            for (int c = 0; c < GOL_GRID_COLS; c++) {
                //check for neighbours
                //if at corners
                //-> corners == if r == 0, r == ROWs, c == 0 
                //int left, right, up, down;
                int count = 0;
                for (int i = r - 1; i <= r + 1; i++) {
                    for (int j = c - 1; j <= c + 1; j++) {
                        if ((i == r && j == c) || (i < 0 || j < 0) || (i >= GOL_GRID_ROWS || j >= GOL_GRID_COLS)) {
                            continue;
                        }
                        if (gGrids[rGrid][i][j] == GOL_ALIVE) {
                            count++;
                        }
                    }
                }
                if (gGrids[rGrid][r][c] == GOL_ALIVE) {
                    if (count < 2) {
                        gGrids[dGrid][r][c] = GOL_DEAD;
                    }
                    else if (count == 2 || count == 3) {
                        gGrids[dGrid][r][c] = GOL_ALIVE;
                    }
                    else if (count > 3) {
                        gGrids[dGrid][r][c] = GOL_DEAD;
                    }
                }
                else if (count == 3) {
                    gGrids[dGrid][r][c] = GOL_ALIVE;
                }
            }
        }
    }
    CP_Settings_StrokeWeight(0.5f);
    for (int r = 0; r < GOL_GRID_ROWS; r++) {
        for (int c = 0; c < GOL_GRID_COLS; c++) {
            CP_Settings_Fill(DeadColor);
            if (gGrids[dGrid][r][c] == GOL_ALIVE) {
                CP_Settings_Fill(AliveColor);
            }
            gGrids[rGrid][r][c] = gGrids[dGrid][r][c];
            CP_Graphics_DrawRect(r * CELL_LENGTH, c * CELL_LENGTH, CELL_LENGTH, CELL_LENGTH);
        }
    }
    rGrid = rGrid == 1 ? 0 : 1;
    dGrid = dGrid == 1 ? 0 : 1;

}

void game_exit(void)
{
}
