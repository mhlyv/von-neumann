#include <stdint.h>

#include "memory/memory.h"

namespace memory {

Data::Data() : Data(0) {
}

Data::Data(uint64_t data) : data(data) {
}

uint64_t Data::read() const {
	return this->data;
}

void Data::write(Data *data) {
	this->data = data->read();
}

Data *Data::clone() const {
	return new Data(this->data);
}

Data::~Data() {
}

}
