#include<stdio.h>
#include<stdint.h>
#include"risc.h"

int main(){
    struct CPU cpu;
    for(int i=0; i<8; i++){
        cpu.reg[i]=0;
    }
    cpu.rom[0]=0b0010000001111111;
    cpu.rom[1]=0b0010000000000001;
    cpu.rom[2]=0b1100000010000000;
    run(&cpu,3);
    for(int i=0; i<8; i++){
        printf("\n%i",cpu.reg[i]);
    }
    for(int i=0; i<8; i++){
        printf("\n%i",cpu.reg[i]);
    }
    scanf("%i");
    return 0;
}