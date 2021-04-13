#pragma once

#include "Sprite.h"

class Ghosts : public Sprite
{
    public:
        virtual void Move();
        virtual bool IsMoveAllowed(const int &nNewRow, const int &nNewCol){return true;}    
};
