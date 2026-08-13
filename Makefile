TOP = regfile
RTL_DIR = rtl
TB_DIR = tb
SIM_DIR = sim

VERILATOR_FLAGS = --Wall --trace --cc $(RTL_DIR)/$(TOP).sv --exe $(TB_DIR)/tb_$(TOP).cpp -CFLAGS "-std=c++14"

all: sim

sim:
	mkdir -p $(SIM_DIR)
	verilator $(VERILATOR_FLAGS) -Mdir obj_dir
	make -C obj_dir -f V$(TOP).mk
	./obj_dir/V$(TOP)

waves:
	surfer $(SIM_DIR)/waves.vcd

clean:
	rm -rf obj_dir $(SIM_DIR)

.PHONY: all sim waves clean