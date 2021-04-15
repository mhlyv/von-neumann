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
	memory::Data *dest;
	memory::Data *src;

	assert(this->operands.size() == 2);

	if (this->operands[0].is_register()) {
		dest = this->operands[0];
	} else {
		dest = &registers[this->operands[0]];
	}

	if (this->operands[1].is_register()) {
		src = this->operands[1];
	} else {
		src = &registers[this->operands[1]];
	}

	*dest = *src;
}

INSTRUCTION(add) {
	memory::Data *dest;
	memory::Data *src;

	if (this->operands[0].is_register()) {
		dest = this->operands[0];
	} else {
		dest = &registers[this->operands[0]];
	}

	for (size_t i = 1; i < this->operands.size(); i++) {
		if (this->operands[1].is_register()) {
			src = this->operands[1];
		} else {
			src = &registers[this->operands[1]];
		}
		*dest += *src;
	}
}

INSTRUCTION(sub) {
	memory::Data *dest;
	memory::Data *src;

	if (this->operands[0].is_register()) {
		dest = this->operands[0];
	} else {
		dest = &registers[this->operands[0]];
	}

	for (size_t i = 1; i < this->operands.size(); i++) {
		if (this->operands[1].is_register()) {
			src = this->operands[1];
		} else {
			src = &registers[this->operands[1]];
		}
		*dest -= *src;
	}
}

INSTRUCTION(mult) {
	memory::Data *dest;
	memory::Data *src;

	if (this->operands[0].is_register()) {
		dest = this->operands[0];
	} else {
		dest = &registers[this->operands[0]];
	}

	for (size_t i = 1; i < this->operands.size(); i++) {
		if (this->operands[1].is_register()) {
			src = this->operands[1];
		} else {
			src = &registers[this->operands[1]];
		}
		*dest *= *src;
	}
}

INSTRUCTION(div) {
	memory::Data *dest;
	memory::Data *src;

	if (this->operands[0].is_register()) {
		dest = this->operands[0];
	} else {
		dest = &registers[this->operands[0]];
	}

	for (size_t i = 1; i < this->operands.size(); i++) {
		if (this->operands[1].is_register()) {
			src = this->operands[1];
		} else {
			src = &registers[this->operands[1]];
		}
		*dest /= *src;
	}
}

}

#undef INSTRUCTION

#endif // INSTRUCTION_SET_H
