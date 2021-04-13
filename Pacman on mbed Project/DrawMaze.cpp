#include "uLCD_4DGL.h"
#include "BuzzyGraphics.h"
#include "Buzzy.h"


extern uLCD_4DGL guLCD;
extern char gDynaMaze[MAZE_NUM_ROW][MAZE_NUM_COL]; 
extern Buzzy gBuzzy;
/////////////////////////////////////////////////////////////////////
// The maze is a scaled down version of the LCD display
// Each element in the maze is really a 3x3 segment of the LCD
// This must be taken into account when drawing the maze on the LCD


// Draw a wall tile when 
void DrawMazeWall(int const &x1, int const &y1)                             // draw maze function!!
{
    int ii = 3*x1+1;
    int jj = 3*y1+1;
    guLCD.filled_rectangle(ii-1, jj-1, ii+1, jj+1, _BLUE);
}
/*
    ECE 2036 Spring 2019 Lab 4
    David Pipes
    Buzzy game on mBed kit
*/
/*
//////////////////////////////////////////////////////////////////////
Use the following #defines to determine which icon to draw in the LCD
#define BLUE_SQUARE 1
#define HONEYDROP_SQUARE 2
#define PWRUP_SQUARE 3
#define GHOST_ICON 4
#define BUZZY_ICON 5
#define TRAP_LINE 6

When drawing the ghosts draw one of each color
*/
void DrawMaze()
{
    int ghostcounter(0);
    
    for (int ii = 0 ; ii < MAZE_NUM_ROW ; ii++)
    {
        for (int jj = 0 ; jj < MAZE_NUM_COL ; jj++)
        {
            gDynaMaze[ii][jj] = gCnstMaze[ii][jj];
            char temp = gCnstMaze[ii][jj];
            switch(temp)
            {
                case 0:
                break;
                
                case 1:
                DrawMazeWall(ii,jj);
                break;
                
                case 2:// honeydrop square 
                guLCD.BLIT((3*(ii+1)-4),(3*(jj+1)-4),3,3,*HoneyDropIcon);
                break;
                
                case 3:// PowerUpIcon[9][9]
                guLCD.BLIT((3*(ii+1)-6),(3*(jj+1)-6),9,9,*PowerUpIcon);
                break;
                
                case 4:// ghost icon
                if (ghostcounter == 0){
                    guLCD.BLIT((3*(ii+1)-6),(3*(jj+1)-6),9,9,*VioletGhost[1]);
                    ++ghostcounter;
                }
                else if (ghostcounter == 1){
                    guLCD.BLIT((3*(ii+1)-6),(3*(jj+1)-6),9,9,*BlueGhost[1]);
                    ++ghostcounter;
                }
                else if (ghostcounter == 2) {
                    guLCD.BLIT((3*(ii+1)-6),(3*(jj+1)-6),9,9,*PinkGhost[1]);
                    ++ghostcounter;
                }
                else if (ghostcounter == 3){
                    guLCD.BLIT((3*(ii+1)-6),(3*(jj+1)-6),9,9,*GreenGhost[1]);
                    ++ghostcounter;
                }
                break;
                
                case 5:
                guLCD.BLIT((3*(ii+1)-6),(3*(jj+1)-6),9,9,*BuzzyIcon[1]);
                //gBuzzy.DrawInNewLocation(ii,jj);
                break;
                
                case 6:
                //guLCD.BLIT((3*(ii+1)-6),(3*(jj+1)-6),9,9,*TrapLine);
                break;
                
                default:
                break;
                
            }
            
            
        }
    }
}