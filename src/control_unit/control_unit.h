#ifndef __CONTROL_UNIT_H__
#define __CONTROL_UNIT_H__

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

#endif // __CONTROL_UNIT_H__
