#include <assert.h>
#include <iostream>
#include <sstream>
#include <stddef.h>
#include <stdexcept>

#include "instruction/instruction.h"
#include "instruction/instruction_set.h"
#include "lang/parser.h"
#include "lang/token.h"
#include "lang/tokenizer.h"
#include "memory/memory.h"
#include "pair/pair.hpp"
#include "vector/vector.hpp"

namespace lang {

// return if the token stream ended, or if the line is a section
bool Parser::parse_instruction(Tokenizer &toker) {
	Tokenizer::Line &line = toker.next_line();
	if (line.right().size() == 0 || line.right()[0] == "section") {
		return true;
	}

	// check if the line is a label
	if (line.right().size() == 2 && line.right()[1] == ":") {
		pair::Pair<Token, size_t> label(
			line.right()[0],
			this->ast[this->ast.size() - 1]
				.right()
				.right()
				.size()
		);
		this->ast[this->ast.size() - 1]
			.right()
			.left()
			.append(label);
		return false;
	}

	pair::Pair<Token, vector::Vector<Token>> new_instruction;
	new_instruction.left() = line.right()[0];

	// if the instruction does not have arguments
	if (line.right().size() == 1) {
		this->ast[this->ast.size() - 1]
			.right()
			.right()
			.append(new_instruction);
		return false;
	}

	if (line.right()[1] == ",") {
		throw syntax_error(line,
				"token expected after instruction name, found: `,`");
	}

	for (size_t i = 1; i < line.right().size(); i++) {
		if (line.right()[i] == "," && i == line.right().size() - 1) {
			throw syntax_error(line, "token expected after `,`");
		} else if (line.right()[i] == "," && i < line.right().size() &&
				line.right()[i + 1] == ",") {
			throw syntax_error(line, "token expected after `,`, found: `,`");
		} else if (i & 1) {
			new_instruction
				.right()
				.append(line.right()[i]);
		}
	}

	this->ast[this->ast.size() - 1]
		.right()
		.right()
		.append(new_instruction);

	return false;
}

// return if the token stream ended
bool Parser::parse_section(Tokenizer &toker) {
	Tokenizer::Line &line = toker.get_line();
	if (line.right().size() == 0) {
		return true;
	}

	if (line.right()[0] != "section") {
		throw syntax_error(line, "a section was expected");
	} else if (line.right().size() != 2) {
		throw syntax_error(line, "expected syntax: `section <section name>`");
	} else {
		Section new_section;

		new_section.left() = Token(line.right()[1]);

		this->ast.append(new_section);
	}

	while (!parse_instruction(toker));
	line = toker.get_line();
	if (line.right().size() == 0) {
		return true;
	}

	return false;
}

memory::Data *Parser::allocate(size_t data) {
	memory::Data *d = new memory::Data(data);
	this->allocated.append(d);
	return d;
}

void Parser::build_from(Tokenizer &toker) {
	this->clean();
	toker.next_line();
	while (!this->parse_section(toker));
}

void Parser::clean() {
	ast.clean();
}

inst::Instruction *Parser::build_instruction(
		const Section &section, size_t nth) {
	const Instruction &inst = section.right().right()[nth];
	vector::Vector<inst::Operand> operands;
	inst::Operand operand;
	const Token &name = inst.left();

	for (const Token *tok = inst.right().cbegin();
			tok != inst.right().cend(); ++tok) {
		bool found = false;
		// check if token is a label
		for (const Label *label = section.right().left().cbegin();
				!found && label != section.right().left().cend(); ++label) {
			if (*tok == label->left()) {
				found = true;
				operand = inst::Operand(this->allocate(label->right()), false);
				operands.append(operand);
			}
		}
		
		// check if token is a register
		if (!found && (*tok)[0] == 'r') {
			found = true;
			std::stringstream ss(tok->cbegin() + 1);
			size_t reg;
			if (!(ss >> reg)) {
				throw std::invalid_argument(
					"something went wrong: registers should be `r<regnum>`");
			}
			operand = inst::Operand(this->allocate(reg), true);
			operands.append(operand);
		}

		// otherwise it should be a number literal
		if (!found) {
			std::stringstream ss(tok->cbegin());
			size_t literal;
			if (!(ss >> literal)) {
				throw std::invalid_argument(
					"something went wrong: expected a number literal");
			}

			// might not be decimal
			if (literal == 0 && tok->cbegin()[0] == '0' && tok->size() > 2) {
				if (tok->cbegin()[1] == 'x') {
					literal = std::stoi(tok->cbegin()+2, 0, 16);
				} else if (tok->cbegin()[1] == 'b') {
					literal = std::stoi(tok->cbegin()+2, 0, 2);
				}
			}
			operand = inst::Operand(this->allocate(literal), false);
			operands.append(operand);
		}
	}

	return inst::build_instruction(name, operands);
}

// return the number of instructions written to memory
size_t Parser::write_to(memory::Memory &mem) {
	size_t written = 0;
	const Section *text = nullptr;
	vector::Vector<size_t> exits;

	for (const Section *section = this->ast.cbegin();
			section != this->ast.cend(); ++section) {
		if (section->left() == ".text") {
			text = section;
			break;
		}
	}

	if (text == nullptr) {
		throw std::invalid_argument("No `.text` section was found");
	}

	for (const Instruction *inst = text->right().right().cbegin();
			inst != text->right().right().cend(); ++inst) {
		assert(mem[written] == nullptr);
		mem[written] = this->build_instruction(*text, written);
		if (mem[written]->read() == inst::exit_opcode) {
			exits.append(written);
		}
		written++;
	}

	if (exits.size() == 0) {
		throw std::invalid_argument("program doesn't have `exit`");
	}

	// build exits to free allocations
	vector::Vector<inst::Operand> exit_operands;
	for (memory::Data *d : this->allocated) {
		inst::Operand op(d, false);
		exit_operands.append(op);
	}
	Token exit_token("exit");
	for (size_t i = 0; i < exits.size(); i++) {
		delete mem[exits[i]];
		mem[exits[i]] = inst::build_instruction(exit_token, exit_operands);
	}

	return written;
}

void Parser::print() const {
	// iterate sections
	for (const Section *section = this->ast.cbegin();
			section != this->ast.cend(); ++section) {
		std::cout << "section " << section->left() << std::endl;

		for (const Label *label = section->right().left().cbegin();
				label != section->right().left().cend(); ++label) {
			std::cout << "\tlabel " << label->left() <<
				": " << label->right() << std::endl;
		}

		for (const Instruction *inst = section->right().right().cbegin();
				inst != section->right().right().cend(); ++inst) {
			std::cout << "\t" << inst->left() << "\t";

			for (size_t i = 0; i < inst->right().size(); i++) {
				std::cout << inst->right()[i];
				if (i + 1 != inst->right().size()) {
					std::cout << ", ";
				}
			}

		 	std::cout << std::endl;
		}
	}
}

}
