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
        case 0x4:   // reletive direct jump
            if (instr & 0x0800){
                if ((c->pc + (instr & 0x07ff)) < c->sp && (c->pc + (instr & 0x07ff)) > c->pc){
                    c->pc += (instr & 0x07ff);
                } else {
                    printf("Error: Stack or PC overflow");
                    exit(2);
                }
            } else if (instr & 0x0800 == 0){
                if (((c->pc - (instr & 0x07ff)) < c->pc)){
                    c->pc -= (instr & 0x07ff);
                } else {
                    printf("Error: Stack underflow");
                    exit(3);
                }
            }
            break;
        case 0x5:   // add
            // convert numbers to int and uint16_t
            int num1 = c->gpr[(instr & 0x00f0) >> 4], num2 = c->gpr[(instr & 0x000f)];
            int snum1 = (int)((int16_t)num1), snum2 = (int)((int16_t)num2);
            // zero flag
            if (num1 + num2 == 0){
                c->fr |= 0x8000000; // zero flag
            }
            // carry or overflow flag
            if (num1 + num2 > 0xffff){
                c->fr |= 0x4000000; // carry flag
            }
            // negetive flag
            if (snum1 + snum2 < 0){
                c->fr |= 0x2000000; // negetive flag
            }
            // signed overflow flag
            if (snum1 + snum2 > 0x7fff || snum1 + snum2 < -0x8000){
                c->fr |= 0x1000000; // signed overflow flag
            }
            // store result
            c->gpr[(instr & 0x0f00) >> 8] = c->gpr[(instr & 0x00f0) >> 4] + c->gpr[(instr & 0x000f)];
            break;
        case 0x6:   // sub
            // convert numbers to int and uint16_t
            int num1 = c->gpr[(instr & 0x00f0) >> 4], num2 = c->gpr[(instr & 0x000f)];
            int snum1 = (int)((int16_t)num1), snum2 = (int)((int16_t)num2);
            // zero flag test
            if (num1 - num2 == 0){
                c->fr |= 0x8000000; // zero flag
            }
            // carry or overflow flag test
            if (num1 - num2 > 0xffff){
                c->fr |= 0x4000000; // carry flag
            }
            // negetive flag test test 
            if (snum1 - snum2 < 0){
                c->fr |= 0x2000000; // negetive flag
            }
            // signed overflow flag test
            if (snum1 - snum2 > 0x7fff || snum1 - snum2 < -0x8000){
                c->fr |= 0x1000000; // signed overflow flag
            }
            // store result
            c->gpr[(instr & 0x0f00) >> 8] = c->gpr[(instr & 0x00f0) >> 4] - c->gpr[(instr & 0x000f)];
            break;
        case 0x7:   // multiplication
            int num1 = c->gpr[(instr & 0x00f0) >> 4], num2 = c->gpr[(instr & 0x000f)];
            int snum1 = (int)((int16_t)num1), snum2 = (int)((int16_t)num2);
            // zero flag test
            if (num1 == 0 || num2 == 0){
                c->fr |= 0x8000000; // zero flag
            }
            // carry or overflow flag test
            if (num1 * num2 > 0xffff){
                c->fr |= 0x4000000; // carry flag
            }
            // negetive flag test test
            if (snum1 * snum2 < 0){
                c->fr |= 0x2000000; // negetive flag
            }
            // signed overflow flag test
            if (snum1 * snum2 > 0x7fff || snum1 * snum2 < -0x8000){
                c->fr |= 0x1000000; // signed overflow flag
            }
            // store result
            c->gpr[(instr & 0x0f00) >> 8] = c->gpr[(instr & 0x00f0) >> 4] * c->gpr[(instr & 0x000f)];
            break;
        case 0x8:   // division
            int num1 = c->gpr[(instr & 0x00f0) >> 4], num2 = c->gpr[(instr & 0x000f)];
            int snum1 = (int)((int16_t)num1), snum2 = (int)((int16_t)num2);\
            // zero flag test
            if (num1 == 0){ // divide by zero is undefined and not equal to zero
                c->fr |= 0x8000000; // zero flag
            }
            // carry or overflow flag test
            if (num1 / num2 > 0xffff){
                c->fr |= 0x4000000; // carry flag
            }
            // negetive flag test test
            if (snum1 / snum2 < 0){
                c->fr |= 0x2000000; // negetive flag
            }
            // signed overflow flag test
            if (snum1 / snum2 > 0x7fff || snum1 / snum2 < -0x8000){
                c->fr |= 0x1000000; // signed overflow flag
            }
            // store result
            c->gpr[(instr & 0x0f00) >> 8] = c->gpr[(instr & 0x00f0) >> 4] / c->gpr[(instr & 0x000f)];
            break;
        case 0x9:   // modulus
            int num1 = c->gpr[(instr & 0x00f0) >> 4], num2 = c->gpr[(instr & 0x000f)];
            int snum1 = (int)((int16_t)num1), snum2 = (int)((int16_t)num2);
            // zero flag test
            if (num1 % num2 == 0){
                c->fr |= 0x8000000; // zero flag
            }
            // carry or overflow flag test
            if (num1 % num2 > 0xffff){
                c->fr |= 0x4000000; // carry flag
            }
            // negetive flag test test
            if (snum1 % snum2 < 0){
                c->fr |= 0x2000000; // negetive flag
            }
            // signed overflow flag test
            if (snum1 % snum2 > 0x7fff || snum1 % snum2 < -0x8000){
                c->fr |= 0x1000000; // signed overflow flag
            }
            // store result
            c->gpr[(instr & 0x0f00) >> 8] = c->gpr[(instr & 0x00f0) >> 4] % c->gpr[(instr & 0x000f)];
            break;
        case 0xa:   // 

    }
}

void nibble2a(computer *c){
    uint16_t instr = c->mem[c->pc];
    switch ((instr & 0x0f00) >> 8){
        case 0x0:   // escape to nibble 3
            nibble3(c);
            break;
        case 0x1:   // indirect jump
            c->pc = ((((uint32_t)(c->gpr[(instr & 0x00f0) >> 4])) << 16) & 0x0fff0000) | ((uint32_t)(c->gpr[(instr & 0x000f)]));
            break;
        case 0x2:   // branch if equal
            if (c->fr & 0x8000000){
                c->pc = ((((uint32_t)(c->gpr[(instr & 0x00f0) >> 4])) << 16) & 0x0fff0000) | ((uint32_t)(c->gpr[(instr & 0x000f)]));
            }
            break;
        case 0x3:   // branch if greater than or equal
            if (c->fr & 0x4000000 || c->fr & 0x8000000){
                c->pc = ((((uint32_t)(c->gpr[(instr & 0x00f0) >> 4])) << 16) & 0x0fff0000) | ((uint32_t)(c->gpr[(instr & 0x000f)]));
            }
            break;
        case 0x4:   // branch if less than or equal
            if (c->fr & 0x2000000 || c->fr & 0x8000000){
                c->pc = ((((uint32_t)(c->gpr[(instr & 0x00f0) >> 4])) << 16) & 0x0fff0000) | ((uint32_t)(c->gpr[(instr & 0x000f)]));
            }
            break;
        case 0x5:   // branch if not equal
            if (!(c->fr & 0x8000000)){
                c->pc = ((((uint32_t)(c->gpr[(instr & 0x00f0) >> 4])) << 16) & 0x0fff0000) | ((uint32_t)(c->gpr[(instr & 0x000f)]));
            }
            break;
        case 0x6:   // branch if greater than
            if (!(c->fr & 0x4000000) && !(c->fr & 0x8000000)){
                c->pc = ((((uint32_t)(c->gpr[(instr & 0x00f0) >> 4])) << 16) & 0x0fff0000) | ((uint32_t)(c->gpr[(instr & 0x000f)]));
            }
            break;
        case 0x7:   // branch if less than
            if (!(c->fr & 0x2000000) && !(c->fr & 0x8000000)){
                c->pc = ((((uint32_t)(c->gpr[(instr & 0x00f0) >> 4])) << 16) & 0x0fff0000) | ((uint32_t)(c->gpr[(instr & 0x000f)]));
            }
            break;
        case 0x8:   // move value from one register to an other
            c->gpr[(instr & 0x00f0) >> 4] = c->gpr[(instr & 0x000f)];
            if (c->gpr[(instr & 0x00f0)>>4] == 0){
                c->fr |= 0x8000000; // zero flag
            }
            break;
        case 0x9:   // and
            c->gpr[(instr & 0x00f0) >> 4] &= c->gpr[(instr & 0x000f)];
            if (c->gpr[(instr & 0x00f0)>>4] == 0){
                c->fr |= 0x8000000; // zero flag
            }
            break;
        case 0xa:   // nand
            c->gpr[(instr & 0x00f0) >> 4] = ~(c->gpr[(instr & 0x00f0) >> 4] & c->gpr[(instr & 0x000f)]);
            if (c->gpr[(instr & 0x00f0)>>4] == 0){
                c->fr |= 0x8000000; // zero flag
            }
            break;
        case 0xb:   // or
            c->gpr[(instr & 0x00f0) >> 4] |= c->gpr[(instr & 0x000f)];
            if (c->gpr[(instr & 0x00f0)>>4] == 0){
                c->fr |= 0x8000000; // zero flag
            }
            break;
        case 0xc:   // nor
            c->gpr[(instr & 0x00f0) >> 4] = ~(c->gpr[(instr & 0x00f0) >> 4] | c->gpr[(instr & 0x000f)]);
            if (c->gpr[(instr & 0x00f0)>>4] == 0){
                c->fr |= 0x8000000; // zero flag
            }
            break;
        case 0xd:   // xor
            c->gpr[(instr & 0x00f0) >> 4] ^= c->gpr[(instr & 0x000f)];
            if (c->gpr[(instr & 0x00f0)>>4] == 0){
                c->fr |= 0x8000000; // zero flag
            }
            break;
        case 0xe:   // xnor
            c->gpr[(instr & 0x00f0) >> 4] = ~(c->gpr[(instr & 0x00f0) >> 4] ^ c->gpr[(instr & 0x000f)]);
            if (c->gpr[(instr & 0x00f0)>>4] == 0){
                c->fr |= 0x8000000; // zero flag
            }
            break;
        

    }
}

void nibble2b(computer *c){

}

void nibble3(computer *c){
    uint16_t instr = c->mem[c->pc];
    switch ((instr & 0x00f0) >> 4){
        case 0x0:   // escape to no register opcodes
            nibble4a(c);
            break;
        case 0x1:   // swap bytes in register
            uint16_t tempLow = (c->gpr[(instr & 0x000f)] & 0x00ff) << 8;
            c->gpr[(instr & 0x000f)] >> 8;
            c->gpr[(instr & 0x000f)] |= tempLow;\
            if (c->gpr[(instr & 0x000f)] == 0){
                c->fr |= 0x8000000; // zero flag
            }
            break;
        case 0x2:  // increment register
            c->gpr[(instr & 0x000f)]++;
            if (c->gpr[(instr & 0x000f)] == 0){
                c->fr |= 0x8000000; // zero flag
            }
            break;
        case 0x3:   // decrement register
            c->gpr[(instr & 0x000f)]--;
            if (c->gpr[(instr & 0x000f)] == 0){
                c->fr |= 0x8000000; // zero flag
            }
            break;
        case 0x4:   // signed shift left
            uint16_t sign = (c->gpr[(instr & 0x000f)] & 0x8000);
            c->gpr[(instr & 0x000f)] <<= 1;
            if (sign > 0){
                c->gpr[(instr & 0x000f)] |= 0x8000;
            } else (sign == 0){
                c->gpr[(instr & 0x000f)] &= 0x7fff;
            }
            break;
        case 0x5:   // signed shift right
            uint16_t sign = (c->gpr[(instr & 0x000f)] & 0x8000);
            c->gpr[(instr & 0x000f)] &= 0x7fff;
            c->gpr[(instr & 0x000f)] >>= 1;
            if(sign > 0){
                c->gpr[(instr & 0x000f)] |= 0x8000;
            } else (sign == 0){
                c->gpr[(instr & 0x000f)] &= 0x7fff;
            }
            break;
        case 0x6:   // rotate left
            uint16_t temp = (c->gpr[(instr & 0x000f)] & 0x8000) >> 15;
            c->gpr[(instr & 0x000f)] <<= 1;
            c->gpr[(instr & 0x000f)] |= temp;
            break;
        case 0x7:   // signed rotate left
            // TODO
            break;
        case 0x8:   // rotate right
            uint16_t temp = (c->gpr[(instr & 0x000f)] & 0x0001) << 15;
            c->gpr[(instr & 0x000f)] >>= 1;
            c->gpr[(instr & 0x000f)] |= temp;
            break;
        case 0x9:   // signed rotate right
            // TODO
            break;
        case 0xa:   // push register onto stack
            c->mem[c->sp] = c->gpr[(instr & 0x000f)];
            c->sp--;
            break;
        case 0xb:   // pop register from stack
            c->gpr[(instr & 0x000f)] = c->mem[c->sp];
            c->sp++;
            break;
        case 0xc:   // write terminal out
            // TODO
            break;
        case 0xd:   // read terminal in
            // TODO
            break;
        case 0xe:   // interrupt enable/disable
            c->fr |= ((uint32_t)(c->gpr[(instr & 0x000f)])) << 15;
            break;
        case 0xf:   // not
            c->gpr[(instr & 0x000f)] = ~c->gpr[(instr & 0x000f)];
            if (c->gpr[(instr & 0x000f)] == 0){
                c->fr |= 0x8000000; // zero flag
            }
            break;
    }
}

void nibble4a(computer *c){

}