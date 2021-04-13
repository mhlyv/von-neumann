#include <stdint.h>

#include "memory/memory.h"

namespace memory {

Data::Data() : Data(0) {
}

Data::Data(Data::data_t data) : data(data) {
}

Data::data_t Data::read() const {
	return this->data;
}

Data::operator Data::data_t&() {
	return this->data;
}

Data::operator Data::data_t() const {
	return this->data;
}

void Data::write(Data::data_t data) {
	this->data = data;
}

void Data::write(Data *data) {
	this->data = data->read();
}

Data *Data::clone() {
	return new Data(this->data);
}

Data::~Data() {
}

}
