#include <stddef.h>

#include "memory/memory.h"
#include "instruction/instruction.h"
#include "control_unit/control_unit.h"

namespace cu {

ControlUnit::ControlUnit(memory::Data &pc) :
	instruction_register(NULL), program_counter(pc) {
}

void ControlUnit::fetch(memory::Memory &mem) {
	this->instruction_register =
		(inst::Instruction *)mem[this->program_counter.read()];
	this->program_counter++;
}

inst::Instruction &ControlUnit::instruction() {
	return *this->instruction_register;
}

void ControlUnit::reset() {
	this->instruction_register = NULL;
	this->program_counter = 0;
}

ControlUnit::~ControlUnit() {
	this->reset();
}

}
