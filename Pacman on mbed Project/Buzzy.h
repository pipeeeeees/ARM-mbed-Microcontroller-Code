/*
    ECE 2036 Spring 2019 Lab 4
    David Pipes
    Buzzy game on mBed kit
*/
#pragma once

#include "Sprite.h"

class Buzzy : public Sprite
{
    public:
        Buzzy(){m_CurrentDirection = m_DesiredDirection = Sprite::LEFT_DIR;m_nActiveImage=0;};
        // Constructor
        Buzzy(enDIRECTIONS inDir, unsigned int inRow, unsigned int inCol);

        virtual ~Buzzy(){};
        virtual void Move();
        virtual bool IsMoveAllowed(const int &nNewRow, const int &nNewCol);

        void DrawInNewLocation(const int &nRow,const int &nCol);
        bool DidGhostGetBuzzy();
        
};

