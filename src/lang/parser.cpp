#include <stddef.h>
#include <iostream>

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
		pair::Pair<	// section
			Token,	// name of section
			pair::Pair<
				vector::Vector<	// list of labels
					pair::Pair<
						Token,	// name of label
						size_t	// number of instruction
					>
				>,
				vector::Vector<	// list of instruction
					pair::Pair<
						Token,	// name of instruction
						vector::Vector<Token> // arguments of instruction
					>
				>
			>		
		> new_section;

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

void Parser::build_from(Tokenizer &toker) {
	this->clean();
	toker.next_line();
	while (!this->parse_section(toker));
}

void Parser::clean() {
	ast.clean();
}

// return the number of instructions written to memory
size_t Parser::write_to(memory::Memory &mem) const {
	size_t written = 0;
	return written;
}

void Parser::print() const {
	// iterate sections
	for (auto section = this->ast.cbegin();
			section != this->ast.cend(); ++section) {
		std::cout << "section " << section->left().cbegin() << std::endl;

		// iterate labels
		for (size_t i = 0; i < section->right().left().size(); i++) {
			std::cout << "\tlabel " <<
				section->right().left()[i].left().cbegin() <<
				": " << section->right().left()[i].right() <<
				std::endl;
		}

		// iterate instruction
		for (size_t i = 0; i < section->right().right().size(); i++) {
			std::cout << "\t" << section->right().right()[i].left().cbegin();
			std:: cout << "\t";
			for (size_t j = 0; j < section->right().right()[i].right().size();
					j++) {
				std::cout << section->right().right()[i].right()[j].cbegin();
				if (j + 1 != section->right().right()[i].right().size()) {
					std::cout << ", ";
				}
			}
			std::cout << std::endl;
		}
	}
}

}
