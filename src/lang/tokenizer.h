#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <fstream>
#include <stddef.h>

#include "lang/token.h"
#include "vector/vector.hpp"

namespace lang {

class Tokenizer {
private:
	std::ifstream ifs;
	vector::Vector<Token> line;
	static const size_t max_token_size = 64;
	size_t nth_line;
	bool important(char c) const;
	char buffer[max_token_size];
	bool skip_whitespace();
	bool skip_comment();
public:
	Tokenizer(const char *filename);
	Token next_token();
	vector::Vector<Token> &next_line();
	~Tokenizer();
};

}

#endif // TOKENIZER_H
