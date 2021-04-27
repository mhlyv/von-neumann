#include <iostream>

#include "test/test_data.h"
#include "test/test_memory.h"
#include "test/test_pair.h"
#include "test/test_vector.h"
#include "test/test_token.h"
#include "test/test_tokenizer.h"
#include "test/test_parser.h"

int main() {
	std::cout << "There should be no output (except this)." << std::endl;
	test::test_vector();
	test::test_data();
	test::test_memory();
	test::test_pair();
	test::test_token();
	test::test_tokenizer();
	test::test_parser();
}
