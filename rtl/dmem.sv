//data memory
module dmem(
    input logic clk,
    input logic [31:0] address,
    input logic writeEnable,
    input logic [31:0] writeData,
    output logic [31:0] readData
);

logic [31:0] mem [63:0];

//read - comb
assign readData = mem[address >> 2];

//write - seq
always_ff @(posedge clk) begin
    if (writeEnable)
        mem[address >> 2] <= writeData;
end

endmodule
