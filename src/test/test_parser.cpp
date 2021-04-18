#include <assert.h>

#include "lang/parser.h"
#include "lang/tokenizer.h"
#include "test/test_parser.h"

namespace test {

void test_parser() {
	lang::Tokenizer toker("examples/nothing.s");
	lang::Parser parser;
	parser.build_from(toker);
	parser.print();
}

}
