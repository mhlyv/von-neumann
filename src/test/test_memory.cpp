#include <assert.h>
#include <stddef.h>

#include "instruction/instruction.h"
#include "memory/memory.h"
#include "pair/pair.hpp"
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
	inst::Operand *operand = new inst::Operand(new memory::Data(1234), false);
	vector::Vector<inst::Operand *> operands;

	operands.append(operand);
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
				assert((*tmp)[j].left()->read() == operands[j]->left()->read());
				assert((*tmp)[j] == *operands[j]);
			}
			(*tmp)();
		} else {
			assert(m[i]->read() == dp->read());
		}
	}

	delete operand->left();
	delete operand;
	delete inst;
	delete dp;
}

void test_memory() {
	test_memory_constructor();
	test_memory_storage();
}

}
