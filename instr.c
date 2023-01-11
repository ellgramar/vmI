#include "instr.h"

void nibble1(computer *c){
    if (c->spr[PC] > 0xfffffff){
        printf("Error: PC out of bounds");
        exit(1);
    }
    uint16_t opcd1 = c->mem[c->spr[PC]] >> 12;
    // switch case statement for opcd1
    switch (opcd1){
        case 0x0:
            nibble2(c);
            break;
        case 0x1:   // r2 = lower byte
            c->gpr[c->mem[c->spr[PC]] >> 8 & 0xf] = c->mem[c->spr[PC]] & 0xff;
            

    }
}

void nibble2(computer *c){

}