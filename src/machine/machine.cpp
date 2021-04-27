#include <stddef.h>

#include "cpu/cpu.h"
#include "memory/memory.h"
#include "machine/machine.h"
#include "lang/tokenizer.h"
#include "lang/parser.h"

namespace machine {

Machine::Machine(size_t memory_size, size_t n_registers) :
	cpu::CPU(n_registers), memory::Memory(memory_size) {
}

size_t Machine::setup(const char *filename) {
	lang::Tokenizer toker(filename);
	lang::Parser parser;
	parser.build_from(toker);
	return parser.write_to((memory::Memory &)*this);
}

void Machine::run(const char *filename) {
	size_t instructions = this->setup(filename);
	this->cpu::CPU::run((memory::Memory &)*this);
	for (size_t i = 0; i < instructions; i++) {
		delete this->operator[](i);
	}
}

}
