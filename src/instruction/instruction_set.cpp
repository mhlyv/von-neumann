#include <assert.h>
#include <iostream>
#include <stdbool.h>
#include <stddef.h>
#include <stdexcept>

#include "cpu/register.h"
#include "instruction/instruction.h"
#include "instruction/instruction_set.h"
#include "lang/token.h"
#include "vector/vector.hpp"

#define INSTRUCTION(_name) \
	void _name::operator()(vector::Vector<Register> &registers)

#define TRANSLATE(_name, _op_code, _inst) \
	do { \
		if (name == _name) { \
			return new _inst(_op_code, operands); \
		} \
	} while (0)

namespace inst {

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
		dest = &registers[this->operands[0]];
	} else {
		dest = this->operands[0];
	}

	if (this->operands[1].is_register()) {
		src = &registers[this->operands[1]];
	} else {
		src = this->operands[1];
	}

	*dest = *src;
}

INSTRUCTION(add_inst) {
	memory::Data *dest;
	memory::Data *src;

	if (this->operands[0].is_register()) {
		dest = &registers[this->operands[0]];
	} else {
		dest = this->operands[0];
	}

	for (size_t i = 1; i < this->operands.size(); i++) {
		if (this->operands[1].is_register()) {
			src = &registers[this->operands[1]];
		} else {
			src = this->operands[1];
		}
		*dest += *src;
	}
}

INSTRUCTION(sub_inst) {
	memory::Data *dest;
	memory::Data *src;

	if (this->operands[0].is_register()) {
		dest = &registers[this->operands[0]];
	} else {
		dest = this->operands[0];
	}

	for (size_t i = 1; i < this->operands.size(); i++) {
		if (this->operands[1].is_register()) {
			src = &registers[this->operands[1]];
		} else {
			src = this->operands[1];
		}
		*dest -= *src;
	}
}

INSTRUCTION(mult_inst) {
	memory::Data *dest;
	memory::Data *src;

	if (this->operands[0].is_register()) {
		dest = &registers[this->operands[0]];
	} else {
		dest = this->operands[0];
	}

	for (size_t i = 1; i < this->operands.size(); i++) {
		if (this->operands[1].is_register()) {
			src = &registers[this->operands[1]];
		} else {
			src = this->operands[1];
		}
		*dest *= *src;
	}
}

INSTRUCTION(div_inst) {
	memory::Data *dest;
	memory::Data *src;

	if (this->operands[0].is_register()) {
		dest = &registers[this->operands[0]];
	} else {
		dest = this->operands[0];
	}

	for (size_t i = 1; i < this->operands.size(); i++) {
		if (this->operands[1].is_register()) {
			src = &registers[this->operands[1]];
		} else {
			src = this->operands[1];
		}
		*dest /= *src;
	}
}

INSTRUCTION(print_inst) {
	for (size_t i = 0; i < this->operands.size(); i++) {
		if (operands[i].is_register()) {
			std::cout << registers[operands[i]];
		} else {
			std::cout << (memory::Data::data_t)operands[i];
		}
	}
	std::cout << std::endl;
}

INSTRUCTION(jmpz_inst) {
	bool zero = false;
	if (operands[0].is_register()) {
		zero = registers[operands[0]] == 0;
	} else {
		zero = operands[0] == 0;
	}
	if (zero) {
		registers[0] = *(operands[1].left()) - 1;
	}
}

INSTRUCTION(jmpnz_inst) {
	bool zero = false;
	if (operands[0].is_register()) {
		zero = registers[operands[0]] == 0;
	} else {
		zero = operands[0] == 0;
	}
	if (!zero) {
		registers[0] = *(operands[1].left());
	}
}

INSTRUCTION(swap_inst) {
	memory::Data *dest;
	memory::Data *src;
	memory::Data tmp;

	assert(this->operands.size() == 2);

	if (this->operands[0].is_register()) {
		dest = &registers[this->operands[0]];
	} else {
		dest = this->operands[0];
	}

	if (this->operands[1].is_register()) {
		src = &registers[this->operands[1]];
	} else {
		src = this->operands[1];
	}

	tmp = *dest;
	*dest = *src;
	*src = tmp;
}

Instruction *build_instruction(const lang::Token &name,
		vector::Vector<Operand> &operands) {
	TRANSLATE( "exit", exit_opcode,  exit_inst);
	TRANSLATE( "move",           2,  move_inst);
	TRANSLATE(  "add",           3,   add_inst);
	TRANSLATE(  "sub",           4,   sub_inst);
	TRANSLATE( "mult",           5,  mult_inst);
	TRANSLATE(  "div",           6,   div_inst);
	TRANSLATE("print",           7, print_inst);
	TRANSLATE( "jmpz",           8,  jmpz_inst);
	TRANSLATE("jmpnz",           9, jmpnz_inst);
	TRANSLATE( "swap",          10,  swap_inst);

	throw std::invalid_argument("No such instruction");
	return nullptr; // unreachable
}

}

#undef TRANSLATE
#undef INSTRUCTION
