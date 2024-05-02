#ifndef CHIP8_H
#define CHIP8_H

#include <time.h>

class chip8{
    private:

        unsigned char chip8_fontset[80] = {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        }

        //Opcodes are 2 bytes (16-bits) long --> short has 2 bytes of memory
        unsigned short opcode; 
        
        //Chip8 has 4KB (4096 Bytes of memory) --> char has 1 byte of memory
        unsigned char memory[4096]; 
        
        /*
        16 General Purpose 8-bit Registers: V[0, 1, 2, ..., F]
        Note V[F] is used as a flag register and is not used by the program
        */
        unsigned char V[16]; 

        /*
        16-bit Register
        Used to store memory addresses
        Since memory is only 3-bytes long, only the 12 LSB are used
        */
        unsigned short I; 
        
        /*
        16-bit Pseudo-Register: program counter (pc)
        Used to store the current executing address
        */
        unsigned short pc;

        /*
        8-bit Pseudo-Register: stack pointer (sp)
        Used to point to the topmost level of the stack
        */
        unsigned char sp; //stack pointer, used to point to the topmost level of the stack

        /*
        Stack
        Array of 16 16-bit values, used to store the address that the interpreter should return
        to when finished with a subroutine
        */
        unsigned short stack[16];

        /*
        Delay Timer (DT)
        Creates a delay
        The timer decrements at a rate of 60Hz.
        */
        unsigned char dt;

        /*
        Sound Timer (ST)
        When the sound timer is greater than zero, it will produce a sound
        The time decrements at a rate of 60Hz.
        */
        unsigned char st;

        /*
        Display
        The Chip-8 uses a 64x32-pixel monochrome display
        */
        unsigned char display[64 * 32];

        /*
        Keys
        The Chip-8 is based on a HEX keypad (0x0 - 0xF)
        therefor an array of length 16 can be used.

        Index is set to 1 when key is pressed
        Index is cleared to 0 when key is not pressed
        */
        unsigned char keypad[16]

    public:
        void initialize();
        void emutlateCycle();
        bool loadGame(char* filename);
        void incrementPC();
}

#endif