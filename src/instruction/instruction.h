#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include <stddef.h>

#include "memory/memory.h"
#include "vector/vector.h"

namespace instruction {

class Instruction : public memory::Data {
private:
	vector::Vector<memory::Data *> operands;
public:
	Instruction(size_t opcode, const vector::Vector<memory::Data *> &operands);
	size_t n_operands() const;
	memory::Data &operator[](size_t i);
	void write(memory::Data *data);
	virtual void operator()();
	memory::Data *clone() const;
	virtual ~Instruction();
};

}

#endif // __INSTRUCTION_H__
