#ifndef MACHINE_H
#define MACHINE_H

#include <stddef.h>

#include "cpu/cpu.h"
#include "memory/memory.h"

namespace machine {

class Machine : public cpu::CPU, public memory::Memory {
private:
	size_t setup(const char *filename);
public:
	Machine(size_t memory_size, size_t n_registers);
	void run(const char *filename);
};

}

#endif // MACHINE_H
