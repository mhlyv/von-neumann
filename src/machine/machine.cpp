#include <stddef.h>

#include "cpu/cpu.h"
#include "memory/memory.h"
#include "machine/machine.h"
#include "lang/tokenizer.h"
#include "lang/parser.h"

namespace machine {

// create cpu and memory with given parameters
Machine::Machine(size_t memory_size, size_t n_registers) :
	cpu::CPU(n_registers), memory::Memory(memory_size) {
}

// read program from file
// return number of instructions written to memory
size_t Machine::setup(const char *filename) {
	lang::Tokenizer toker(filename);
	lang::Parser parser;

	// create and write instructions to memory
	parser.build_from(toker);
	size_t n_instructions = parser.write_to((memory::Memory &)*this);

	// set stack pointer
	memory::Data **sp = &this->operator[](0);
	for (size_t i = 0; i < n_instructions - 1; i++) {
		sp++;
	}
	uint64_t d = reinterpret_cast<uint64_t>(sp);
	this->set_sp(d);

	return n_instructions;
}

// read and execute program from file
void Machine::run(const char *filename) {
	size_t instructions = this->setup(filename);
	this->cpu::CPU::run((memory::Memory &)*this);
	for (size_t i = 0; i < instructions; i++) {
		delete this->operator[](i);
	}
}

}
