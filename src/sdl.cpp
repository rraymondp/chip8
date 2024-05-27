#include "../inc/sdl.h"
using namespace std;

sdl::sdl(chip8* c8){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    myState = RUNNING; 
    debug = true;
    chip8Ref = c8;
}

sdl::~sdl(){
    SDL_Quit();
}

/*
Original    QWERTY
-------------------
123C        1234
456D        QWER
789E        ASDF
A0BF        ZXCV
*/

void sdl::eventHandler(){
    uint8_t* keypad = chip8Ref->getKeypad();
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                myState = STOP;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case(SDLK_ESCAPE):
                        myState = STOP;
                        break;
                    
                    case(SDLK_p):
                        if(myState == RUNNING){
                            myState = PAUSE;
                            if(debug){ cout << "--- PAUSED ---" << endl; }
                        }
                        else{
                            myState = RUNNING;
                        }
                        break;
                }

            default:
                keypad[0x1] = state[SDL_SCANCODE_1];
                keypad[0x2] = state[SDL_SCANCODE_2];
                keypad[0x3] = state[SDL_SCANCODE_3];
                keypad[0xC] = state[SDL_SCANCODE_4];

                keypad[0x4] = state[SDL_SCANCODE_Q];
                keypad[0x5] = state[SDL_SCANCODE_W];
                keypad[0x6] = state[SDL_SCANCODE_E];
                keypad[0xD] = state[SDL_SCANCODE_R];
                
                keypad[0x7] = state[SDL_SCANCODE_A];
                keypad[0x8] = state[SDL_SCANCODE_S];
                keypad[0x9] = state[SDL_SCANCODE_D];
                keypad[0xE] = state[SDL_SCANCODE_F];

                keypad[0xA] = state[SDL_SCANCODE_Z];
                keypad[0x0] = state[SDL_SCANCODE_X];
                keypad[0xB] = state[SDL_SCANCODE_C];
                keypad[0xF] = state[SDL_SCANCODE_V];
                break;
        }
    }   
}

void sdl::updateTimer(){
    uint8_t* dtRef = chip8Ref->getDTimer();
    uint8_t* stRef = chip8Ref->getSTimer();

    if(dtRef > 0){
        *dtRef--;
    }
    if(stRef > 0){
        *stRef--;
    }
}

int sdl::getState(){
    return myState;
}
