/*
    ECE 2036 Spring 2019 Lab 4
    David Pipes
    Buzzy game on mBed kit
*/
#include "Buzzy.h"
#include "Ghosts.h"
#include "BuzzyGraphics.h"
#include "uLCD_4DGL.h"
#include "Speaker.h"



extern char gDynaMaze[MAZE_NUM_ROW][MAZE_NUM_COL]; 
extern Ghosts gGhosts[NUM_GHOSTS];
extern Buzzy gBuzzy;
extern uLCD_4DGL guLCD;
extern Speaker gSpeakerOut;

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// Constructor
Buzzy::Buzzy(enDIRECTIONS inDir, unsigned int inRow, unsigned int inCol):
Sprite(inDir, inRow, inCol)
{
    
}    
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void Buzzy::Move()
{
    gSpeakerOut.SwitchSound(Speaker::SIREN);
    switch(m_DesiredDirection)
    {
        case NO_DIR:
        gSpeakerOut.SwitchSound(Speaker::SIREN);
        break;
        
        case UP_DIR:
        if ( IsMoveAllowed(m_RowPos + 2 , m_ColPos) == true)
        {
            DrawInNewLocation(m_RowPos + 1 , m_ColPos);
            m_CurrentDirection = m_DesiredDirection;   
        }
        break;
        
        case DOWN_DIR:
        if ( IsMoveAllowed(m_RowPos - 2 , m_ColPos) == true)
        {
            DrawInNewLocation(m_RowPos - 1 , m_ColPos);
            m_CurrentDirection = m_DesiredDirection;

        }
        break;
        
        case LEFT_DIR:
        if ( IsMoveAllowed(m_RowPos, m_ColPos - 2) == true)
        {
            DrawInNewLocation(m_RowPos, m_ColPos - 1);
            m_CurrentDirection = m_DesiredDirection;
        }
        break;
        
        case RIGHT_DIR:
        if ( IsMoveAllowed(m_RowPos, m_ColPos + 2) == true)
        {
            DrawInNewLocation(m_RowPos, m_ColPos + 1);
            m_CurrentDirection = m_DesiredDirection;
        }
        break;
        
        default:
        break;
    }
    //if (m_CurrentDirection)
    //{
        switch(m_CurrentDirection)
        {
            case NO_DIR:
            gSpeakerOut.SwitchSound(Speaker::SIREN);
            break;
        
            case UP_DIR:
            if ( IsMoveAllowed(m_RowPos + 2 , m_ColPos) == true)
            {
                DrawInNewLocation(m_RowPos + 1 , m_ColPos); 
            }
            break;
        
            case DOWN_DIR:
            if ( IsMoveAllowed(m_RowPos - 2 , m_ColPos) == true)
            {
                DrawInNewLocation(m_RowPos - 1 , m_ColPos);
            }
            break;
        
            case LEFT_DIR:
            if ( IsMoveAllowed(m_RowPos, m_ColPos - 2) == true)
            {
                DrawInNewLocation(m_RowPos, m_ColPos - 1);
            }
            break;
        
            case RIGHT_DIR:
            if ( IsMoveAllowed(m_RowPos, m_ColPos + 2) == true)
            {
                DrawInNewLocation(m_RowPos, m_ColPos + 1);
            }
            break;
        
            default:
            gSpeakerOut.SwitchSound(Speaker::BEGIN);
            break;
        }
    //}
 
 
    // If failed to move in desired directione the try to move Buzzy in old direction

       
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void Buzzy::DrawInNewLocation(const int &nRow,const int &nCol)
{
    int x1, y1;
    
    // Test if we hit a honeydrop or fruit or ghost
    if (gDynaMaze[nRow][nCol] == 2)
    {
        //honeydrop condition
        
        gDynaMaze[nRow][nCol] = 0;
        gSpeakerOut.SwitchSound(Speaker::CHOMP);
    }
    
    else if (gDynaMaze[nRow][nCol] == 3)
    {
        //power up condition
        gSpeakerOut.SwitchSound(Speaker::EAT_FRUIT);
        gDynaMaze[nRow][nCol] = 0;
    }
    
    else if (gDynaMaze[nRow][nCol] == 4)
    {
        //ghost condition
        gSpeakerOut.SwitchSound(Speaker::EAT_GHOST);
        gDynaMaze[nRow][nCol] = 0;
    }
    x1 = (3*m_RowPos+1)-4;
    y1 = (3*m_ColPos+1)-4;
    guLCD.filled_rectangle(x1,y1,x1+8, y1+8,BLACK);
    gBuzzy.SetLocation(nRow, nCol); 
    
    x1 = (3*m_RowPos+1)-4;
    y1 = (3*m_ColPos+1)-4;
    
    
    
    // Clean up the part that will be left
    /*
        switch(m_DesiredDirection)
        {
            case RIGHT_DIR:
            guLCD.filled_rectangle(x1+8,y1-1,x1, y1-3,BLACK);
            break;
        
            case LEFT_DIR:
            guLCD.filled_rectangle(x1,y1+11,x1+8, y1+9,BLACK);
            break;
        
            case UP_DIR:
            guLCD.filled_rectangle(x1-1,y1+8,x1-3, y1,BLACK);
            break;
        
            case DOWN_DIR:
            guLCD.filled_rectangle(x1+11,y1+8,x1+9, y1,BLACK);
            break;
        }
   */
    guLCD.BLIT(x1, y1, 9, 9, &BuzzyIcon[GetImageIndex()][0][0]);  
    
    
    
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool Buzzy::DidGhostGetBuzzy()
{

    return false;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool Buzzy::IsMoveAllowed(const int &nNewRow, const int &nNewCol)
{
    if(m_DesiredDirection == RIGHT_DIR)
    {
        if (gCnstMaze[nNewRow+1][nNewCol] == 1)
        {
           return false;
        }
        else if (gCnstMaze[nNewRow-1][nNewCol] == 1)
        {
           return false;
        }
        else if (gCnstMaze[nNewRow][nNewCol] == 1)
        {
           return false;
        }
        else
        {
           return true;
        }
    }
    else if(m_DesiredDirection == LEFT_DIR)
    {
        if (gCnstMaze[nNewRow+1][nNewCol] == 1)
        {
            return false;
        }
        else if (gCnstMaze[nNewRow-1][nNewCol] == 1)
        {
            return false;
        }
        else if (gCnstMaze[nNewRow][nNewCol] == 1)
        {
           return false;
        }
        else
        {
            return true;
        }
    }
    else if(m_DesiredDirection == UP_DIR)
    {
        if (gCnstMaze[nNewRow][nNewCol+1] == 1)
        {
            return false;
        }
        else if (gCnstMaze[nNewRow][nNewCol-1] == 1)
        {
            return false;
        }
        else if (gCnstMaze[nNewRow][nNewCol] == 1)
        {
           return false;
        }
        else
        {
            return true;
        }
    }
    else if(m_DesiredDirection == DOWN_DIR)
    {
        if (gCnstMaze[nNewRow][nNewCol+1] == 1)
        {
            return false;
        }
        else if (gCnstMaze[nNewRow][nNewCol-1] == 1)
        {
            return false;
        }
        else if (gCnstMaze[nNewRow][nNewCol] == 1)
        {
           return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }   
}
