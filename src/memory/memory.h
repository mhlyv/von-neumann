#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

#include "vector/vector.hpp"

namespace memory {

// object to hold a unit of data
class Data {
public:
	typedef uint64_t data_t;
private:
	data_t data;
public:
	Data();
	Data(data_t data);
	data_t read() const;
	void write(data_t data);
	operator data_t&();
	operator data_t() const;
	virtual void write(Data *data);
	virtual ~Data();
};

// object to hold a list of data
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
