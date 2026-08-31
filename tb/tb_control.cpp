#include "Vcontrol.h"
#include "verilated.h"
#include <cstdio>

int main(int argc, char** argv){
    Verilated::commandArgs(argc, argv);
    Vcontrol *dut = new Vcontrol;

    // Test R-type ADD (opcode=0110011, funct3=000, funct7=0000000)
    dut->opcode = 0b0110011;
    dut->funct3 = 0b000;
    dut->funct7 = 0b0000000;
    dut->eval();
    if (dut->reg_write == 1 && dut->alu_ctrl == 0b0000 && dut->alu_src == 0)
        printf("R-type ADD test PASSED\n");
    else
        printf("R-type ADD test FAILED\n");

    // Test R-type SUB (funct7=0100000)
    dut->opcode = 0b0110011;
    dut->funct3 = 0b000;
    dut->funct7 = 0b0100000;
    dut->eval();
    if (dut->reg_write == 1 && dut->alu_ctrl == 0b0001 && dut->alu_src == 0)
        printf("R-type SUB test PASSED\n");
    else
        printf("R-type SUB test FAILED\n");

    // Test I-type ADDI (opcode=0010011, funct3=000)
    dut->opcode = 0b0010011;
    dut->funct3 = 0b000;
    dut->funct7 = 0b0000000;
    dut->eval();
    if (dut->reg_write == 1 && dut->alu_ctrl == 0b0000 && dut->alu_src == 1)
        printf("I-type ADDI test PASSED\n");
    else
        printf("I-type ADDI test FAILED\n");

    // Test LOAD (opcode=0000011)
    dut->opcode = 0b0000011;
    dut->funct3 = 0b010;
    dut->funct7 = 0b0000000;
    dut->eval();
    if (dut->reg_write == 1 && dut->mem_read == 1 && dut->alu_src == 1)
        printf("LOAD test PASSED\n");
    else
        printf("LOAD test FAILED\n");

    // Test STORE (opcode=0100011)
    dut->opcode = 0b0100011;
    dut->funct3 = 0b010;
    dut->funct7 = 0b0000000;
    dut->eval();
    if (dut->mem_write == 1 && dut->reg_write == 0 && dut->alu_src == 1)
        printf("STORE test PASSED\n");
    else
        printf("STORE test FAILED\n");

    // Test BRANCH (opcode=1100011)
    dut->opcode = 0b1100011;
    dut->funct3 = 0b000;
    dut->funct7 = 0b0000000;
    dut->eval();
    if (dut->branch == 1 && dut->reg_write == 0 && dut->mem_write == 0)
        printf("BRANCH test PASSED\n");
    else
        printf("BRANCH test FAILED\n");

    // Test JAL (opcode=1101111)
    dut->opcode = 0b1101111;
    dut->funct3 = 0b000;
    dut->funct7 = 0b0000000;
    dut->eval();
    if (dut->jump == 1 && dut->reg_write == 1)
        printf("JAL test PASSED\n");
    else
        printf("JAL test FAILED\n");

    delete dut;
    return 0;
}