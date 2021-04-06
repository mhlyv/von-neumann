#include <stddef.h>
#include <stdexcept>

#include "memory/memory.h"
#include "vector/vector.hpp"

namespace memory {

Memory::Memory(size_t len) : len(len) {
	this->memory = new Data *[this->len];
}

Data *&Memory::operator[](size_t i) {
	if (i >= this->len) {
		throw std::out_of_range("Index out of range");
	}

	return this->memory[i];
}

Memory::~Memory() {
	delete[] this->memory;
}

}
