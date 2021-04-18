#ifndef PARSER_H
#define PARSER_H

#include <exception>
#include <stddef.h>
#include <sstream>

#include "lang/token.h"
#include "lang/tokenizer.h"
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

typedef vector::Vector<
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
	>
> AST;

class syntax_error : public std::exception {
private:
	std::ostringstream oss;
public:
	syntax_error(Tokenizer::Line &line, const char *msg) : std::exception() {
			this->oss << "Syntax error on line " << line.left() << " :\n";

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
	}
	const char *what() const throw() {
		return this->oss.str().c_str();
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
	void print() const;
};

}

#endif // PARSER_H
