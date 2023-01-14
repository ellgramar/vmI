#include "computer.h"

computer *computer_init(){
    computer *c = malloc(sizeof(computer));
    c->mem = calloc(0xfffffff, sizeof(uint16_t));
    c->gpr = calloc(16, sizeof(uint16_t));
    c->ivt = calloc(8, sizeof(uint32_t));
    c->pc = calloc(1, sizeof(uint32_t));
    c->sp = calloc(1, sizeof(uint32_t));
    c->fp = calloc(1, sizeof(uint32_t));
    c->lr = calloc(1, sizeof(uint32_t));
    c->cr = calloc(1, sizeof(uint32_t));
    c->tr = calloc(1, sizeof(uint32_t));
    c->er = calloc(1, sizeof(uint32_t));
    c->fr = calloc(1, sizeof(uint32_t));
    return c;
}