#ifndef PROCESSING_UNIT_H
#define PROCESSING_UNIT_H

#include <stddef.h>

#include "instruction/instruction.h"
#include "processing_unit/register.h"
#include "vector/vector.hpp"

namespace pu {

class ProcessingUnit {
private:
	vector::Vector<Register> registers;
public:
	ProcessingUnit(size_t n);
	void eval(inst::Instruction &inst);
	~ProcessingUnit();
};

}

#endif // PROCESSING_UNIT_H
