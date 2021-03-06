#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string.h>

#include "vector/vector.hpp"

namespace lang {

// class to store a string
class Token : public vector::Vector<char> {
public:
	Token();
	Token(const char *str);
	bool operator==(const char *str) const;
	bool operator!=(const char *str) const;
	bool operator==(const Token &tok) const;
	bool operator!=(const Token &tok) const;
};

std::ostream &operator<<(std::ostream &os, const Token &tok);

}

#endif // TOKEN_H
