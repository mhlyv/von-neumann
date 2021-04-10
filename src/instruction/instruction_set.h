#ifndef __INSTRUCTION_SET_H__
#define __INSTRUCTION_SET_H__

#include <stddef.h>

#include "instruction/instruction.h"
#include "vector/vector.hpp"

#define INSTRUCTION(name) \
	class name : public Instruction { \
		name(size_t opcode, vector::Vector<Operand *> &operands) : \
				Instruction(opcode, operands) {} \
		void operator()(Register *registers = NULL); \
	}; \
	void name::operator()(Register *registers)



namespace inst {
const size_t exit_opcode(1);
}

#undef INSTRUCTION

#endif // __INSTRUCTION_SET_H__
