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

// check if operand is a register, put value in _name
#define OPERAND(_name, _nth) \
	do { \
		if (this->operands[_nth].is_register()) { \
			_name = &registers[this->operands[_nth]]; \
		} else { \
			_name = this->operands[_nth]; \
		} \
	} while (0)

// get stack pointer from register
// increment stack pointer
// make new copy of _name on stack
// write stack pointer value to register
#define PUSH(_name) \
	do { \
		memory::Data::data_t _raw = registers[1]; \
		memory::Data **_sptr = reinterpret_cast<memory::Data **>(_raw); \
		_sptr++; \
		*_sptr = new memory::Data(_name); \
		registers[1] = reinterpret_cast<memory::Data::data_t>(_sptr); \
	} while (0)

// get stack pointer from register
// copy value from stack to _name
// delete allocation from stack
// decrement stack pointer
// write stack pointer value to register
#define POP(_name) \
	do { \
		memory::Data::data_t _raw = registers[1]; \
		memory::Data **_sptr = reinterpret_cast<memory::Data **>(_raw); \
		_name = **_sptr; \
		delete *_sptr; \
		_sptr--; \
		registers[1] = reinterpret_cast<memory::Data::data_t>(_sptr); \
	} while (0)

namespace inst {

INSTRUCTION(exit_inst) {
	(void)registers;
	for (Operand &o : this->operands) {
		delete o.left();
	}
}

INSTRUCTION(move_inst) {
	memory::Data *dest;
	memory::Data *src;

	assert(this->operands.size() == 2);

	OPERAND(dest, 0);
	OPERAND(src, 1);

	*dest = *src;
}

INSTRUCTION(add_inst) {
	memory::Data *dest;
	memory::Data *src;

	OPERAND(dest, 0);

	for (size_t i = 1; i < this->operands.size(); i++) {
		OPERAND(src, i);
		*dest += *src;
	}
}

INSTRUCTION(sub_inst) {
	memory::Data *dest;
	memory::Data *src;

	OPERAND(dest, 0);

	for (size_t i = 1; i < this->operands.size(); i++) {
		OPERAND(src, i);
		*dest -= *src;
	}
}

INSTRUCTION(mult_inst) {
	memory::Data *dest;
	memory::Data *src;

	OPERAND(dest, 0);

	for (size_t i = 1; i < this->operands.size(); i++) {
		OPERAND(src, i);
		*dest *= *src;
	}
}

INSTRUCTION(div_inst) {
	memory::Data *dest;
	memory::Data *src;

	OPERAND(dest, 0);

	for (size_t i = 1; i < this->operands.size(); i++) {
		OPERAND(src, i);
		*dest /= *src;
	}
}

INSTRUCTION(shl_inst) {
	assert(this->operands.size() == 2);
	memory::Data *dest;
	memory::Data *src;
	OPERAND(dest, 0);
	OPERAND(src, 1);
	if (sizeof(memory::Data::data_t) > *src) {
		*dest <<= *src;
	} else {
		*dest = 0;
	}
}

INSTRUCTION(shr_inst) {
	assert(this->operands.size() == 2);
	memory::Data *dest;
	memory::Data *src;
	OPERAND(dest, 0);
	OPERAND(src, 1);
	if (sizeof(memory::Data::data_t) > *src) {
		*dest >>= *src;
	} else {
		*dest = 0;
	}
}

INSTRUCTION(and_inst) {
	assert(this->operands.size() == 2);
	memory::Data *dest;
	memory::Data *src;
	OPERAND(dest, 0);
	OPERAND(src, 1);
	*dest &= *src;
}

INSTRUCTION(or_inst) {
	assert(this->operands.size() == 2);
	memory::Data *dest;
	memory::Data *src;
	OPERAND(dest, 0);
	OPERAND(src, 1);
	*dest |= *src;
}

INSTRUCTION(xor_inst) {
	assert(this->operands.size() == 2);
	memory::Data *dest;
	memory::Data *src;
	OPERAND(dest, 0);
	OPERAND(src, 1);
	*dest ^= *src;
}

INSTRUCTION(not_inst) {
	assert(this->operands.size() == 1);
	memory::Data *dest;
	OPERAND(dest, 0);
	*dest = ~*dest;
}

INSTRUCTION(print_inst) {
	memory::Data *src;
	for (size_t i = 0; i < this->operands.size(); i++) {
		OPERAND(src, i);
		std::cout << (memory::Data::data_t)*src << " ";
	}
	std::cout << std::endl;
}

INSTRUCTION(jmpz_inst) {
	assert(operands.size() == 2);
	memory::Data *src;
	OPERAND(src, 0);

	if (*src == 0) {
		registers[0] = *(operands[1].left()) - 1;
	}
}

INSTRUCTION(jmpnz_inst) {
	assert(operands.size() == 2);
	memory::Data *src;
	OPERAND(src, 0);

	if (*src != 0) {
		registers[0] = *(operands[1].left());
	}
}

INSTRUCTION(swap_inst) {
	assert(operands.size() == 2);
	memory::Data *dest;
	memory::Data *src;
	memory::Data tmp;

	assert(this->operands.size() == 2);

	OPERAND(dest, 0);
	OPERAND(src, 1);

	tmp = *dest;
	*dest = *src;
	*src = tmp;
}

INSTRUCTION(push_inst) {
	assert(this->operands.size() == 1);
	memory::Data *src;
	OPERAND(src, 0);
	PUSH(*src);
}

INSTRUCTION(pop_inst) {
	assert(this->operands.size() == 1);
	memory::Data *dest;
	OPERAND(dest, 0);
	POP(*dest);
}

INSTRUCTION(call_inst) {
	assert(this->operands.size() == 1);
	memory::Data *dest;
	OPERAND(dest, 0);

	// save position of next instruction to stack
	// the register is already at the next instuction, because
	// it is incremented before the execution of the instruction
	memory::Data next_inst(registers[0]);
	PUSH(next_inst);

	// jump
	registers[0] = *dest;
}

INSTRUCTION(ret_inst) {
	assert(this->operands.size() == 0);
	// jump to position of next instruction
	POP(registers[0]);
}

Instruction *build_instruction(const lang::Token &name,
		vector::Vector<Operand> &operands) {
	TRANSLATE( "exit", exit_opcode,  exit_inst);
	TRANSLATE( "move",           2,  move_inst);
	TRANSLATE(  "add",           3,   add_inst);
	TRANSLATE(  "sub",           4,   sub_inst);
	TRANSLATE( "mult",           5,  mult_inst);
	TRANSLATE(  "div",           6,   div_inst);
	TRANSLATE(  "shl",           7,   shl_inst);
	TRANSLATE(  "shr",           8,   shr_inst);
	TRANSLATE(  "and",           9,   and_inst);
	TRANSLATE(   "or",          10,    or_inst);
	TRANSLATE(  "xor",          11,   xor_inst);
	TRANSLATE(  "not",          12,   not_inst);
	TRANSLATE("print",          13, print_inst);
	TRANSLATE( "jmpz",          14,  jmpz_inst);
	TRANSLATE("jmpnz",          15, jmpnz_inst);
	TRANSLATE( "swap",          16,  swap_inst);
	TRANSLATE( "push",          17,  push_inst);
	TRANSLATE(  "pop",          18,   pop_inst);
	TRANSLATE( "call",          19,	 call_inst);
	TRANSLATE(  "ret",          20,   ret_inst);

	throw std::invalid_argument("No such instruction");
	return nullptr; // unreachable
}

}

#undef POP
#undef PUSH
#undef OPERAND
#undef TRANSLATE
#undef INSTRUCTION
