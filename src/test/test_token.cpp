#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "lang/token.h"
#include "test/test_token.h"

namespace test {

void test_token_constructor() {
	const char *s = "Hello, World!";
	lang::Token t(s);

	for (size_t i = 0; i <= strlen(s); i++) {
		assert(s[i] == t[i]);
	}
}

void test_token_comparison() {
	const char *s1 = "Hello, World!";
	const char *s2 = "nope";

	lang::Token t1(s1);
	lang::Token t2(s2);
	lang::Token t3(s2);

	assert(t1 == s1);
	assert(t2 == s2);

	assert(t1 != s2);
	assert(t2 != s1);

	assert(t1 != t2);
	assert(t2 == t3);
}

void test_token() {
	test_token_constructor();
	test_token_comparison();
}

}
