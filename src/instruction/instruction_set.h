#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

#include <assert.h>
#include <iostream>
#include <stdbool.h>
#include <stddef.h>
#include <stdexcept>

#include "instruction/instruction.h"
#include "lang/token.h"
#include "vector/vector.hpp"
#include "cpu/register.h"

#define INSTRUCTION(_name) \
	class _name : public Instruction { \
		public: \
			_name(size_t opcode, vector::Vector<Operand> &operands) : \
					Instruction(opcode, operands) {} \
			void operator()(vector::Vector<Register> &registers); \
	}


namespace inst {

const size_t exit_opcode(1);

INSTRUCTION(  exit_inst);
INSTRUCTION(  move_inst);
INSTRUCTION(   add_inst);
INSTRUCTION(   sub_inst);
INSTRUCTION(  mult_inst);
INSTRUCTION(   div_inst);
INSTRUCTION(   shl_inst);
INSTRUCTION(   shr_inst);
INSTRUCTION(   and_inst);
INSTRUCTION(    or_inst);
INSTRUCTION(   xor_inst);
INSTRUCTION(   not_inst);
INSTRUCTION( print_inst);
INSTRUCTION(  jmpz_inst);
INSTRUCTION(  relz_inst);
INSTRUCTION( jmpnz_inst);
INSTRUCTION( relnz_inst);
INSTRUCTION(  swap_inst);
INSTRUCTION(  push_inst);
INSTRUCTION(   pop_inst);
INSTRUCTION(  call_inst);
INSTRUCTION(   ret_inst);

Instruction *build_instruction(const lang::Token &name,
		vector::Vector<Operand> &operands);

}

#undef INSTRUCTION

#endif // INSTRUCTION_SET_H
