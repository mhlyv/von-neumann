#include <stddef.h>

#include "control_unit/control_unit.h"
#include "cpu/cpu.h"
#include "instruction/instruction.h"
#include "instruction/instruction_set.h"
#include "memory/memory.h"
#include "processing_unit/processing_unit.h"

namespace cpu {

CPU::CPU(memory::Data &pc, size_t regs) : cu(pc), pu(regs) {
}

size_t CPU::perform_cycle(memory::Memory &mem) {
	this->cu.fetch(mem);
	inst::Instruction &inst = this->cu.instruction();
	this->pu.eval(inst);
	return inst.read();
}

void CPU::run(memory::Memory &mem) {
	while (this->perform_cycle(mem) != inst::exit_opcode);
}

}
