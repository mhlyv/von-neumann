#include <assert.h>
#include <stddef.h>
#include <iostream>
#include <stdexcept>

#include "vector/vector.hpp"
#include "test/test_vector.h"

namespace test {

void test_vector_empty() {
	vector::Vector<int> v;
	assert(v.size() == 0);

	try {
		v[0];
		assert(0 && "Should have thrown!");
	} catch (const std::out_of_range &) {
	}
}

void test_vector_elements() {
	vector::Vector<int> v;
	for (int i = 0; i < 100; i++) {
		v.append(i);
	}
	assert(v.size() == 100);
	for (int i = 0; i < 100; i++) {
		assert(v[i] == i);
	}
}

void test_vector_clean() {
	vector::Vector<int> v;
	for (int i = 0; i < 100; i++) {
		v.append(0);
	}
	v.clean();
	v.clean();
	assert(v.size() == 0);

	for (int i = 0; i < 100; i++) {
		try {
			v[i];
			assert(0 && "Should have thrown!");
		} catch (const std::out_of_range &) {
		}
	}
}

void test_vector_copy() {
	vector::Vector<int> v;
	for (int i = 0; i < 100; i++) {
		v.append(i);
	}
	vector::Vector<int> c = v;
	assert(c.size() == v.size());
	for (int i = 0; i < 100; i++) {
		assert(c[i] == v[i]);
	}
}

void test_vector_assign() {
	vector::Vector<int> v;
	for (int i = 0; i < 100; i++) {
		v.append(i);
	}
	vector::Vector<int> v1;
	v1.append(42);
	v = v1; // also check memory leaks
	for (size_t i = 0; i < v1.size(); i++) {
		assert(v[i] == v1[i]);
	}

	try {
		v[v1.size()];
		assert(0 && "Should have thrown!");
	} catch (const std::out_of_range &) {
	}
}

void test_vector() {
	test_vector_empty();
	test_vector_elements();
	test_vector_clean();
	test_vector_copy();
	test_vector_assign();
}

}
