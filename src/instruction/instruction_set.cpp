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

// make a new instruction
#define TRANSLATE(_name, _op_code, _inst) \
	do { \
		if (name == _name) { \
			return new _inst(_op_code, operands); \
		} \
	} while (0)

// put the value of the _nth operand in _name (handle register/literal)
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

// free all values passed as operands
INSTRUCTION(exit_inst) {
	(void)registers;
	for (Operand &o : this->operands) {
		delete o.left();
	}
}

// copy the value of the second operand to the first operand
INSTRUCTION(move_inst) {
	memory::Data *dest;
	memory::Data *src;

	assert(this->operands.size() == 2);

	OPERAND(dest, 0);
	OPERAND(src, 1);

	*dest = *src;
}

// add the value of all operands to the first operands (except itself)
INSTRUCTION(add_inst) {
	memory::Data *dest;
	memory::Data *src;

	OPERAND(dest, 0);

	for (size_t i = 1; i < this->operands.size(); i++) {
		OPERAND(src, i);
		*dest += *src;
	}
}

// substract the value of all operands from the first operands (except itself)
INSTRUCTION(sub_inst) {
	memory::Data *dest;
	memory::Data *src;

	OPERAND(dest, 0);

	for (size_t i = 1; i < this->operands.size(); i++) {
		OPERAND(src, i);
		*dest -= *src;
	}
}

// multiply the value of the first operand with all operands (except itself)
INSTRUCTION(mult_inst) {
	memory::Data *dest;
	memory::Data *src;

	OPERAND(dest, 0);

	for (size_t i = 1; i < this->operands.size(); i++) {
		OPERAND(src, i);
		*dest *= *src;
	}
}

// divide the value of the first operand with all operands (except itself)
INSTRUCTION(div_inst) {
	memory::Data *dest;
	memory::Data *src;

	OPERAND(dest, 0);

	for (size_t i = 1; i < this->operands.size(); i++) {
		OPERAND(src, i);
		*dest /= *src;
	}
}

// shift the bits of the value of the first operand to the left with the value
// of the second operand (inserting 0-s at the end)
INSTRUCTION(shl_inst) {
	memory::Data *dest;
	memory::Data *src;

	assert(this->operands.size() == 2);

	OPERAND(dest, 0);
	OPERAND(src, 1);

	// if the shift value is larger than the number of bits in the value to
	// be shifted it causes undefined behavior
	// thank you c++ compiler, very cool
	if (sizeof(memory::Data::data_t) > *src) {
		*dest <<= *src;
	} else {
		*dest = 0;
	}
}

// shift the bits of the value of the first operand to the right with the value
// of the second operand (inserting 0-s at the front)
INSTRUCTION(shr_inst) {
	memory::Data *dest;
	memory::Data *src;

	assert(this->operands.size() == 2);

	OPERAND(dest, 0);
	OPERAND(src, 1);

	// if the shift value is larger than the number of bits in the value to
	// be shifted it causes undefined behavior
	// thank you c++ compiler, very cool
	if (sizeof(memory::Data::data_t) > *src) {
		*dest >>= *src;
	} else {
		*dest = 0;
	}
}

// perform logical `and` between the values of the operands and put the result
// in the first operand
INSTRUCTION(and_inst) {
	memory::Data *dest;
	memory::Data *src;

	OPERAND(dest, 0);

	for (size_t i = 1; i < this->operands.size(); i++) {
		OPERAND(src, i);
		*dest &= *src;
	}
}

// perform logical `or` between the values of the operands and put the result
// in the first operand
INSTRUCTION(or_inst) {
	memory::Data *dest;
	memory::Data *src;

	OPERAND(dest, 0);

	for (size_t i = 1; i < this->operands.size(); i++) {
		OPERAND(src, i);
		*dest |= *src;
	}
}

// perform logical `xor` between the values of the operands and put the result
// in the first operand
INSTRUCTION(xor_inst) {
	memory::Data *dest;
	memory::Data *src;

	OPERAND(dest, 0);

	for (size_t i = 1; i < this->operands.size(); i++) {
		OPERAND(src, i);
		*dest ^= *src;
	}
}

// perform logical `not` on the value of the first operand
INSTRUCTION(not_inst) {
	memory::Data *dest;
	assert(this->operands.size() == 1);
	OPERAND(dest, 0);
	*dest = ~*dest;
}

// print the value of the operands, divided by a space
INSTRUCTION(print_inst) {
	memory::Data *src;
	for (size_t i = 0; i < this->operands.size(); i++) {
		OPERAND(src, i);
		std::cout << (memory::Data::data_t)*src << " ";
	}
	std::cout << std::endl;
}

// if the value of the first operand is 0, set the value of the program counter
// register to the value of the second operand
INSTRUCTION(jmpz_inst) {
	assert(operands.size() == 2);
	memory::Data *src;
	OPERAND(src, 0);

	if (*src == 0) {
		registers[0] = *(operands[1].left());
	}
}

// if the value of the first operand is 0, add the value of the second operand
// to the value of the program counter register and comensate for back jump
INSTRUCTION(relz_inst) {
	assert(operands.size() == 2);
	memory::Data *src;
	OPERAND(src, 0);

	// fix back jumps, compensate for the cpu incrementing the pc
	int64_t signed_val = (int64_t)*(operands[1].left());
	if (signed_val < 0) {
		signed_val--;
	}

	if (*src == 0) {
		registers[0] += (memory::Data::data_t)signed_val;
	}
}

// if the value of the first operand is not 0, set the value of the program
// counter register to the value of the second operand
INSTRUCTION(jmpnz_inst) {
	assert(operands.size() == 2);
	memory::Data *src;
	OPERAND(src, 0);

	if (*src != 0) {
		registers[0] = *(operands[1].left());
	}
}

// if the value of the first operand is not 0, add the value of the second
// operand to the value of the program counter register and compensate for
// back jumps
INSTRUCTION(relnz_inst) {
	assert(operands.size() == 2);
	memory::Data *src;
	OPERAND(src, 0);

	// fix back jumps, compensate for the cpu incrementing the pc
	int64_t signed_val = (int64_t)*(operands[1].left());
	if (signed_val < 0) {
		signed_val--;
	}

	if (*src != 0) {
		registers[0] += (memory::Data::data_t)signed_val;
	}
}

// swap the value of the first operand with the value of the second argument
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

// push the value of the first operand on the stack
INSTRUCTION(push_inst) {
	assert(this->operands.size() == 1);
	memory::Data *src;
	OPERAND(src, 0);
	PUSH(*src);
}

// pop a value from the stack and copy it into the first operand
INSTRUCTION(pop_inst) {
	assert(this->operands.size() == 1);
	memory::Data *dest;
	OPERAND(dest, 0);
	POP(*dest);
}

// call a subroutine marked by the first operand
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

// return from subroutine
INSTRUCTION(ret_inst) {
	assert(this->operands.size() == 0);
	// jump to position of next instruction
	POP(registers[0]);
}

// build an instruction from based on the name of the instruction
// returns a pointer to a dynamically allocated instruction object
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
	TRANSLATE( "relz",          15,  relz_inst);
	TRANSLATE("jmpnz",          16, jmpnz_inst);
	TRANSLATE("relnz",          17, relnz_inst);
	TRANSLATE( "swap",          18,  swap_inst);
	TRANSLATE( "push",          19,  push_inst);
	TRANSLATE(  "pop",          20,   pop_inst);
	TRANSLATE( "call",          21,	 call_inst);
	TRANSLATE(  "ret",          22,   ret_inst);

	throw std::invalid_argument("No such instruction");
	return nullptr; // unreachable
}

}

#undef POP
#undef PUSH
#undef OPERAND
#undef TRANSLATE
#undef INSTRUCTION
