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

void Data::write(uint64_t data) {
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

// assignment
Data &Data::operator%=(const Data &d) {
	this->data %= d.read();
	return *this;
}

Data &Data::operator%=(uint64_t data) {
	this->data %= data;
	return *this;
}

Data &Data::operator&=(const Data &d) {
	this->data &= d.read();
	return *this;
}

Data &Data::operator&=(uint64_t data) {
	this->data &= data;
	return *this;
}

Data &Data::operator*=(const Data &d) {
	this->data *= d.read();
	return *this;
}

Data &Data::operator*=(uint64_t data) {
	this->data *= data;
	return *this;
}

Data &Data::operator+=(const Data &d) {
	this->data += d.read();
	return *this;
}

Data &Data::operator+=(uint64_t data) {
	this->data += data;
	return *this;
}

Data &Data::operator-=(const Data &d) {
	this->data -= d.read();
	return *this;
}

Data &Data::operator-=(uint64_t data) {
	this->data -= data;
	return *this;
}

Data &Data::operator/=(const Data &d) {
	this->data /= d.read();
	return *this;
}

Data &Data::operator/=(uint64_t data) {
	this->data /= data;
	return *this;
}

Data &Data::operator<<=(const Data &d) {
	this->data <<= d.read();
	return *this;
}

Data &Data::operator<<=(uint64_t data) {
	this->data <<= data;
	return *this;
}

Data &Data::operator=(const Data &d) {
	this->data = d.read();
	return *this;
}

Data &Data::operator=(uint64_t data) {
	this->data = data;
	return *this;
}

Data &Data::operator>>=(const Data &d) {
	this->data >>= d.read();
	return *this;
}

Data &Data::operator>>=(uint64_t data) {
	this->data >>= data;
	return *this;
}

Data &Data::operator^=(const Data &d) {
	this->data ^= d.read();
	return *this;
}

Data &Data::operator^=(uint64_t data) {
	this->data ^= data;
	return *this;
}

Data &Data::operator|=(const Data &d) {
	this->data |= d.read();
	return *this;
}

Data &Data::operator|=(uint64_t data) {
	this->data |= data;
	return *this;
}

// increment, decrement
Data &Data::operator++() {
	this->data++;
	return *this;
}

Data Data::operator++(int n) {
	(void)n;
	this->data++;
	return Data(this->data - 1);
}

Data &Data::operator--() {
	this->data--;
	return *this;
}

Data Data::operator--(int n) {
	(void)n;
	this->data--;
	return Data(this->data + 1);
}

// artihmetic
Data Data::operator%(const Data &d) const {
	return Data(this->data % d.read());
}

Data Data::operator%(uint64_t data) const {
	return Data(this->data % data);
}

Data Data::operator&(const Data &d) const {
	return Data(this->data & d.read());
}

Data Data::operator&(uint64_t data) const {
	return Data(this->data & data);
}

Data Data::operator*(const Data &d) const {
	return Data(this->data * d.read());
}

Data Data::operator*(uint64_t data) const {
	return Data(this->data * data);
}

Data Data::operator+() const {
	return Data(+this->data);
}

Data Data::operator+(const Data &d) const {
	return Data(this->data + d.read());
}

Data Data::operator+(uint64_t data) const {
	return Data(this->data + data);
}

Data Data::operator-() const {
	return Data(-this->data);
}

Data Data::operator-(const Data &d) const {
	return Data(this->data - d.read());
}

Data Data::operator-(uint64_t data) const {
	return Data(this->data - data);
}

Data Data::operator/(const Data &d) const {
	return Data(this->data / d.read());
}

Data Data::operator/(uint64_t data) const {
	return Data(this->data / data);
}

Data Data::operator<<(const Data &d) const {
	// idk what is going on, but left shifts larger than the
	// type's size are returning garbage.
	return Data((d.read() >= sizeof(this->data)*8) ? 0 :
			this->data << d.read());
}

Data Data::operator<<(uint64_t data) const {
	// idk what is going on, but left shifts larger than the
	// type's size are returning garbage.
	return Data((data >= sizeof(this->data)*8) ? 0 : this->data << data);
}

Data Data::operator>>(const Data &d) const {
	return Data(this->data >> d.read());
}

Data Data::operator>>(uint64_t data) const {
	return Data(this->data >> data);
}

Data Data::operator^(const Data &d) const {
	return Data(this->data ^ d.read());
}

Data Data::operator^(uint64_t data) const {
	return Data(this->data ^ data);
}

Data Data::operator|(const Data &d) const {
	return Data(this->data | d.read());
}

Data Data::operator|(uint64_t data) const {
	return Data(this->data | data);
}

Data Data::operator~() const {
	return Data(~this->data);
}

// logical
bool Data::operator!() const {
	return !this->data;
}

bool Data::operator&&(const Data &d) const {
	return this->data && d.read();
}

bool Data::operator&&(uint64_t data) const {
	return this->data && data;
}

bool Data::operator||(const Data &d) const {
	return this->data || d.read();
}

bool Data::operator||(uint64_t data) const {
	return this->data || data;
}

// comparison
bool Data::operator!=(const Data &d) const {
	return this->read() != d.read();
}

bool Data::operator!=(uint64_t data) const {
	return  this->read() != data;
}

bool Data::operator<(const Data &d) const {
	return this->data < d.read();
}

bool Data::operator<(uint64_t data) const {
	return this->data < data;
}

bool Data::operator<=(const Data &d) const {
	return this->data <= d.read();
}

bool Data::operator<=(uint64_t data) const {
	return this->data <= data;
}

bool Data::operator==(const Data &d) const {
	return this->data == d.read();
}

bool Data::operator==(uint64_t data) const {
	return this->data == data;
}

bool Data::operator>(const Data &d) const {
	return this->data > d.read();
}

bool Data::operator>(uint64_t data) const {
	return this->data > data;
}

bool Data::operator>=(const Data &d) const {
	return this->data >= d.read();
}

bool Data::operator>=(uint64_t data) const {
	return this->data >= data;
}

}
