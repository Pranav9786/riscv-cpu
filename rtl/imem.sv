module imem(
    input  logic [31:0] address,
    output logic [31:0] instr
);

logic [31:0] mem [63:0];

//load test into mem
initial begin
    $readmemh("programs/test.hex", mem);
end
//fetch
assign instr = mem[address >> 2];

endmodule
