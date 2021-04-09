#include <stddef.h>

#include "instruction/instruction.h"
#include "processing_unit/processing_unit.h"
#include "vector/vector.hpp"

namespace pu {

ProcessingUnit::ProcessingUnit(size_t n) : registers(n) {
}

void ProcessingUnit::eval(inst::Instruction &inst) {
	inst(this->registers);
}

ProcessingUnit::~ProcessingUnit() {
}

}
