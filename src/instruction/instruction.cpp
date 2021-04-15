#include <stddef.h>
#include <stdexcept>

#include "instruction/instruction.h"
#include "memory/memory.h"
#include "pair/pair.hpp"
#include "processing_unit/register.h"
#include "vector/vector.hpp"

namespace inst {

Operand::Operand() : pair::Pair<memory::Data *, bool>() {
}

Operand::Operand(memory::Data *data, bool is_reg = false)
	: pair::Pair<memory::Data *, bool>(data, is_reg) {
}

bool Operand::is_register() const {
	return this->right();
}

Instruction::Instruction(size_t opcode,
		vector::Vector<Operand *> &operands) :
	memory::Data(opcode), operands(operands) {
}

size_t Instruction::n_operands() const {
	return this->operands.size();
}

Operand &Instruction::operator[](size_t i) {
	if (i >= this->operands.size()) {
		throw std::out_of_range("Index out of range");
	}

	return *(this->operands[i]);
}

void Instruction::write(memory::Data *data) {
	(Data &)*this = *data;
	Instruction *inst = (Instruction *)data;

	this->operands.clean();

	for (size_t i = 0; i < inst->n_operands(); i++) {
		this->operands.append(&(*inst)[i]);
	}
}

void Instruction::operator()(vector::Vector<Register> &registers) {
	// the default instruction does nothing
	(void)registers;
}

memory::Data *Instruction::clone() {
	return new Instruction(this->read(), this->operands);
}

Instruction::~Instruction() {
	this->operands.clean();
}

}
