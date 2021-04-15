#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "memory/memory.h"
#include "instruction/instruction.h"
#include "processing_unit/processing_unit.h"
#include "processing_unit/register.h"
#include "test/test_processing_unit.h"
#include "vector/vector.hpp"

#define INSTRUCTION(name) \
	class name : public inst::Instruction { \
		public: \
			name(size_t opcode, vector::Vector<inst::Operand> &operands) : \
					Instruction(opcode, operands) {} \
			void operator()(vector::Vector<Register> &registers); \
	}; \
	void name::operator()(vector::Vector<Register> &registers)

namespace test {

namespace processing_unit_constructor {

size_t regs = 42;

INSTRUCTION(test_inst) {
	memory::Data::data_t val;
	for (size_t i = 0; i < regs; i++) {
		try {
			val = registers[i].read();
		} catch (...) {
			assert(0 && "not enough registers");
		}
	}

	try {
		val = registers[regs].read();
		assert(0 && "too many registers");
	} catch (...) {
	}

	(void)val;
}

void test() {
	pu::ProcessingUnit pu(regs);
	vector::Vector<inst::Operand> vec;
	test_inst i(0, vec);
	pu.eval(i);
}

}

namespace processing_unit_registers {

size_t regs = 10000;

INSTRUCTION(set) {
	for (size_t i = 0; i < regs; i++) {
		registers[i] = i * i;
	}
}

INSTRUCTION(test_set) {
	for (size_t i = 0; i < regs; i++) {
		assert(registers[i] == i * i);
	}
}

void test() {
	pu::ProcessingUnit pu(regs);
	vector::Vector<inst::Operand> vec;

	set s(0, vec);
	pu.eval(s);
	test_set t(0, vec);
	pu.eval(t);
}

}

void test_processing_unit() {
	processing_unit_constructor::test();
	processing_unit_registers::test();
}

}

#undef INSTRUCTION
