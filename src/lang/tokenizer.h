#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <fstream>
#include <stddef.h>

#include "lang/token.h"
#include "pair/pair.hpp"
#include "vector/vector.hpp"

namespace lang {

class Tokenizer {
public:
	// (line_number, tokens[])
	typedef pair::Pair<size_t, vector::Vector<Token>> Line;
private:
	std::ifstream ifs;
	Line line;
	static const size_t max_token_size = 64;
	bool important(char c) const;
	char buffer[max_token_size];
	bool skip_whitespace();
	bool skip_comment();
public:
	Tokenizer(const char *filename);
	Token next_token();
	Line &next_line();
	~Tokenizer();
};

}

#endif // TOKENIZER_H
