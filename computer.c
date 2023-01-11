#include "computer.h"

computer *computer_init(){
    computer *c = malloc(sizeof(computer));
    c->mem = calloc(0xfffffff, sizeof(uint16_t));
    c->gpr = calloc(16, sizeof(uint16_t));
    c->spr = calloc(8, sizeof(uint32_t));
    c->ivt = calloc(8, sizeof(uint32_t));
    return c;
}