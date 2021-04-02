#include <cctype>
#include <stdexcept>

#include "memory/memory.h"

namespace memory {

Memory::Memory(std::size_t n) : n_elements(n) {
	this->elements = new MemoryElement *[this->n_elements];
}

MemoryElement &Memory::operator[](std::size_t i) {
	if (i >= this->n_elements) {
		throw std::out_of_range("Index is out of range");
	}

	return *this->elements[i];
}

Memory::~Memory() {
	delete[] this->elements;
}

}
