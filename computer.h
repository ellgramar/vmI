#ifndef COMPUTER_H
#define COMPUTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct computer{
    uint16_t *mem;
    uint16_t *gpr;
    uint32_t *ivt;
    uint32_t pc;
    uint32_t sp;
    uint32_t fp;
    uint32_t lr;
    uint32_t cr;
    uint32_t tr;
    uint32_t er;
    uint32_t fr;

} computer;

enum Spr{
    PC = 0,
    SP = 1,
    FP = 2,
    LR = 3,
    CR = 4,
    TR = 5,
    ER = 6,
    FR = 7,
    spr_cnt = 8
};


#endif