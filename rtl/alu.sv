module alu(
    input logic [31:0] a,
    input logic [31:0] b,
    input logic [3:0] alu_control,
    output logic [31:0] result,
    output logic zero
  );

  always_comb begin
    case (alu_control)
      4'b0000: result = a + b; //Add
      4'b0001: result = a - b; //Subtract
      4'b0010: result = a & b; //Bitwise and
      4'b0011: result = a | b; //Bitwise or
      4'b0100: result = a ^ b; //Bitwise xor
      4'b0101: result = a << b[4:0]; //Logic shift a left by b[4:0] positions
      4'b0110: result = a >> b[4:0]; //Logic shift a right by b[4:0] positions
      4'b0111: result = $signed(a) >>> b[4:0]; //Arithmetic shift right by b[4:0] positions
      4'b1000: result = $signed(a) < $signed(b)? 32'b1:32'b0; //Signed less than
      default: result = 32'b0;
    endcase
  end

  assign zero = (result == 32'b0);

endmodule
