#include<stdio.h>
#include<stdint.h>
extern struct CPU{
    int16_t ram[1024];
    int16_t rom[1024];
    int16_t reg[8];
};
int8_t int8_to_int7(int8_t integer){
    int8_t num=integer;
    if(num>=0b1000000){
        num>>1;
        num+=0b10000000;
    }
    return num;
}
void cpu_add(struct CPU *cpu, int16_t i){
    int16_t regA,regB,regC;
    regA=cpu->rom[i]>>10;
    regB=cpu->rom[i]-((cpu->rom[i]>>10)<<10)>>7;
    regC=cpu->rom[i]-(regB<<7)-(regA<<10);
    cpu->reg[regA]=cpu->reg[regB]+cpu->reg[regC];
}
void cpu_addi(struct CPU *cpu, int16_t i){
    int16_t regA,regB,regC;
    int8_t immed;
    regA=(cpu->rom[i]-(1<<13))>>10;
    regB=((cpu->rom[i]-(1<<13))-(regA<<10))>>7;
    immed=int8_to_int7(((cpu->rom[i]-(1<<13))-(regA<<10))-(regB<<7));
    cpu->reg[regA]=cpu->reg[regB]+immed;
}
void cpu_nand(struct CPU *cpu, int16_t i){
    int16_t regA,regB,regC;
    int8_t immed;
    regA=(cpu->rom[i]-(1<<14))>>10;
    regB=(cpu->rom[i]-(regA<<10)-(1<<14))>>7;
    regC=(cpu->rom[i]-(regA<<10)-(1<<14)-(regB<<7));
    cpu->reg[regA]=~(cpu->reg[regB]&cpu->reg[regC]);
}
void cpu_lui(struct CPU *cpu, int16_t i){
    int16_t regA,regB,regC;
    int8_t immed;
    regA=(cpu->rom[i]-(1<<14))>>10;
    immed=(cpu->rom[i]-(1<<14)-(regA<<10))<<6;
    cpu->reg[regA]=immed;
}
void cpu_sw(struct CPU *cpu, int16_t i){
    int16_t regA,regB,regC;
    int8_t immed;
    regA=(cpu->rom[i]-(0b101<<13))>>10;
    regB=((cpu->rom[i]-(0b101<<13))-(regA<<10))>>7;
    immed=int8_to_int7(((cpu->rom[i]-(0b101<<13))-(regA<<10))-(regB<<7));
    cpu->ram[cpu->reg[regB]+immed]=cpu->reg[regA];
}
void cpu_lw(struct CPU *cpu, int16_t i){
    int16_t regA,regB,regC;
    int8_t immed;
    regA=(cpu->rom[i]-(0b100<<13))>>10;
    regB=((cpu->rom[i]-(0b100<<13))-(regA<<10))>>7;
    immed=int8_to_int7(((cpu->rom[i]-(0b100<<13))-(regA<<10))-(regB<<7));
    cpu->reg[regA]=cpu->ram[cpu->reg[regB]+immed];
}
int cpu_beq(struct CPU *cpu, int16_t i){
    int16_t regA,regB,regC;
    int8_t immed;
    int16_t cp=i;
    regA=(cpu->rom[i]-(0b110<<13))>>10;
    regB=((cpu->rom[i]-(0b110<<13))-(regA<<10))>>7;
    immed=int8_to_int7(((cpu->rom[i]-(0b110<<13))-(regA<<10))-(regB<<7));
    if(cpu->reg[regA]==cpu->reg[regB]){
        cp=i+1+immed;
    }
    return cp;
}
int cpu_jalr(struct CPU *cpu, int16_t i){
    int16_t regA,regB,regC;
    int8_t immed;
    int16_t cp=i;
    regA=(cpu->rom[i]-(0b111<<13))>>10;
    regB=((cpu->rom[i]-(0b111<<13))-(regA<<10))>>7;
    cpu->reg[regA]=i;
    cp=cpu->reg[regB];
    return cp;
}
int run(struct CPU *cpu, int16_t pcList){
    //struct CPU *cpu=&prcocess;
    int16_t regA,regB,regC;
    int8_t immed;
    int16_t i=0;
    for(int pc=0; pc<pcList; pc++){
        i+=1;
        if(cpu->rom[i]>=0&&cpu->rom[i]<=0b0001111110000111){ //add
            cpu_add(cpu, i);
        }
        if(cpu->rom[i]>=0b0010000000000000&&cpu->rom[i]<=0b0011111111111111){ //addi
            cpu_addi(cpu, i);
        }
        if(cpu->rom[i]>=0b0100000000000000&&cpu->rom[i]<=0b0101111110000111){ //nand
            cpu_nand(cpu, i);
        }
        if(cpu->rom[i]>=0b0110000000000000&&cpu->rom[i]<=0b01111100000000000){ //lui
            cpu_lui(cpu, i);
        }
        if(cpu->rom[i]>=0b1010000000000000&&cpu->rom[i]<=0b1011111111111111){ //sw
            cpu_sw(cpu, i);
        }
        if(cpu->rom[i]>=0b1000000000000000&&cpu->rom[i]<=0b1001111111111111){ //lw
            cpu_lw(cpu, i);
        }
        if(cpu->rom[i]>=0b1100000000000000&&cpu->rom[i]<=0b1101111111111111){ //beq
            i=cpu_beq(cpu, i);
        }
        if(cpu->rom[i]>=0b1110000000000000&&cpu->rom[i]<=0b1111111110000000){ //jalr
            i=cpu_jalr(cpu, i);
        }
    }
}