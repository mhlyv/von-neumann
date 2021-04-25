#include <iostream>
#include <stddef.h>
#include <string.h>

#include "lang/token.h"

namespace lang {

Token::Token() : vector::Vector<char>() {
}

Token::Token(const char *str) : vector::Vector<char>(strlen(str) + 1) {
	for (size_t i = 0; i < this->size(); i++) {
		this->operator[](i) = str[i];
	}
}

bool Token::operator==(const char *str) const {
	if (this->size() != strlen(str) + 1) {
		return false;
	} else {
		for (size_t i = 0; i < this->size(); i++) {
			if (this->operator[](i) != str[i]) {
				return false;
			}
		}
	}

	return true;
}

bool Token::operator!=(const char *str) const {
	return !(*this == str);
}

bool Token::operator==(const Token &tok) const {
	if (this->size() != tok.size()) {
		return false;
	} else {
		for (size_t i = 0; i < this->size(); i++) {
			if (this->operator[](i) != tok[i]) {
				return false;
			}
		}
	}

	return true;
}

bool Token::operator!=(const Token &tok) const {
	return !(*this == tok);
}

std::ostream &operator<<(std::ostream &os, const Token &tok) {
	return os << tok.cbegin();
}

}
