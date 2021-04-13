/*
    ECE 2036 Spring 2019 Lab 4
    David Pipes
    Buzzy game on mBed kit
*/

#include "mbed.h"
#include <stdio.h>
#include "Speaker.h"
#include "PinDetect.h"
#include "BuzzyGraphics.h"
#include "uLCD_4DGL.h"

#include "Buzzy.h"
#include "Ghosts.h"
////////////////////////////////////////
// Setup instance of LCD display
uLCD_4DGL guLCD(p28, p27, p29); // serial tx, serial rx, reset pin;
////////////////////////////////////////
// Setup instances of push button pins
PinDetect gPB_left(p19); 
PinDetect gPB_right(p16); 
PinDetect gPB_up(p17);
PinDetect gPB_down(p18);
// Create Buzzy and Ghosts
Buzzy gBuzzy;
Ghosts gGhosts[NUM_GHOSTS];
// Variable indicates if game is paused or running
int gGameState = GAME_PAUSED;
// Declare and initialize the speaker
Speaker gSpeakerOut(p21);

////////////////////////////////////////////////////////
// This is the maze that changes as the game is played
char gDynaMaze[MAZE_NUM_ROW][MAZE_NUM_COL]; 

//////////////////////////
// Prototype functions
void DrawMaze();

//////////////////////////////////////////////////////////////////////
// Interrupt routine
// used to output next analog sample whenever a timer interrupt occurs
void Sample_timer_interrupt(void)
{
    // Call speaker function to play next value
    gSpeakerOut.PlayNextValue();
}
//---------------------------------------------------------------------------------------------------
// Callback routine is interrupt activated by a debounced pb_left hit
void pb_left_hit_callback (void)
{
    gBuzzy.SetDesiredDirectionToMove(Sprite::LEFT_DIR);
}
//---------------------------------------------------------------------------------------------------
// Callback routine is interrupt activated by a debounced pb_right hit
void pb_right_hit_callback (void)
{
    gBuzzy.SetDesiredDirectionToMove(Sprite::RIGHT_DIR);
}
//---------------------------------------------------------------------------------------------------
// Callback routine is interrupt activated by a debounced pb_up hit
void pb_up_hit_callback (void)
{
    gBuzzy.SetDesiredDirectionToMove(Sprite::UP_DIR);
}
//---------------------------------------------------------------------------------------------------
// Callback routine is interrupt activated by a debounced pb_down hit
void pb_down_hit_callback (void)
{
    gBuzzy.SetDesiredDirectionToMove(Sprite::DOWN_DIR);
}
//---------------------------------------------------------------------------------------------------
int main()
{
        
    // Setup push buttons
    gPB_left.mode(PullUp);
    gPB_right.mode(PullUp);
    gPB_up.mode(PullUp);
    gPB_down.mode(PullUp);
    // Delay for initial pullup to take effect
    wait(.01);
    // Setup Interrupt callback functions for a pb hit
    gPB_left.attach_deasserted(&pb_left_hit_callback);
    gPB_right.attach_deasserted(&pb_right_hit_callback);
    gPB_up.attach_deasserted(&pb_up_hit_callback);
    gPB_down.attach_deasserted(&pb_down_hit_callback);
    // Setup speaker
    gSpeakerOut.period(1.0/200000.0);  
    // set up a timer to be used for sample rate interrupts
    Ticker Sample_Period;      
    Sample_Period.attach(&Sample_timer_interrupt, 1.0/(20000.0));

    //Setup LCD display
    guLCD.display_control(PORTRAIT);
    guLCD.background_color(BLACK);
    guLCD.cls();
    guLCD.baudrate(BAUD_3000000); //jack up baud rate to max for fast display
    wait(1.0);
  
    // Start sampling pb inputs using interrupts
    gPB_left.setSampleFrequency();
    gPB_right.setSampleFrequency();
    gPB_up.setSampleFrequency();
    gPB_down.setSampleFrequency();
    //////////////////////////////////////
    // Everything should be ready to start playing the game.
    
    
    while(1)
    {
        guLCD.cls();
        // Ask the user if they would like to play a game. 
        guLCD.printf("\nHello! If you would like to play Buzzy, press any button.\n");
        
        // Wait for a button to be pressed
        while(gPB_left == 1 && gPB_right == 1 && gPB_up == 1 && gPB_down == 1)
        {
            wait(0.001);
        }
        
        
        guLCD.cls();
        // Initialize needed parts
        
        
        // Reset the Ghosts and Buzzy states

        // Start up new game
        // Play introduction sounds while drawing the Maze
        gSpeakerOut.SwitchSound(Speaker::BEGIN);
        DrawMaze();
        gSpeakerOut.SwitchSound(Speaker::NO_SOUND);
        
        gBuzzy.SetLocation(25,20);
        wait(0.5);
        
        
        // Start Game loop
        gGameState = GAME_RUNNING;
        gBuzzy.SetDesiredDirectionToMove(Sprite::LEFT_DIR);
        while (gGameState == GAME_RUNNING)
        {
            gBuzzy.Move();
            
            // Check to see if Buzzy has eaten all the honey drops
            
            
            int drops(0);
            for ( int ii = 0; ii < 40; ii++)
            {   
                for ( int jj = 0; jj < 42; jj++)
                {   
                    if (gDynaMaze[ii][jj] == 2)
                    {   
                       drops++;
                    }
                }
            }
            
            if (drops == 0)
            {
                gGameState = GAME_PAUSED;
            }
            
            // Break out of loop if all honey drops are consumed
            wait(0.001);
        }
        gSpeakerOut.SwitchSound(Speaker::NO_SOUND);
        gGameState = GAME_PAUSED;
    }

} //end main