#include <assert.h>
#include <stddef.h>
#include <iostream>

#include "lang/token.h"
#include "lang/tokenizer.h"
#include "pair/pair.hpp"
#include "test/test_tokenizer.h"
#include "vector/vector.hpp"

namespace test {

void test_tokenizer() {
	lang::Tokenizer toker("src/test/tokenizer_test.txt");
	lang::Tokenizer::Line line;

	// this is based on the input file

	for (int i = 0; i < 4; i++) {
		line = toker.next_line();
		assert(line.right().size() == 4);
		assert(line.right()[0] == "this");
		assert(line.right()[1] == "is");
		assert(line.right()[2] == "an");
		assert(line.right()[3] == "example");
	}

	for (int i = 0; i < 10; i++) {
		line = toker.next_line();
		assert(line.right().size() == 0);
	}
}

}
