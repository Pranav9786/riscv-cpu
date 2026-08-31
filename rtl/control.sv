module control (
    input logic [6:0] opcode,
    input logic [2:0] funct3,
    input logic [6:0] funct7,
    output logic reg_write,
    output logic mem_write,
    output logic mem_read,
    output logic alu_src,
    output logic [3:0] alu_ctrl,
    output logic branch,
    output logic jump
);

//ALU encodings
localparam ALU_ADD  = 4'b0000;
localparam ALU_SUB  = 4'b0001;
localparam ALU_AND  = 4'b0010;
localparam ALU_OR   = 4'b0011;
localparam ALU_XOR  = 4'b0100;
localparam ALU_SLL  = 4'b0101;
localparam ALU_SRL  = 4'b0110;
localparam ALU_SRA  = 4'b0111;
localparam ALU_SLT  = 4'b1000;

//RV32I opcodes
localparam OP_R      = 7'b0110011; // R-type - ops with 2 registers
localparam OP_I      = 7'b0010011; // I-type - ops with 1 register
localparam OP_LOAD   = 7'b0000011; // Load
localparam OP_STORE  = 7'b0100011; // Store
localparam OP_BRANCH = 7'b1100011; // Branch
localparam OP_JAL    = 7'b1101111; // Jump and link

always_comb begin
    // safe defaults, prevent latches
    reg_write = 0;
    mem_write = 0;
    mem_read = 0;
    alu_src = 0;
    alu_ctrl = ALU_ADD;
    branch = 0;
    jump = 0;

    case (opcode)
        OP_R: begin
            reg_write = 1;
            case ({funct7, funct3}) //concat both signals
                10'b0000000_000: alu_ctrl = ALU_ADD;
                10'b0100000_000: alu_ctrl = ALU_SUB;
                10'b0000000_111: alu_ctrl = ALU_AND;
                10'b0000000_110: alu_ctrl = ALU_OR;
                10'b0000000_100: alu_ctrl = ALU_XOR;
                10'b0000000_001: alu_ctrl = ALU_SLL;
                10'b0000000_101: alu_ctrl = ALU_SRL;
                10'b0100000_101: alu_ctrl = ALU_SRA;
                10'b0000000_010: alu_ctrl = ALU_SLT;
                default:         alu_ctrl = ALU_ADD;
            endcase
        end

        OP_I: begin
            reg_write = 1;
            alu_src   = 1;
            case (funct3)
                3'b000: alu_ctrl = ALU_ADD; // addi
                3'b111: alu_ctrl = ALU_AND; // andi
                3'b110: alu_ctrl = ALU_OR;  // ori
                3'b100: alu_ctrl = ALU_XOR; // xori
                3'b010: alu_ctrl = ALU_SLT; // slti
                3'b001: alu_ctrl = ALU_SLL; // slli
                3'b101: alu_ctrl = (funct7[5]) ? ALU_SRA : ALU_SRL; //only need funct7 to distinguish SRA/SRL for I-type ops
                default: alu_ctrl = ALU_ADD;
            endcase
        end

        // load full word
        OP_LOAD: begin
            reg_write = 1;
            mem_read = 1;
            alu_src = 1;
            alu_ctrl = ALU_ADD;
        end

        OP_STORE: begin
            mem_write = 1;
            alu_src = 1;
            alu_ctrl = ALU_ADD;
        end

        OP_BRANCH: begin
            branch = 1;
            alu_ctrl = ALU_SUB;
        end

        OP_JAL: begin
            reg_write = 1;
            jump = 1;
        end

        default: begin
            reg_write = 0;
            mem_write = 0;
            mem_read = 0;
            alu_src = 0;
            alu_ctrl = ALU_ADD;
            branch = 0;
            jump = 0;
        end
    endcase
end

endmodule
