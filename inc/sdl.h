#ifndef SDL_H
#define SDL_H

#include "SDL2/SDL.h"
#include <iostream>

class sdl{
    private:
        SDL_Event event;
        enum state {STOP, RUNNING, PAUSE};
        enum state myState;

    public:
        sdl();
        ~sdl();
        void eventHandler();
        int getState();
};

#endif