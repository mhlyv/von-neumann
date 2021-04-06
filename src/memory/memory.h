#ifndef __MEMORY_H__
#define __MEMORY_H__

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
	virtual void write(Data *data);
	virtual Data *clone() const;
	virtual ~Data();
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

#endif // __MEMORY_H__
