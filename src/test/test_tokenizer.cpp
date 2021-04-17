#include <assert.h>
#include <stddef.h>
#include <iostream>

#include "lang/token.h"
#include "lang/tokenizer.h"
#include "test/test_tokenizer.h"
#include "vector/vector.hpp"

namespace test {

void test_tokenizer() {
	lang::Tokenizer toker("src/test/tokenizer_test.txt");
	vector::Vector<lang::Token> line;

	// this is based on the input file

	for (int i = 0; i < 4; i++) {
		line = toker.next_line();
		assert(line.size() == 4);
		assert(line[0] == "this");
		assert(line[1] == "is");
		assert(line[2] == "an");
		assert(line[3] == "example");
	}

	for (int i = 0; i < 10; i++) {
		line = toker.next_line();
		assert(line.size() == 0);
	}
}

}
