#include "Vdmem.h"
#include "verilated.h"
#include <cstdio>

int main(int argc, char** argv){
    Verilated::commandArgs(argc, argv);
    Vdmem *dut = new Vdmem;

    dut->clk = 0;
    dut->eval();

    // Test 1: write 42 to address 0, read it back
    dut->writeEnable = 1;
    dut->address = 0;
    dut->writeData = 42;
    dut->clk = 1; dut->eval();
    dut->clk = 0; dut->eval();

    if (dut->readData == 42)
        printf("Write/Read test PASSED\n");
    else
        printf("Write/Read test FAILED: expected 42, got %u\n", dut->readData);

    // Test 2: verify enable low causes no update
    dut->writeEnable = 0;
    dut->address = 0;
    dut->writeData = 999;
    dut->clk = 1; dut->eval();
    dut->clk = 0; dut->eval();

    if (dut->readData == 42)
        printf("Write enable low test PASSED\n");
    else
        printf("Write enable low test FAILED: expected 42, got %u\n", dut->readData);

    // Test 3: write to address 4, verify address 0 unchanged
    dut->writeEnable = 1;
    dut->address = 4;
    dut->writeData = 100;
    dut->clk = 1; dut->eval();
    dut->clk = 0; dut->eval();

    dut->address = 0;
    dut->eval();
    if (dut->readData == 42)
        printf("Address isolation test PASSED\n");
    else
        printf("Address isolation test FAILED: expected 42, got %u\n", dut->readData);

    // Test 4: verify address 4 has correct value
    dut->address = 4;
    dut->eval();
    if (dut->readData == 100)
        printf("Address 4 read test PASSED\n");
    else
        printf("Address 4 read test FAILED: expected 100, got %u\n", dut->readData);

    delete dut;
    return 0;
}