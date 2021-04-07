#include <iostream>
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

void test_data_assignment() {
	uint64_t u1 = 42;
	uint64_t u2 = 13;
	memory::Data d1 = u1;
	memory::Data d2;

	d2 = u2;
	assert(d2 == u2);
	d2 = d1;
	assert(d2 == d1);

	d2 = u2;
	d1 %= d2;
	assert(d1 == u1 % u2);
	d1 = u1;
	d1 %= u2;
	assert(d1 == u1 % u2);

	d1 = u1;
	d1 &= d2;
	assert(d1 == (u1 & u2));
	d1 = u1;
	d1 &= u2;
	assert(d1 == (u1 & u2));

	d1 = u1;
	d1 *= d2;
	assert(d1 == u1 * u2);
	d1 = u1;
	d1 *= u2;
	assert(d1 == u1 * u2);

	d1 = u1;
	d1 += d2;
	assert(d1 == u1 + u2);
	d1 = u1;
	d1 += u2;
	assert(d1 == u1 + u2);

	d1 = u1;
	d1 -= d2;
	assert(d1 == u1 - u2);
	d1 = u1;
	d1 -= u2;
	assert(d1 == u1 - u2);

	d1 = u1;
	d1 /= d2;
	assert(d1 == u1 / u2);
	d1 = u1;
	d1 /= u2;
	assert(d1 == u1 / u2);

	d1 = u1;
	d1 <<= d2;
	assert(d1 == (u1 << u2));
	d1 = u1;
	d1 <<= u2;
	assert(d1 == (u1 << u2));

	d1 = u1;
	d1 >>= d2;
	assert(d1 == (u1 >> u2));
	d1 = u1;
	d1 >>= u2;
	assert(d1 == (u1 >> u2));

	d1 = u1;
	d1 ^= d2;
	assert(d1 == (u1 ^ u2));
	d1 = u1;
	d1 ^= u2;
	assert(d1 == (u1 ^ u2));

	d1 = u1;
	d1 |= d2;
	assert(d1 == (u1 | u2));
	d1 = u1;
	d1 |= u2;
	assert(d1 == (u1 | u2));
}

void test_data_inc_dec() {
	uint64_t u = 42;
	memory::Data d;

	d = u;
	assert(d++ == u);
	assert(d == u + 1);

	d = u;
	assert(++d == u + 1);

	d = u;
	assert(d-- == u);
	assert(d == u - 1);

	d = u;
	assert(--d == u - 1);
}

void test_data_arithmetic() {
	uint64_t u1 = 42;
	uint64_t u2 = 1000;

	assert((memory::Data(u1) % memory::Data(u2))  == (u1 % u2));
	assert((memory::Data(u1) % u2)                == (u1 % u2));

	assert((memory::Data(u1) & memory::Data(u2))  == (u1 & u2));
	assert((memory::Data(u1) & u2)                == (u1 & u2));

	assert((memory::Data(u1) * memory::Data(u2))  == (u1 * u2));
	assert((memory::Data(u1) * u2)                == (u1 * u2));

	assert((memory::Data(u1) + memory::Data(u2))  == (u1 + u2));
	assert((memory::Data(u1) + u2)                == (u1 + u2));

	assert((memory::Data(u1) - memory::Data(u2))  == (u1 - u2));
	assert((memory::Data(u1) - u2)                == (u1 - u2));

	assert((memory::Data(u1) / memory::Data(u2))  == (u1 / u2));
	assert((memory::Data(u1) / u2)                == (u1 / u2));

	assert((memory::Data(u1) << memory::Data(u2)) == (u1 << u2));
	assert((memory::Data(u1) << u2)               == (u1 << u2));

	assert((memory::Data(u1) >> memory::Data(u2)) == (u1 >> u2));
	assert((memory::Data(u1) >> u2)               == (u1 >> u2));

	assert((memory::Data(u1) ^ memory::Data(u2))  == (u1 ^ u2));
	assert((memory::Data(u1) ^ u2)                == (u1 ^ u2));

	assert((memory::Data(u1) | memory::Data(u2))  == (u1 | u2));
	assert((memory::Data(u1) | u2)                == (u1 | u2));

	assert(-memory::Data(u1)  == -u1);
	assert(-memory::Data(-u1) == u1);
	assert(+memory::Data(u1)  == +u1);
	assert(+memory::Data(-u1) == -u1);
	assert(~memory::Data(u1)  == ~u1);
}

void test_data_logical() {
	uint64_t u1 = 42; // MUST BE NON ZERO
	uint64_t u2 = 13; // MUST BE NON ZERO
	assert(!memory::Data(u1)                      == false);
	assert((memory::Data(u1) && memory::Data(u2)) == true);
	assert((memory::Data(0)  && memory::Data(u2)) == false);
	assert((memory::Data(u1) && u2)               == true);
	assert((memory::Data(0)  && u2)               == false);
	assert((memory::Data(u1) || memory::Data(u2)) == true);
	assert((memory::Data(0)  || memory::Data(u2)) == true);
	assert((memory::Data(u1) || u2)               == true);
	assert((memory::Data(0)  || u2)               == true);
	assert((memory::Data(0)  || memory::Data(0))  == false);
	assert((memory::Data(0)  || 0)                == false);
}

void test_data_comparison() {
	uint64_t u1 = 42;
	uint64_t u2 = 13;

	assert((memory::Data(u1) != memory::Data(u2)) == (u1 != u2));
	assert((memory::Data(u1) != u2)               == (u1 != u2));
	assert((memory::Data(u1) <  memory::Data(u2)) == (u1 <  u2));
	assert((memory::Data(u1) <  u2)               == (u1 <  u2));
	assert((memory::Data(u1) <= memory::Data(u2)) == (u1 <= u2));
	assert((memory::Data(u1) <= u2)               == (u1 <= u2));
	assert((memory::Data(u1) == memory::Data(u2)) == (u1 == u2));
	assert((memory::Data(u1) == u2)               == (u1 == u2));
	assert((memory::Data(u1) >  memory::Data(u2)) == (u1 >  u2));
	assert((memory::Data(u1) >  u2)               == (u1 >  u2));
	assert((memory::Data(u1) >= memory::Data(u2)) == (u1 >= u2));
	assert((memory::Data(u1) >= u2)               == (u1 >= u2));
}

void test_data() {
	test_data_default_constructor();
	test_data_constructor();
	test_data_write();
	test_data_clone();
	test_data_assignment();
	test_data_inc_dec();
	test_data_arithmetic();
	test_data_logical();
	test_data_comparison();
}

}
