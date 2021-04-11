#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stddef.h>

#include "memory/memory.h"
#include "pair/pair.hpp"
#include "processing_unit/register.h"
#include "vector/vector.hpp"

namespace inst {

typedef pair::Pair<memory::Data *, bool> Operand;

class Instruction : public memory::Data {
protected:
	// the boolean is true if the operand is a register, otherwise false
	vector::Vector<Operand *> operands;
public:
	Instruction(size_t opcode, vector::Vector<Operand *> &operands);
	size_t n_operands() const;
	Operand &operator[](size_t i);
	void write(memory::Data *data);
	virtual void operator()(vector::Vector<Register> &registers);
	memory::Data *clone();
	virtual ~Instruction();
};

}

#endif // INSTRUCTION_H
