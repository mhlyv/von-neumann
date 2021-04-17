#ifndef TOKEN_H
#define TOKEN_H

#include <string.h>
#include "vector/vector.hpp"

namespace lang {

class Token : public vector::Vector<char> {
public:
	Token();
	Token(const char *str);
	bool operator==(const char *str) const;
	bool operator!=(const char *str) const;
	bool operator==(const Token &tok) const;
	bool operator!=(const Token &tok) const;
};

}

#endif // TOKEN_H
