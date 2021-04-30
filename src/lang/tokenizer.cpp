#include <ctype.h>
#include <fstream>
#include <stdexcept>

#include "lang/token.h"
#include "lang/tokenizer.h"
#include "pair/pair.hpp"
#include "vector/vector.hpp"

namespace lang {

// return true if the charecter is `important`
bool Tokenizer::important(char c) const {
	const char *chars = "\n:,;";
	while (*chars != '\0') {
		if (*chars == c) {
			return true;
		}
		chars++;
	}
	return false;
}

// remove leading whitespace from the input stream
// return true if any whitespace was skipped
bool Tokenizer::skip_whitespace() {
	char in;
	bool has_skipped = false;

	if (!this->ifs.is_open()) {
		return false;
	}

	// don't skip newlines
	while (this->ifs.peek() && isspace(this->ifs.peek()) &&
			!this->important(this->ifs.peek())) {
		this->ifs.get(in);
		has_skipped = true;
	}

	return has_skipped;
}

// skip comments from the input stream
// return true if any comments were skipped
bool Tokenizer::skip_comment() {
	char in;
	bool has_skipped = false;

	if (!this->ifs.is_open()) {
		return false;
	}

	this->skip_whitespace();
	
	if (this->ifs.peek() == ';') {
		has_skipped = true;
		// skip until end of line
		while (this->ifs.peek() && this->ifs.peek() != '\n') {
			this->ifs.get(in);
		}
	}

	return has_skipped;
}

// open file for reading
Tokenizer::Tokenizer(const char *filename) : ifs(filename), line() {
	if (!this->ifs.is_open()) {
		throw std::invalid_argument("Couldn't open file!");
	}
	this->line.left() = 0;
}

// read and return the next token from the input stream
Token Tokenizer::next_token() {
	char in;
	Token token;

	if (!this->ifs.is_open()) {
		return Token();
	}

	this->skip_comment();

	// if we reached an important character
	if (this->important(this->ifs.peek())) {
		this->ifs.get(in);
		token.append(in);
	} else {
		// read until reaching whitespace ir an important character
		while (!isspace(this->ifs.peek()) &&
				!this->important(this->ifs.peek())) {
			this->ifs.get(in);
			token.append(in);
		}
	}

	token.append('\0');
	return token;
}

// read and return the next line of tokens
Tokenizer::Line &Tokenizer::next_line() {
	Token tok;

	if (!this->ifs.is_open()) {
		this->line.left() = 0;
		this->line.right().clean();
		return this->line;
	}

	do {
		this->line.left()++; // increase the line number
		this->line.right().clean();
		tok = this->next_token();

		// read tokens until the end of the line
		while (tok != "\n") {
			this->line.right().append(tok);
			tok = this->next_token();
		}

		if (this->ifs.peek() == EOF) {
			this->ifs.close();
		}
		// skip 'empty' lines
	} while (this->line.right().size() == 0 && this->ifs.is_open());

	return this->line;
}

Tokenizer::Line &Tokenizer::get_line() {
	return this->line;
}

Tokenizer::~Tokenizer() {
	if (this->ifs.is_open()) {
		this->ifs.close();
	}
}

}
