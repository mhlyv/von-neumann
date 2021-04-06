#include <iostream>

#include "test/test_data.h"
#include "test/test_memory.h"
#include "test/test_vector.h"

int main() {
	std::cout << "There should be no output (except this)." << std::endl;
	test::test_vector();
	test::test_data();
	test::test_memory();
}
