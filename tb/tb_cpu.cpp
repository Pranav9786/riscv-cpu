#include "Vcpu.h"
#include "Vcpu___024root.h"
#include "verilated.h"
#include <cstdio>

#define CLOCK_CYCLE(dut) \
    dut->clk = 0; dut->eval(); \
    dut->clk = 1; dut->eval(); \
    dut->clk = 0; dut->eval();

int main(int argc, char** argv){
    Verilated::commandArgs(argc, argv);
    Vcpu *dut = new Vcpu;

    // Reset for 3 cycles
    dut->reset = 1;
    CLOCK_CYCLE(dut);
    CLOCK_CYCLE(dut);
    CLOCK_CYCLE(dut);
    dut->reset = 0;

    // Execute 3 instructions — one cycle each
    CLOCK_CYCLE(dut); // addi x1, x0, 5
    CLOCK_CYCLE(dut); // addi x2, x0, 10
    CLOCK_CYCLE(dut); // add  x3, x1, x2

    // Check register values
    uint32_t x1 = dut->rootp->cpu__DOT__regfile_inst__DOT__registers[1];
    uint32_t x2 = dut->rootp->cpu__DOT__regfile_inst__DOT__registers[2];
    uint32_t x3 = dut->rootp->cpu__DOT__regfile_inst__DOT__registers[3];

    if (x1 == 5)
        printf("x1 test PASSED: x1 = %u\n", x1);
    else
        printf("x1 test FAILED: expected 5, got %u\n", x1);

    if (x2 == 10)
        printf("x2 test PASSED: x2 = %u\n", x2);
    else
        printf("x2 test FAILED: expected 10, got %u\n", x2);

    if (x3 == 15)
        printf("x3 test PASSED: x3 = %u\n", x3);
    else
        printf("x3 test FAILED: expected 15, got %u\n", x3);

    delete dut;
    return 0;
}