#include "Vregfile.h"
#include "verilated.h"
#include <cstdio>

int main(int argc, char** argv){
    Verilated::commandArgs(argc, argv);
    Vregfile *dut = new Vregfile;

    dut->clk = 0;
    dut->eval();

    // Test 1: write to register 1, read back data
    dut->enable = 1;
    dut->writeTo = 1;
    dut->writeData = 42;
    dut->sourceReg1 = 1;
    dut->clk = 1; dut->eval();
    dut->clk = 0; dut->eval();

    if (dut->outReg1 == 42)
        printf("Write/Read test PASSED\n");
    else
        printf("Write/Read test FAILED: expected 42, got %u\n", dut->outReg1);

    // Test 2: write to register 2, read reg1 and reg2 simultaneously
    dut->enable = 1;
    dut->writeTo = 2;
    dut->writeData = 100;
    dut->sourceReg1 = 1;
    dut->sourceReg2 = 2;
    dut->clk = 1; dut->eval();
    dut->clk = 0; dut->eval();

    if (dut->outReg1 == 42 && dut->outReg2 == 100)
        printf("Dual read test PASSED\n");
    else
        printf("Dual read test FAILED: reg1=%u reg2=%u\n", dut->outReg1, dut->outReg2);

    // Test 3: verify cannot write to x0
    dut->enable = 1;
    dut->writeTo = 0;
    dut->writeData = 999;
    dut->sourceReg1 = 0;
    dut->clk = 1; dut->eval();
    dut->clk = 0; dut->eval();

    if (dut->outReg1 == 0)
        printf("x0 hardwired zero test PASSED\n");
    else
        printf("x0 hardwired zero test FAILED: expected 0, got %u\n", dut->outReg1);

    // Test 4: verify enable low causes no update
    dut->enable = 0;
    dut->writeTo = 1;
    dut->writeData = 999;
    dut->sourceReg1 = 1;
    dut->clk = 1; dut->eval();
    dut->clk = 0; dut->eval();

    if (dut->outReg1 == 42)
        printf("Write enable low test PASSED\n");
    else
        printf("Write enable low test FAILED: expected 42, got %u\n", dut->outReg1);

    delete dut;
    return 0;
}