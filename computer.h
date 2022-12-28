#ifndef COMPUTER_H
#define COMPUTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct computer{
    uint16_t *mem;
    uint16_t *gpr;
    uint16_t *spr;
} computer;



#endif