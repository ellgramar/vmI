#ifndef COMPUTER_H
#define COMPUTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct computer{
    uint16_t *mem;
    uint16_t *gpr;
    uint32_t *spr;
    uint32_t *ivt;
} computer;

enum spr{
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