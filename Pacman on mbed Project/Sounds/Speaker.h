/*
    ECE 2036 Spring 2019 Lab 4
    David Pipes
    Buzzy game on mBed kit
*/
#include "mbed.h"
#include "buzzy_siren.h"
#include "buzzy_begin.h"
#include "buzzy_chomp.h"
#include "buzzy_eatghost.h"
#include "buzzy_death.h"
#include "buzzy_eatfruit.h"


class Speaker : public PwmOut
{
public:
    enum BUZZY_Sounds {NO_SOUND, BEGIN, SIREN, CHOMP, EAT_GHOST, DEATH, EAT_FRUIT};
    
    Speaker(PinName nPin):PwmOut(nPin)
    {
       m_ulAudioArrayIndex = 0;
       SwitchSound(NO_SOUND);
    }
    
    void PlayNextValue()
    {
        if (m_pAudioArray != NULL)
        {
            write((float)m_pAudioArray[ GetNextValue() ]/255.0f);
        }       
    }
    
    void SwitchSound ( const BUZZY_Sounds &newSound)
    {
        if (newSound == m_enActiveAudioArray)
        {
            return;
        }
            
        m_ulAudioArrayIndex = 0;
        m_enActiveAudioArray = newSound;
        switch (newSound)
        {           
            case NO_SOUND:
                m_pAudioArray = NULL;
                break;   
            case BEGIN:
                m_pAudioArray = &data_BEGIN[0];
                break;   
            case CHOMP:
                 m_pAudioArray = &data_CHOMP[0];
                break;
            case EAT_GHOST:
                m_pAudioArray = &data_GHOST[0];
                break;
            case DEATH:
                m_pAudioArray = &data_DEATH[0];
                break;
            case EAT_FRUIT:
                m_pAudioArray = &data_EAT_FRUIT[0];
                break;              
            case SIREN:
            default:
                m_pAudioArray = &data_SIREN[0];
                break; 
        }
                             
    }
    
    unsigned int GetNextValue()
    {
        m_ulAudioArrayIndex++;
        switch (m_enActiveAudioArray)
        {           
            case BEGIN:
                m_ulAudioArrayIndex %= NUM_BEGIN_ELEMENTS;
                break;   
            case CHOMP:
                 m_ulAudioArrayIndex %= NUM_CHOMP_ELEMENTS;
                break;
            case EAT_GHOST:
                 m_ulAudioArrayIndex %= NUM_GHOST_ELEMENTS;
                break;
            case DEATH:
                 m_ulAudioArrayIndex %= NUM_DEATH_ELEMENTS;
                 if (m_ulAudioArrayIndex == 0)
                 {
                     SwitchSound(SIREN);
                 }
                break;
            case EAT_FRUIT:
                 m_ulAudioArrayIndex %= NUM_EAT_FRUIT_ELEMENTS;
                break;              
            case SIREN:
            default:
                 m_ulAudioArrayIndex %= NUM_SIREN_ELEMENTS;
                break;          
        }
        return m_ulAudioArrayIndex;
    }
private:
    unsigned long m_ulAudioArrayIndex;
    BUZZY_Sounds m_enActiveAudioArray;
    const unsigned char *m_pAudioArray;
    
};

            
