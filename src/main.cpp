#include "../inc/chip8.h"
#include "../inc/sdl.h"
#include "../inc/display.h"
#include <iostream>

chip8 myChip8;
sdl mySDL(&myChip8);
display myDisplay(&myChip8);

using namespace std;

int main(int argc, char* argv[]){
    float delay;
    uint8_t* keypad = myChip8.getKeypad();
    // for(int i = 0; i < 16; i++){
    //     printf("%d, ", test[i]);
    // }
    // printf("\n");
    // test[0] = 20;
    //     for(int i = 0; i < 16; i++){
    //     printf("%d, ", test1[i]);
    // }

    if(!myChip8.loadGame("../ROMS/Games/Tetris.ch8")){
        return 1;
    }
    myDisplay.clearDisplay();

    while(mySDL.getState()){          //loop if not in STOP state

        mySDL.eventHandler();

        if(mySDL.getState() == 2){    //if PAUSE
            continue;
        }
    
        double startTime = SDL_GetPerformanceCounter();

        for(int i = 0; i < 600 / 60; i++){          //we want 700 instructions per second 
            myChip8.emutlateCycle();                //However, we update the display at 60Hz(16.67ms)

            if((myChip8.getOpcode() >> 12) == 0xD){
                break;
            }
        }                                           //Therefore we want to execute 700(inst/sec) * (1/60)(sec) to get number of instrcutions in 16.67ms

        double endTime = SDL_GetPerformanceCounter();

        double elapsedTIme = (double)((endTime - startTime) * 1000) / SDL_GetPerformanceFrequency();

        if(16.67 - elapsedTIme > 0){
            delay = 16.67 - elapsedTIme;
        }
        else{
            delay = 0;
        }

        if(myChip8.getDrawFlag()){
            myDisplay.updateDisplay();
        }

        SDL_Delay(delay); //16ms = 60Hz

    }

    return 0;
}



