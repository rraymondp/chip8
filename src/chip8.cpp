#include "../inc/chip8.h"
#include <sys/stat.h>

using namespace std;

chip8::chip8(){
    srand(time(NULL)); //seed for random nember generatation for opcode 0xCxkk
    entryPoint = 0x200;
    pc = entryPoint; //pc starts at 0x200 since the first 512 bytes are reserved
    opcode = 0;
    I = 0;
    sp = 0;
    st = 0;
    dt = 0;
    drawFlag = false;

    debug = false;

    for(int i = 0; i < 80; i++){
        memory[i] = chip8_fontset[i];
    }
    for(int i = 0; i < 16; i++){
        stack[i] = 0;
        keypad[i] = 0;
        V[i] = 0;
    }
    for(int i = 0; i < 64 * 32; i++){
        display[i] = 0;
    }
}

bool chip8::loadGame(char* filename){

    FILE* rom = fopen(filename, "rb");
    if(!rom){
        cout << "File Not Found!" << endl;
        return false;
    }

    fseek(rom, 0, SEEK_END); //move file pointer to end of file
    size_t romSize = ftell(rom); //find the position of file pointer with respect to start of file (return number of bytes)
    size_t maxSize = sizeof(memory) - sizeof(entryPoint);
    rewind(rom); //sets file position to the beginning

    if(romSize > maxSize){
        cout << "ROM file is too big! ROM size: " << romSize << " Maz size: " << maxSize << endl;
        return false;
    }

    /*
    reads from a file and stores it into the buffer memory
    reads from the given rom, and stores it into memory starting at 0x200
    */
    fread(&memory[entryPoint], 1, romSize, rom); 

    fclose(rom);
    return true;
}

uint8_t* chip8::getKeypad(){
    return keypad;
}

uint8_t* chip8::getDisplay(){
    return display;
}

bool chip8::getDrawFlag(){
    return drawFlag;
}

uint8_t* chip8::getDTimer(){
    return &dt;
}

uint8_t* chip8::getSTimer(){
    return &st;
}

uint16_t chip8::getOpcode(){
    return opcode;
}

void chip8::updateTimers(){
    if(dt > 0){
        dt--;
    }
    if(st > 0){
        puts("BEEP");
        st--;
    }
}


/*
After each instruction is completed, the pc is incremented by 2 since an opcode/instruction
takes up 2 memory locations
*/
void chip8::incrementPC(){
    pc += 2;
}

void chip8::emutlateCycle(){

    /*
    Instructions/opcodes are 2 bytes long, however memory is only 1 byte long.
    Therefore, we need to combine/merge two words
    Opcodes are stored in big-endian, which means that the most significant values are stored first, at the lowest memory address
    In this case, the 2 most significant bytes are stored first.

    We will get the first word and shift it to the left by 8 bits since it will represent the 2 most significant bytes of the opcode
    Then we OR it with the second word at the next memory address
    */
    opcode = memory[pc] << 8 | memory[pc + 1];

    unsigned char x = (opcode & 0x0F00) >> 8; //x is a 4-bit value, located at the lower 4-bits of the 2 most significant bytes of the opcode
    unsigned char y = (opcode & 0x00F0) >> 4; //y is a 4-bit valye, located at the upper 4-bits of the 2 least significant bytes of the opcode
    unsigned char kk = (opcode & 0x00FF); //kk is the lowest 8-bits of an opcode
    bool isPressed;
    int i;
    int xCoord = 0;
    int yCoord = 0;
    int height = 0;
    drawFlag = false;

    // for(int i = 0; i < 16; i++){
    //     printf("%d, ", keypad[i]);
    // }
    // printf("\n");

    //printf("Address: 0x%04X, Opcode: 0x%04X\n", pc, opcode);

    switch (opcode & 0xF000){
        case 0x0000:
            switch (opcode & 0x00FF){
                //0x00E0 --> Clear display
                case 0x00E0:
                    //printf("[OK] Opcode: 0x%04X\n", opcode);
                    for(i = 0; i < 64 * 32; i++){
                        display[i] = 0;
                    }
                    incrementPC();
                    break;
                //0x00EE --> return from subroutine
                case 0x00EE:
                    //printf("[OK] Opcode: 0x%04X\n", opcode);
                    pc = stack[sp];
                    sp--;
                    incrementPC();
                    break;
                default:
                    //printf("[FAILED] Unknown Opcode: 0x%04X\n", opcode);
                    break;
            }
            break;

        //0x1nnn --> jump to location nnn
        //Note: no need to increment pc since we're moving it to a new location
        case 0x1000:
            pc = opcode & 0x0FFF;
            break;

        /*
        0x2nnn --> call subroutine at nnn
        
        Increments stack pointer then push current PC to the stack
        PC is then set to nnn
        */
        case 0x2000:
            sp++;
            stack[sp] = pc;
            pc = opcode & 0x0FFF;
            break;

        //0x3xkk --> skip next instruction if V[x] == kk
        case 0x3000:
            if(V[x] == kk){
                incrementPC();
            }
            incrementPC();
            break;

        //0x4xkk --> skip next instruction if V[x] != kk
        case 0x4000:
            if(V[x] != kk){
                incrementPC();
            }
            incrementPC();
            break;

        //0x5xy0 --> skip next instruction if V[x] == V[y]
        case 0x5000:
            if(V[x] == V[y]){
                incrementPC();
            }
            incrementPC();
            break;

        case 0x6000:
            V[x] = kk;
            incrementPC();
            break;

        case 0x7000:
            V[x] += kk;
            incrementPC();
            break;

        case 0x8000:
            switch (opcode & 0x000F){
                case(0x0000):
                    V[x] = V[y];
                    incrementPC();
                    break;

                case(0x0001):
                    V[x] |= V[y];
                    incrementPC();
                    break;
                
                case(0x0002):
                    V[x] &= V[y];
                    incrementPC();
                    break;
                
                case(0x0003):
                    V[x] ^= V[y];
                    incrementPC();
                    break;
                
                case(0x0004):
                    if((V[x] + V[y]) > 255){ V[0xF] = 1; }
                    else{ V[0xF] = 0; }
                    V[x] += V[y]; //only keep the 8 LSB if there is overflow
                    incrementPC();
                    break;
                
                case(0x0005):
                    if(V[x] > V[y]){ V[0xF] = 1; }
                    else{ V[0xF] = 0; }
                    V[x] -= V[y];
                    incrementPC();
                    break;
                
                case(0x0006):
                    V[0xF] = V[x] & 0x1;
                    V[x] >>= 1; // divide V[x] by 2 by shifting the bits by 1 to the right
                    incrementPC();
                    break;
                
                case(0x0007):
                    if(V[y] > V[x]){ V[0xF] = 1; }
                    else{ V[0XF] = 0; }
                    V[x] -= V[y];
                    incrementPC();
                    break;
                
                case(0x000E):
                    if((V[x] >> 7) & 0x1){ V[0xF] = 1; }
                    else{ V[0xF] = 0; }
                    V[x] <<= 1; // multiply V[x] by 2 by shifting the bits by 1 to the left
                    incrementPC();
                    break;

                default:
                    break;
            }
            break;
        
        case 0x9000:
            if(V[x] != V[y]){
                incrementPC();
            }
            incrementPC();
            break;
        
        case 0xA000:
            I = opcode & 0x0FFF;
            incrementPC();
            break;

        case 0xB000:
            pc = (opcode & 0x0FFF) + V[0];
            break;

        case 0xC000:
            V[x] = kk & (rand() % 256);
            incrementPC();
            break;
        
        case 0xD000: 
            drawFlag = true;
            xCoord = V[x] % 64; //x-coordinate wrap around
            yCoord = V[y] % 32; //y-coordinate wrap around 
            height = opcode & 0x000F;
            V[0xF] = 0;
            
            for(int row = 0; row < height; row++){
                // if(yCoord + row > 32){
                //     break;
                // }
                for(int col = 0; col < 8; col++){
                    // if(xCoord + col > 64){
                    //     break;
                    // }
                    if((memory[(I + row)] & (0b10000000 >> col)) != 0){                  //(I + row) --> Nth byte of data from the sprite font
                                                                                          //After getting the Nth byte, we want to check each bit from left to right and check if it is 1(not zero)
                                                                                          //If the bit from the sprite is 1, we want to XOR the pixel on the display starting at Vx and Vy
                        if(display[(xCoord + (64*yCoord)) + (64*row) + col] == 1){        //If the curr pixel on the display is already set/ON, then set the V[F] flag
                            V[0xF] = 1;                                                   
                        }
                        display[(xCoord + (64*yCoord)) + (64*row) + col] ^= 1;            //Then XOR the curr pixel on the display
                    }
                }
            }

        incrementPC();
        break;
        

        case 0xE000:
            switch(opcode & 0x00FF){
                case 0x009E:
                    //printf("Key 0x%02X\n", V[x]);
                    if(keypad[V[x]]){
                        incrementPC();
                    }
                    incrementPC();
                    break;
                case 0x00A1:
                    //printf("Key 0x%02X\n", V[x]);
                    if(!keypad[V[x]]){
                        incrementPC();
                    }
                    incrementPC();
                    break;
                default:
                    break;
            }
            break;
        
        case 0xF000:
            switch(opcode & 0x00FF){
                case 0x0007:
                    V[x] = dt;
                    incrementPC();
                    break;
                
                /*
                Check each key to see if it is pressed (set to 1)
                */
                case 0x000A:
                    for(i = 0; i < 16; i++){
                        if(keypad[i]){
                            V[x] = i;
                            incrementPC();
                            break;
                        }
                    }
                    break;
                    //isPressed = false;
                    // while(!isPressed){
                    //     if(V[i]){
                    //         V[x] = i;
                    //         isPressed = true;
                    //     }
                    //     i = ((i + 1) % 16);
                    // }
                    // incrementPC();
                    // break;

                case 0x0015:
                    dt = V[x];
                    incrementPC();
                    break;
                
                case 0x0018:
                    st = V[x];
                    incrementPC();
                    break;

                case 0x001E:
                    I += V[x];
                    incrementPC();
                    break;

                /*
                V[x] will contain a value 0x0 - 0xF which corresponds to a specific sprite in the fontset
                It is multiplied by 5 to get the starting address of the desired value since the fontset is placed at 0x0 in memory

                ex. V[x] = 0x6;
                To get the starting address of 6, we multiply 6 by 5 to get 30 --> therefore it starts at the 30th byte of memory
                */
                case 0x0029:
                    I = V[x] * 5;
                    incrementPC();
                    break;

                case 0x0033:
                    memory[I] = V[x] / 100;
                    memory[I + 1] = (V[x] / 10) % 10;
                    memory[I + 2] = V[x] % 10;
                    incrementPC();
                    break;

                case 0x0055:
                    for(i = 0; i <= x; i++){
                        memory[I + i] = V[i];
                    }
                    incrementPC();
                    break;

                case 0x0065:
                    for(i = 0; i <= x; i++){
                        V[i] = memory[I + i];
                    }
                    incrementPC();
                    break;

                default:
                    break;
            }
            break;
        
        default:
            break;
    }

    updateTimers();

}