#include "../inc/chip8.h"
#include "../inc/sdl.h"
#include "../inc/display.h"
#include <iostream>

sdl mySDL;
display myDisplay;
chip8 myChip8;
using namespace std;

int main(int argc, char* argv[]){

    myDisplay.clearDisplay();

    while(mySDL.getState()){          //loop if not in STOP state
        myDisplay.updateDisplay();
        SDL_Delay(16); //16ms = 60Hz
    }

    return 0;
}



