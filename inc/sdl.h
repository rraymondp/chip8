#ifndef SDL_H
#define SDL_H

#include "SDL2/SDL.h"
#include <iostream>

class sdl{
    private:
        SDL_Event event;
        enum state {STOP, RUNNING, PAUSE};
        enum state myState;
        bool debug;

    public:
        sdl();
        ~sdl();
        void eventHandler(uint8_t keypad[]);
        int getState();
};

#endif