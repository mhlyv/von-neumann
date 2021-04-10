#ifndef __CPU_H__
#define __CPU_H__

#include <stddef.h>

#include "control_unit/control_unit.h"
#include "memory/memory.h"
#include "processing_unit/processing_unit.h"

namespace cpu {

class CPU {
private:
	cu::ControlUnit cu;
	pu::ProcessingUnit pu;
public:
	CPU(memory::Data &pc, size_t regs);
	size_t perform_cycle(memory::Memory &mem);
	void run(memory::Memory &mem);
};

}

#endif // __CPU_H__
