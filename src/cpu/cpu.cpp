#include <stddef.h>
#include <stdexcept>
#include <iostream>

#include "cpu/cpu.h"
#include "instruction/instruction.h"
#include "instruction/instruction_set.h"
#include "memory/memory.h"

namespace cpu {

CPU::CPU(size_t regs) : registers(regs) {
	if (regs < 2) {
		throw std::invalid_argument("The CPU needs at least 2 registers");
	}
	for (memory::Data &r : this->registers) {
		r = 0;
	}
}

// set the stack pointer register
void CPU::set_sp(Register sp) {
	registers[1] = sp;
}

// evalute the next instruction, and increment the program counter
size_t CPU::perform_cycle(memory::Memory &mem) {
	inst::Instruction *inst = (inst::Instruction *)mem[this->registers[0]];
	// increment pc before the instruction to allow jumps
	this->registers[0]++;
	inst->operator()(this->registers);
	return inst->read();
}

// evalute instructions until the first exit instruction is evaluated
void CPU::run(memory::Memory &mem) {
	while (this->perform_cycle(mem) != inst::exit_opcode);
}

}
