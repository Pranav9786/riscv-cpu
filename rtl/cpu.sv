module cpu (
    input logic clk,
    input logic reset
);

    //PC
    logic [31:0] pc, pc_next;

    //Instruction fetch
    logic [31:0] instr;

    //Instruction fields
    logic [6:0] opcode;
    logic [4:0] rs1, rs2, rd;
    logic [2:0] funct3;
    logic [6:0] funct7;

    // Control signals
    logic reg_write, mem_write, mem_read;
    logic alu_src, branch, jump;
    logic [3:0] alu_ctrl;

    // Register file outputs
    logic [31:0] reg_data1, reg_data2;

    // Immediate
    logic [31:0] imm;

    // ALU
    logic [31:0] alu_a, alu_b, alu_result;
    logic alu_zero;

    // Memory
    logic [31:0] mem_data;

    // Writeback
    logic [31:0] write_data;

    // Branch/jump target
    logic [31:0] branch_target, jump_target;
    logic take_branch;

    // ─── Program Counter ───────────────────────────────────────────
    always_ff @(posedge clk) begin
        if (reset)
            pc <= 32'b0;
        else
            pc <= pc_next;
    end

    // Next PC logic
    assign branch_target = pc + (imm << 1);
    assign jump_target = pc + imm;
    assign take_branch = branch & alu_zero;

    always_comb begin
        if (jump)
            pc_next = jump_target;
        else if (take_branch)
            pc_next = branch_target;
        else
            pc_next = pc + 4;
    end

    // ─── Instruction Fetch ─────────────────────────────────────────
    imem imem_inst (
        .address (pc),
        .instr (instr)
    );

    // ─── Instruction Decode ────────────────────────────────────────
    assign opcode = instr[6:0];
    assign rd = instr[11:7];
    assign funct3 = instr[14:12];
    assign rs1 = instr[19:15];
    assign rs2 = instr[24:20];
    assign funct7 = instr[31:25];

    // ─── Control Unit ──────────────────────────────────────────────
    control control_inst (
        .opcode (opcode),
        .funct3 (funct3),
        .funct7 (funct7),
        .reg_write (reg_write),
        .mem_write (mem_write),
        .mem_read (mem_read),
        .alu_src (alu_src),
        .alu_ctrl (alu_ctrl),
        .branch (branch),
        .jump (jump)
    );

    // ─── Register File ─────────────────────────────────────────────
    regfile regfile_inst (
        .clk (clk),
        .sourceReg1 (rs1),
        .sourceReg2 (rs2),
        .writeTo (rd),
        .writeData (write_data),
        .outReg1 (reg_data1),
        .outReg2 (reg_data2),
        .enable (reg_write)
    );

    // ─── Immediate Generator ───────────────────────────────────────
    always_comb begin
        case (opcode)
            7'b0010011,         // I-type
            7'b0000011:         // Load
                imm = {{20{instr[31]}}, instr[31:20]};
            7'b0100011:         // Store
                imm = {{20{instr[31]}}, instr[31:25], instr[11:7]};
            7'b1100011:         // Branch
                imm = {{19{instr[31]}}, instr[31], instr[7], instr[30:25], instr[11:8], 1'b0};
            7'b1101111:         // JAL
                imm = {{11{instr[31]}}, instr[31], instr[19:12], instr[20], instr[30:21], 1'b0};
            default:
                imm = 32'b0;
        endcase
    end

    // ─── ALU Input Mux ─────────────────────────────────────────────
    assign alu_a = reg_data1;
    assign alu_b = alu_src ? imm : reg_data2;

    // ─── ALU ───────────────────────────────────────────────────────
    alu alu_inst (
        .a (alu_a),
        .b (alu_b),
        .alu_control (alu_ctrl),
        .result (alu_result),
        .zero (alu_zero)
    );

    // ─── Data Memory ───────────────────────────────────────────────
    dmem dmem_inst (
        .clk (clk),
        .address (alu_result),
        .writeEnable (mem_write),
        .writeData (reg_data2),
        .readData (mem_data)
    );

    // ─── Writeback Mux ─────────────────────────────────────────────
    assign write_data = mem_read ? mem_data : alu_result;

endmodule
