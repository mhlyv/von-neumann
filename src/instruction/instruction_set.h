#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

#include <assert.h>
#include <stddef.h>
#include <stdexcept>

#include "instruction/instruction.h"
#include "lang/token.h"
#include "vector/vector.hpp"

#define INSTRUCTION(_name) \
	class _name : public Instruction { \
		public: \
			_name(size_t opcode, vector::Vector<Operand> &operands) : \
					Instruction(opcode, operands) {} \
			void operator()(Register *registers = nullptr); \
	}; \
	void _name::operator()(Register *registers)

#define TRANSLATE(_name, _op_code, _inst) \
	do { \
		if (name == _name) { \
			return new _inst(_op_code, operands); \
		} \
	} while (0)

namespace inst {

const size_t exit_opcode(1);

INSTRUCTION(exit_inst) {
	(void)registers;
	for (Operand &o : this->operands) {
		if (!o.is_register()) {
			delete o.left();
		}
	}
}

INSTRUCTION(move_inst) {
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

INSTRUCTION(add_inst) {
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

INSTRUCTION(sub_inst) {
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

INSTRUCTION(mult_inst) {
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

INSTRUCTION(div_inst) {
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

Instruction *build_instruction(lang::Token &name,
		vector::Vector<Operand> &operands) {
	TRANSLATE("exit", exit_opcode, exit_inst);
	TRANSLATE("move",           1, move_inst);
	TRANSLATE( "add",           2,  add_inst);
	TRANSLATE( "sub",           3,  sub_inst);
	TRANSLATE("mult",           4, mult_inst);
	TRANSLATE( "div",           5,  div_inst);

	throw std::invalid_argument("No such instruction");
	return nullptr; // unreachable
}

}

#undef TRANSLATE
#undef INSTRUCTION

#endif // INSTRUCTION_SET_H
