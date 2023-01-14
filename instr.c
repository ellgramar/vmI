#include "instr.h"

void nibble1(computer *c){
    if (c->pc > 0xfffffff){
        printf("Error: PC out of bounds");
        exit(1);
    }
    uint16_t instr = c->mem[c->pc];
    // switch case statement for opcd1
    switch ((instr & 0xf000) >> 12){
        case 0x0:
            nibble2(c);
            break;
        case 0x1:   // gpr[n2] = lower byte of instruction
            c->gpr[(instr & 0x0f00) >> 8] = instr & 0x00ff;
            break;
        case 0x2:  // indirect load
            // destination is nibble2          source 1 is nibble3                          source 2 is nibble4
            c->gpr[(instr * 0x0f00) >> 8] = ((uint32_t)c->gpr[(instr & 0x00f0) << 12]) | ((uint32_t)c->gpr[(instr & 0x000f)]);
            break;
        case 0x3:   // indirect store from gpr[n2] to address in n3 and n4
            c->mem[(((uint32_t)c->gpr[(instr & 0x00f0) << 12]) | ((uint32_t)c->gpr[(instr & 0x000f)]))] = c->gpr[(instr * 0x0f00) >> 8];
            break;
        case 0x4:
            

    }
}

void nibble2(computer *c){

}