#include "../inc/sdl.h"

sdl::sdl(){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    myState = RUNNING; 
}

sdl::~sdl(){
    SDL_Quit();
}

void sdl::eventHandler(){
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                myState = STOP;
                break;
            case SDL_KEYDOWN:
                break;
            case SDL_KEYUP:
                break;
            default:
                break;
        }

    }
}

int sdl::getState(){
    return myState;
}


