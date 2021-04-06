#include <assert.h>
#include <stdint.h>

#include "memory/memory.h"

namespace test {

void test_data_default_constructor() {
	memory::Data d;
	assert(d.read() == 0);
}

void test_data_constructor() {
	memory::Data d = UINT64_MAX;
	assert(d.read() == UINT64_MAX);
}

void test_data_write() {
	memory::Data d = 13;
	memory::Data d1 = 31;
	assert(d.read() == 13);
	d.write(&d1);
	assert(d.read() == d1.read());
}

void test_data_clone() {
	memory::Data d = 42;
	memory::Data *dp = d.clone();
	assert(d.read() == dp->read());
	delete dp;
}

void test_data() {
	test_data_default_constructor();
	test_data_constructor();
	test_data_write();
	test_data_clone();
}

}
