#include <stddef.h>
#include <stdexcept>
#include <iostream>

#include "cpu/cpu.h"
#include "instruction/instruction.h"
#include "instruction/instruction_set.h"
#include "memory/memory.h"

namespace cpu {

CPU::CPU(size_t regs) : registers(regs) {
	if (regs < 1) {
		throw std::invalid_argument("The CPU needs at least 1 register");
	}
	for (memory::Data &r : this->registers) {
		r = 0;
	}
}

size_t CPU::perform_cycle(memory::Memory &mem) {
	inst::Instruction *inst = (inst::Instruction *)mem[this->registers[0]];
	// increment pc before the instruction to allow jumps
	this->registers[0]++;
	inst->operator()(this->registers);
	return inst->read();
}

void CPU::run(memory::Memory &mem) {
	while (this->perform_cycle(mem) != inst::exit_opcode);
}

}
