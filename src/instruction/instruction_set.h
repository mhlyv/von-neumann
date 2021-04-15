#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

#include <assert.h>
#include <stddef.h>

#include "instruction/instruction.h"
#include "vector/vector.hpp"

#define INSTRUCTION(name) \
	class name : public Instruction { \
		name(size_t opcode, vector::Vector<Operand> &operands) : \
				Instruction(opcode, operands) {} \
		void operator()(Register *registers = nullptr); \
	}; \
	void name::operator()(Register *registers)

namespace inst {

const size_t exit_opcode(1);

INSTRUCTION(exit) {
	(void)registers;
	for (Operand &o : this->operands) {
		if (!o.is_register()) {
			delete o.left();
		}
	}
}

INSTRUCTION(move) {
	assert(this->operands.size() == 2);
	if (this->operands[0].is_register()) {
		if (this->operands[1].is_register()) {
			registers[this->operands[0]] = registers[this->operands[1]];
		} else {
			registers[this->operands[0]] = this->operands[1];
		}
	} else {
	}
}

}

#undef INSTRUCTION

#endif // INSTRUCTION_SET_H
