#include "Valu.h"
#include "verilated.h"
#include <cstdio>

int main(int argc, char** argv){
    Verilated::commandArgs(argc, argv);
    Valu *dut = new Valu;

    //Test Add, 2 + 7 = 9
    dut->a = 2;
    dut->b = 7;
    dut->alu_control = 0;
    dut->eval();
    if (dut->result == 9)
        printf("Add test PASSED\n");
    else
        printf("Add test FAILED: expected 9, got %u\n", dut->result);

    //Test Sub, 3 - 6 = -3
    dut->a = 3;
    dut->b = 6;
    dut->alu_control = 1;
    dut->eval();
    if (dut->result == (uint32_t)-3)
        printf("Sub test PASSED\n");
    else
        printf("Sub test FAILED: expected -3, got %u\n", dut->result);

    //Test And, 10 & 8 = 8
    dut->a = 10;
    dut->b = 8;
    dut->alu_control = 2;
    dut->eval();
    if (dut->result == 8)
        printf("And test PASSED\n");
    else
        printf("And test FAILED: expected 8, got %u\n", dut->result);

    //Test Or, 6 | 11 = 15
    dut->a = 6;
    dut->b = 11;
    dut->alu_control = 3;
    dut->eval();
    if (dut->result == 15)
        printf("Or test PASSED\n");
    else
        printf("Or test FAILED: expected 15, got %u\n", dut->result);

    //Test Xor, 3 ^ 7 = 4
    dut->a = 3;
    dut->b = 7;
    dut->alu_control = 4;
    dut->eval();
    if (dut->result == 4)
        printf("Xor test PASSED\n");
    else
        printf("Xor test FAILED: expected 4, got %u\n", dut->result);

    //Test SLL, 1 << 3 = 8
    dut->a = 1;
    dut->b = 3;
    dut->alu_control = 5;
    dut->eval();
    if (dut->result == 8)
        printf("SLL test PASSED\n");
    else
        printf("SLL test FAILED: expected 8, got %u\n", dut->result);

    //Test SRL, 8 >> 1 = 4
    dut->a = 8;
    dut->b = 1;
    dut->alu_control = 6;
    dut->eval();
    if (dut->result == 4)
        printf("SRL test PASSED\n");
    else
        printf("SRL test FAILED: expected 4, got %u\n", dut->result);

    //Test SRA, -8 >>> 1 = -4
    dut->a = (uint32_t)-8;
    dut->b = 1;
    dut->alu_control = 7;
    dut->eval();
    if (dut->result == (uint32_t)-4)
        printf("SRA test PASSED\n");
    else
        printf("SRA test FAILED: expected -4, got %u\n", dut->result);

    //Test SLT, 3 < 6 = 1
    dut->a = 3;
    dut->b = 6;
    dut->alu_control = 8;
    dut->eval();
    if (dut->result == 1)
        printf("SLT test PASSED\n");
    else
        printf("SLT test FAILED: expected 1, got %u\n", dut->result);

    //Test SLT, 6 < 3 = 0
    dut->a = 6;
    dut->b = 3;
    dut->alu_control = 8;
    dut->eval();
    if (dut->result == 0)
        printf("SLT (reverse) test PASSED\n");
    else
        printf("SLT (reverse) test FAILED: expected 0, got %u\n", dut->result);

    delete dut;
    return 0;
}