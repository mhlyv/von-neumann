#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stddef.h>

#include "cpu/register.h"
#include "memory/memory.h"
#include "pair/pair.hpp"
#include "vector/vector.hpp"

namespace inst {

// an argument of an instruction
// it can either mark a register (then the value means the nth register)
// or it can be a literal value
class Operand : public pair::Pair<memory::Data *, bool> {
public:
	Operand();
	Operand(memory::Data *data, bool is_reg);
	bool is_register() const;
	Operand &operator=(memory::Data &d);
	operator memory::Data::data_t&();
	operator memory::Data::data_t() const;
	operator memory::Data*();
	operator memory::Data&();
	operator memory::Data() const;
};

// an instruction that can be stored in Memory
// it has a list of operands
// for evaluation (using the operator()) the registers need to be passed as
// argument
class Instruction : public memory::Data {
protected:
	// the boolean is true if the operand is a register, otherwise false
	vector::Vector<Operand> operands;
public:
	Instruction(size_t opcode, vector::Vector<Operand> &operands);
	size_t n_operands() const;
	Operand &operator[](size_t i);
	void write(memory::Data *data);
	virtual void operator()(vector::Vector<Register> &registers);
	virtual ~Instruction();
};

}

#endif // INSTRUCTION_H
