#include <assert.h>
#include <iostream>

#include "pair/pair.hpp"
#include "test/test_pair.h"

namespace test {

void test_pair_constructor() {
	int i = 42;
	const char *str = "Hello, World!\n";
	pair::Pair<int, const char *> p(i, str);
	assert(p.left() == i);
	assert(p.right() == str);
}

void test_pair_assign() {
	int i = 42;
	const char *str = "Hello, World!\n";
	pair::Pair<int, const char *> p(i, str);
	pair::Pair<int, const char *> p1(13, "Idk, something else");
	p = p1;
	assert(p.left() == p1.left());
	assert(p.right() == p1.right());
}

void test_pait_equal() {
	int i = 42;
	const char *str = "Hello, World!\n";
	pair::Pair<int, const char *> p1(i, str);
	pair::Pair<int, const char *> p2(i, str);
	assert(p1 == p2);
	pair::Pair<int, const char *> tmp(13, "asd");
	p2 = tmp;
	assert(!(p1 == p2));
}

void test_pair() {
	test_pair_constructor();
	test_pair_assign();
}

}
