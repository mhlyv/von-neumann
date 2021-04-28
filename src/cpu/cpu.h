#ifndef CPU_H
#define CPU_H

#include <stddef.h>

#include "cpu/register.h"
#include "memory/memory.h"
#include "vector/vector.hpp"

namespace cpu {

class CPU {
private:
	// registers:
	// [0]: program counter
	// [1]: stack pointer
	// ...: general purpose
	vector::Vector<Register> registers;
public:
	CPU(size_t regs);
	void set_sp(Register sp);
	size_t perform_cycle(memory::Memory &mem);
	void run(memory::Memory &mem);
};

}

#endif // CPU_H
