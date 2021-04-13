#include "Sprite.h"
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/*
    ECE 2036 Spring 2019 Lab 4
    David Pipes
    Buzzy game on mBed kit
*/
// Default Constructor
Sprite::Sprite():
m_CurrentDirection(NO_DIR), 
m_DesiredDirection(NO_DIR),
m_RowPos(0),
m_ColPos(0),
m_nActiveImage(0)
{
    
}
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// Constructor
Sprite::Sprite(enDIRECTIONS inDir, unsigned int inRow, unsigned int inCol):
m_CurrentDirection(inDir), 
m_DesiredDirection(inDir),
m_RowPos(inRow),
m_ColPos(inCol),
m_nActiveImage(0)
{
    
}    
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// SetDesiredDirectionToMove    
void Sprite::SetDesiredDirectionToMove(enDIRECTIONS dir)
{
    m_DesiredDirection = dir;
}