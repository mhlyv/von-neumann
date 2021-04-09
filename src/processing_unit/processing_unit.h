#ifndef __PROCESSING_UNIT_H__
#define __PROCESSING_UNIT_H__

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

#endif // __PROCESSING_UNIT_H__
