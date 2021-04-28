#include <assert.h>
#include <stddef.h>

#include "lang/parser.h"
#include "lang/tokenizer.h"
#include "test/test_parser.h"
#include "memory/memory.h"
#include "cpu/cpu.h"

namespace test {

void test_parser() {
	lang::Tokenizer toker("examples/nothing.s");
	lang::Parser parser;
	parser.build_from(toker);
	// parser.print();
	memory::Memory mem(1000);
	size_t inst_count = parser.write_to(mem);
	cpu::CPU cpu(2);
	cpu.run(mem);
	for (size_t i = 0; i < inst_count; i++) {
		delete mem[i];
	}
}

}
