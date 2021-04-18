#include <ctype.h>
#include <fstream>
#include <stdexcept>

#include "lang/token.h"
#include "lang/tokenizer.h"
#include "pair/pair.hpp"
#include "vector/vector.hpp"

namespace lang {

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

Tokenizer::Tokenizer(const char *filename) : ifs(filename), line() {
	if (!this->ifs.is_open()) {
		throw std::invalid_argument("Couldn't open file!");
	}
	this->line.left() = 0;
}

Token Tokenizer::next_token() {
	char in;
	size_t read = 0;

	if (!this->ifs.is_open()) {
		return Token();
	}

	this->skip_comment();

	if (this->important(this->ifs.peek())) {
		this->ifs.get(in);
		this->buffer[read] = in;
		read++;
	} else {
		while (!isspace(this->ifs.peek()) &&
				!this->important(this->ifs.peek())) {
			this->ifs.get(in);
			this->buffer[read] = in;
			read++;
		}
	}

	this->buffer[read] = '\0';
	return Token(this->buffer);
}

Tokenizer::Line &Tokenizer::next_line() {
	Token tok;

	if (!this->ifs.is_open()) {
		this->line.left() = 0;
		this->line.right().clean();
		return this->line;
	}

	do {
		this->line.left()++;
		this->line.right().clean();
		tok = this->next_token();

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
