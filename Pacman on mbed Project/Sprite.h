#pragma once
/*
    ECE 2036 Spring 2019 Lab 4
    David Pipes
    Buzzy game on mBed kit
*/

class Sprite
{
public:
    enum enDIRECTIONS {NO_DIR, UP_DIR, DOWN_DIR, LEFT_DIR, RIGHT_DIR};
    // Default Constructor
    Sprite();
    // Constructor
    Sprite(enDIRECTIONS inDir, unsigned int inRow, unsigned int inCol);
    
    virtual ~Sprite(){};
    
    void SetDesiredDirectionToMove(enDIRECTIONS dir);
    
    virtual void SetLocation(const int &nRow, const int &nCol) {m_RowPos=nRow;m_ColPos=nCol;};
    
    virtual void Move() = 0;
    virtual bool IsMoveAllowed(const int &nNewRow, const int &nNewCol) = 0;
    virtual int GetImageIndex() {return (m_nActiveImage++)%2;}
 
protected:
    
    enDIRECTIONS m_CurrentDirection;
    enDIRECTIONS m_DesiredDirection;
    
    unsigned int m_RowPos;
    unsigned int m_ColPos;
    int m_nActiveImage;   
    
    
};
