#ifndef DISPLAY_H
#define DISPLAY_H

#include "SDL2/SDL.h"
#include "chip8.h"
#include <iostream>

class display{
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Rect rect;
        int windowHeight;
        int windowWidth;
        int windowScaleFactor;  //scale factor since original size of chip-8 is 32x64 (which is too small)

        int fg_colour; //foreground colour
        int bg_colour; //background colour

        chip8* chip8Ref;

    public:
        display(chip8 *chip8);
        ~display();
        void clearDisplay();
        void updateDisplay();

        int getFgColour();
        int getBgColour();

        int getFgRed();
        int getFgGreen();
        int getFgBlue();
        int getFgAlpha();

        int getBgRed();
        int getBgGreen();
        int getBgBlue();
        int getBgAlpha();

        void setFgColour(int colour);
        void setBgColour(int colour);

};

#endif