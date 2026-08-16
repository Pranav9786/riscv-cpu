#include "Vimem.h"
#include "verilated.h"
#include <cstdio>

int main(int argc, char** argv){
    Verilated::commandArgs(argc, argv);
    Vimem *dut = new Vimem;

    // Test 1: address 0 should return instruction 1
    dut->address = 0;
    dut->eval();
    if (dut->instr == 0x00500093)
        printf("Address 0 test PASSED\n");
    else
        printf("Address 0 test FAILED: expected 0x00500093, got 0x%08X\n", dut->instr);

    // Test 2: address 4 should return instruction 2
    dut->address = 4;
    dut->eval();
    if (dut->instr == 0x00A00113)
        printf("Address 4 test PASSED\n");
    else
        printf("Address 4 test FAILED: expected 0x00A00113, got 0x%08X\n", dut->instr);

    // Test 3: address 8 should return instruction 3
    dut->address = 8;
    dut->eval();
    if (dut->instr == 0x002081B3)
        printf("Address 8 test PASSED\n");
    else
        printf("Address 8 test FAILED: expected 0x002081B3, got 0x%08X\n", dut->instr);

    delete dut;
    return 0;
}