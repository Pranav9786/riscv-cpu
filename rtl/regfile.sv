module regfile(
    input logic clk,
    input logic [4:0] sourceReg1, sourceReg2,
    input logic [4:0] writeTo,
    input logic [31:0] writeData,
    output logic [31:0] outReg1, outReg2,
    input logic enable
);

// 32 regs, each 32 bits
logic [31:0] registers [31:0];

// Read logic (combinational)
//Handle x0 case
assign outReg1 = (sourceReg1 == 5'b0) ? 32'b0 : registers[sourceReg1];
assign outReg2 = (sourceReg2 == 5'b0) ? 32'b0 : registers[sourceReg2];

// Write logic (sequential)
//Cannot write to x0
always_ff @(posedge clk) begin
    if (enable && writeTo != 5'b0)
        registers[writeTo] <= writeData;
end

endmodule
