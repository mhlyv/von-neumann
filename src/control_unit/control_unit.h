#ifndef __CONTROL_UNIT_H__
#define __CONTROL_UNIT_H__

#include <stddef.h>

#include "memory/memory.h"
#include "instruction/instruction.h"

namespace cu {

class ControlUnit {
private:
	const inst::Instruction *instruction_register;
	memory::Data program_counter;
public:
	ControlUnit();
	ControlUnit(memory::Memory &mem);
	void fetch(memory::Memory &mem);
	const inst::Instruction &instruction() const;
	void reset();
	~ControlUnit();
};

}

#endif // __CONTROL_UNIT_H__
