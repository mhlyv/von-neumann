#include <assert.h>
#include <stddef.h>

#include "instruction/instruction.h"
#include "memory/memory.h"
#include "vector/vector.hpp"

namespace test {

void test_memory_constructor() {
	memory::Memory m = 1000;
	for (size_t i = 0; i < 1000; i++) {
		m[i];
	}
}

void test_memory_storage() {
	memory::Memory m = 1000;
	memory::Data *dp = new memory::Data(42);
	memory::Data *op = new memory::Data(1234);
	vector::Vector<memory::Data *> operands;

	operands.append(op);
	inst::Instruction *inst = new inst::Instruction(13, operands);

	for (size_t i = 0; i < 1000; i++) {
		if (i % 2 == 0) {
			m[i] = (memory::Data *)inst;
		} else {
			m[i] = dp;
		}
	}

	for (size_t i = 0; i < 1000; i++) {
		if (i % 2 == 0) {
			inst::Instruction *tmp = (inst::Instruction *)m[i];
			assert(tmp->read() == 13);
			assert(tmp->n_operands() == inst->n_operands());
			for (size_t j = 0; j < operands.size(); j++) {
				assert((*tmp)[j].read() == operands[j]->read());
			}
			(*tmp)();
		} else {
			assert(m[i]->read() == dp->read());
		}
	}

	delete inst;
	delete op;
	delete dp;
}

void test_memory() {
	test_memory_constructor();
	test_memory_storage();
}

}
