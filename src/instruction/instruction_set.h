#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

#include <stddef.h>

#include "instruction/instruction.h"
#include "vector/vector.hpp"

#define INSTRUCTION(name) \
	class name : public Instruction { \
		name(size_t opcode, vector::Vector<Operand *> &operands) : \
				Instruction(opcode, operands) {} \
		void operator()(Register *registers = nullptr); \
	}; \
	void name::operator()(Register *registers)



namespace inst {
const size_t exit_opcode(1);
}

#undef INSTRUCTION

#endif // INSTRUCTION_SET_H
