#include <stddef.h>

#include "memory/memory.h"
#include "instruction/instruction.h"
#include "control_unit/control_unit.h"

namespace cu {

ControlUnit::ControlUnit() : instruction_register(NULL), program_counter(0) {
}

ControlUnit::ControlUnit(memory::Memory &mem) :
	instruction_register((inst::Instruction *)mem[0]), program_counter(0) {
}

void ControlUnit::fetch(memory::Memory &mem) {
	this->instruction_register =
		(inst::Instruction *)mem[this->program_counter.read()];
	this->program_counter++;
}

const inst::Instruction &ControlUnit::instruction() const {
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
