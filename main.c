#include "main.h"

int main(int argc, char *argv[]){
    //create a pointer to an array of uint16_t of size 0x0ffffff
    uint16_t *mem = (uint16_t *)calloc(0x0ffffff, sizeof(uint16_t));
    //check if the array is null
    if(mem == NULL){
        //if it is, print an error message
        printf("Error: calloc failed");
    }
    
    free(mem);
    return 0;
}