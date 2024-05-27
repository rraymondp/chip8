#ifndef SDL_H
#define SDL_H

#include "SDL2/SDL.h"
#include "chip8.h"
#include <iostream>


class sdl{
    private:
        SDL_Event event;
        enum state {STOP, RUNNING, PAUSE};
        enum state myState;
        bool debug;
        chip8* chip8Ref;

    public:
        sdl(chip8* chip8);
        ~sdl();
        void eventHandler();
        void updateTimer();
        int getState();
};

#endif