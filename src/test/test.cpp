#include <iostream>

#include "test/test_data.h"
#include "test/test_memory.h"
#include "test/test_pair.h"
#include "test/test_processing_unit.h"
#include "test/test_vector.h"

int main() {
	std::cout << "There should be no output (except this)." << std::endl;
	test::test_vector();
	test::test_data();
	test::test_memory();
	test::test_pair();
	test::test_processing_unit();
}
