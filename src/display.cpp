#include "../inc/display.h"

display::display(){
    windowHeight = 32;
    windowWidth = 64;
    windowScaleFactor = 20;
    window = NULL;
    renderer = NULL;

    fg_colour = 0xFFFFFFFF; //white
    bg_colour = 0x008080FF; //teal
    // bg_colour = 0x000000FF; //black

    window = SDL_CreateWindow(
        "CHIP8 EMULATOR",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth * windowScaleFactor,
        windowHeight * windowScaleFactor,
        0
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

display::~display(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void display::clearDisplay(){
    SDL_SetRenderDrawColor(renderer, getBgRed(), getBgGreen(), getBgBlue(), getBgAlpha());
    SDL_RenderClear(renderer);
}

void display::updateDisplay(){
    SDL_RenderPresent(renderer);
}

void display::setFgColour(int colour){
    fg_colour = colour;
}

void display::setBgColour(int colour){
    bg_colour = colour;
}

int display::getFgRed(){
    return (fg_colour >> 24) & 0xFF;
}

int display::getFgGreen(){
    return (fg_colour >> 16) & 0xFF;
}

int display::getFgBlue(){
    return (fg_colour >> 8) & 0xFF;
}

int display::getFgAlpha(){
    return (fg_colour >> 0) & 0xFF;
}

int display::getBgRed(){
    return ((bg_colour >> 24) & 0xFF);
}

int display::getBgGreen(){
    return ((bg_colour >> 16) & 0xFF);
}

int display::getBgBlue(){
    return ((bg_colour >> 8) & 0xFF);
}

int display::getBgAlpha(){
    return ((bg_colour >> 0) & 0xFF);
}

int display::getBgColour(){
    return bg_colour;
}

int display::getFgColour(){
    return fg_colour;
}