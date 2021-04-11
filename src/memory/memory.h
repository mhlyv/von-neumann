#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

#include "vector/vector.hpp"

namespace memory {

class Data {
private:
	uint64_t data;
public:
	Data();
	Data(uint64_t data);
	uint64_t read() const;
	void write(uint64_t data);
	virtual void write(Data *data);
	virtual Data *clone();
	virtual ~Data();

	// assignment
	Data &operator%=(const Data &d);
	Data &operator%=(uint64_t data);
	Data &operator&=(const Data &d);
	Data &operator&=(uint64_t data);
	Data &operator*=(const Data &d);
	Data &operator*=(uint64_t data);
	Data &operator+=(const Data &d);
	Data &operator+=(uint64_t data);
	Data &operator-=(const Data &d);
	Data &operator-=(uint64_t data);
	Data &operator/=(const Data &d);
	Data &operator/=(uint64_t data);
	Data &operator<<=(const Data &d);
	Data &operator<<=(uint64_t data);
	Data &operator=(const Data &d);
	Data &operator=(uint64_t data);
	Data &operator>>=(const Data &d);
	Data &operator>>=(uint64_t data);
	Data &operator^=(const Data &d);
	Data &operator^=(uint64_t data);
	Data &operator|=(const Data &d);
	Data &operator|=(uint64_t data);

	// increment, decrement
	Data &operator++();
	Data operator++(int n);
	Data &operator--();
	Data operator--(int n);

	// artihmetic
	Data operator%(const Data &d) const;
	Data operator%(uint64_t data) const;
	Data operator&(const Data &d) const;
	Data operator&(uint64_t data) const;
	Data operator*(const Data &d) const;
	Data operator*(uint64_t data) const;
	Data operator+() const;
	Data operator+(const Data &d) const;
	Data operator+(uint64_t data) const;
	Data operator-() const;
	Data operator-(const Data &d) const;
	Data operator-(uint64_t data) const;
	Data operator/(const Data &d) const;
	Data operator/(uint64_t data) const;
	Data operator<<(const Data &d) const;
	Data operator<<(uint64_t data) const;
	Data operator>>(const Data &d) const;
	Data operator>>(uint64_t data) const;
	Data operator^(const Data &d) const;
	Data operator^(uint64_t data) const;
	Data operator|(const Data &d) const;
	Data operator|(uint64_t data) const;
	Data operator~() const;

	// logical
	bool operator!() const;
	bool operator&&(const Data &d) const;
	bool operator&&(uint64_t data) const;
	bool operator||(const Data &d) const;
	bool operator||(uint64_t data) const;

	// comparison
	bool operator!=(const Data &d) const;
	bool operator!=(uint64_t data) const;
	bool operator<(const Data &d) const;
	bool operator<(uint64_t data) const;
	bool operator<=(const Data &d) const;
	bool operator<=(uint64_t data) const;
	bool operator==(const Data &d) const;
	bool operator==(uint64_t data) const;
	bool operator>(const Data &d) const;
	bool operator>(uint64_t data) const;
	bool operator>=(const Data &d) const;
	bool operator>=(uint64_t data) const;
};

class Memory {
private:
	Data **memory;
	const size_t len;
public:
	Memory(size_t len);
	Data *&operator[](size_t i);
	~Memory();
};

}

#endif // MEMORY_H
