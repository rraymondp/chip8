#include "../inc/sdl.h"
using namespace std;

sdl::sdl(chip8* c8){
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    myState = RUNNING; 
    debug = false;
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

                    case(SDLK_1):
                        keypad[0x1] = 1;
                        if(debug){cout << "1 is down" << endl;}
                        break;
                    case(SDLK_2):
                        keypad[0x2] = 1;
                        if(debug){cout << "2 is down" << endl;}
                        break;
                    case(SDLK_3):
                        keypad[0x3] = 1;
                        if(debug){cout << "3 is down" << endl;}
                        break;
                    case(SDLK_4):
                        keypad[0xC] = 1;
                        if(debug){cout << "4 is down" << endl;}
                        break;

                    case(SDLK_q):
                        keypad[0x4] = 1;
                        if(debug){cout << "Q is down" << endl;}
                        break;
                    case(SDLK_w):
                        keypad[0x5] = 1;
                        if(debug){cout << "W is down" << endl;}
                        break;
                    case(SDLK_e):
                        keypad[0x6] = 1;
                        if(debug){cout << "E is down" << endl;}
                        break;
                    case(SDLK_r):
                        keypad[0xD] = 1;
                        if(debug){cout << "R is down" << endl;}
                        break;

                    case(SDLK_a):
                        keypad[0x7] = 1;
                        if(debug){cout << "A is down" << endl;}
                        break;
                    case(SDLK_s):
                        keypad[0x8] = 1;
                        if(debug){cout << "S is down" << endl;}
                        break;
                    case(SDLK_d):
                        keypad[0x9] = 1;
                        if(debug){cout << "D is down" << endl;}
                        break;
                    case(SDLK_f):
                        keypad[0xE] = 1;
                        if(debug){cout << "F is down" << endl;}
                        break;

                    case(SDLK_z):
                        keypad[0xA] = 1;
                        if(debug){cout << "Z is down" << endl;}
                        break;
                    case(SDLK_x):
                        keypad[0x0] = 1;
                        if(debug){cout << "X is down" << endl;}
                        break;
                    case(SDLK_c):
                        keypad[0xB] = 1;
                        if(debug){cout << "C is down" << endl;}
                        break;
                    case(SDLK_v):
                        keypad[0xF] = 1;
                        if(debug){cout << "V is down" << endl;}
                        break;

                    default:
                        break;
                }
                break;

            case SDL_KEYUP:
                switch(event.key.keysym.sym){
                    case(SDLK_1):
                        keypad[0x1] = 0;
                        if(debug){cout << "1 is up" << endl;}
                        break;
                    case(SDLK_2):
                        keypad[0x2] = 0;
                        if(debug){cout << "2 is up" << endl;}
                        break;
                    case(SDLK_3):
                        keypad[0x3] = 0;
                        if(debug){cout << "3 is up" << endl;}
                        break;
                    case(SDLK_4):
                        keypad[0xC] = 0;
                        if(debug){cout << "4 is up" << endl;}
                        break;

                    case(SDLK_q):
                        keypad[0x4] = 0;
                        if(debug){cout << "Q is up" << endl;}
                        break;
                    case(SDLK_w):
                        keypad[0x5] = 0;
                        if(debug){cout << "W is up" << endl;}
                        break;
                    case(SDLK_e):
                        keypad[0x6] = 0;
                        if(debug){cout << "E is up" << endl;}
                        break;
                    case(SDLK_r):
                        keypad[0xD] = 0;
                        if(debug){cout << "R is up" << endl;}
                        break;

                    case(SDLK_a):
                        keypad[0x7] = 0;
                        if(debug){cout << "A is up" << endl;}
                        break;
                    case(SDLK_s):
                        keypad[0x8] = 0;
                        if(debug){cout << "S is up" << endl;}
                        break;
                    case(SDLK_d):
                        keypad[0x9] = 0;
                        if(debug){cout << "D is up" << endl;}
                        break;
                    case(SDLK_f):
                        keypad[0xE] = 0;
                        if(debug){cout << "F is up" << endl;}
                        break;

                    case(SDLK_z):
                        keypad[0xA] = 0;
                        if(debug){cout << "Z is up" << endl;}
                        break;
                    case(SDLK_x):
                        keypad[0x0] = 0;
                        if(debug){cout << "X is up" << endl;}
                        break;
                    case(SDLK_c):
                        keypad[0xB] = 0;
                        if(debug){cout << "C is up" << endl;}
                        break;
                    case(SDLK_v):
                        keypad[0xF] = 0;
                        if(debug){cout << "V is up" << endl;}
                        break;

                    default:
                        break;
                }
            break;
        }
    }
}   

void sdl::updateTimer(){
    uint8_t* dtRef = chip8Ref->getDTimer();
    uint8_t* stRef = chip8Ref->getSTimer();

    if(dtRef > 0){
        (*dtRef)--;
    }
    if(stRef > 0){
        (*stRef)--;
    }
}

int sdl::getState(){
    return myState;
}
