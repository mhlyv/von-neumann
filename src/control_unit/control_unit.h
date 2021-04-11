#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

#include <stddef.h>

#include "memory/memory.h"
#include "instruction/instruction.h"

namespace cu {

class ControlUnit {
private:
	inst::Instruction *instruction_register;
	memory::Data &program_counter;
public:
	ControlUnit(memory::Data &pc);
	void fetch(memory::Memory &mem);
	inst::Instruction &instruction();
	void reset();
	~ControlUnit();
};

}

#endif // CONTROL_UNIT_H
