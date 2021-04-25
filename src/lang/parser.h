#ifndef PARSER_H
#define PARSER_H

#include <exception>
#include <stddef.h>
#include <sstream>
#include <string.h>

#include "lang/token.h"
#include "lang/tokenizer.h"
#include "memory/memory.h"
#include "pair/pair.hpp"
#include "vector/vector.hpp"

namespace lang {

// Section(name):
//     Instruction(name, operands...)
//     ...
//
// Label(name):
//     Instruction(name, operands...)
//     ...

typedef pair::Pair<
	Token,	// name of instruction
	vector::Vector<Token> // arguments of instruction
> Instruction;

typedef pair::Pair<
	Token, // name of label
	size_t // nth instruction in section
> Label;

typedef pair::Pair<
	Token,	// name of section
	pair::Pair<
		vector::Vector<	// list of labels
			Label
		>,
		vector::Vector<	// list of instruction
			Instruction
		>
	>		
> Section;

// ast is a list of sections
typedef vector::Vector<Section> AST;

class syntax_error : public std::exception {
private:
	char *str;
public:
	syntax_error(Tokenizer::Line &line, const char *msg) : std::exception() {
		std::ostringstream oss;
		oss << "Syntax error on line " << line.left() << " :\n";

		// add the line of code
		for (size_t i = 0; i < line.right().size(); i++) {
			for (char &c : line.right()[i]) {
				if (c == '\0') {
					oss << ' ';
				} else {
					oss << c;
				}
			}
		}

		// add message
		oss << "\n\t" << msg;
		this->str = new char[oss.str().size() + 1];
		strncpy(this->str,
				oss.str().c_str(),
				oss.str().size());
	}
	const char *what() const throw() {
		return this->str;
	}
	virtual ~syntax_error() {
		delete[] this->str;
	}
};

class Parser {
private:
	AST ast;
	bool parse_instruction(Tokenizer &toker);
	bool parse_section(Tokenizer &toker);
public:
	void build_from(Tokenizer &toker);
	void clean();
	size_t write_to(memory::Memory &mem) const;
	void print() const;
};

}

#endif // PARSER_H
