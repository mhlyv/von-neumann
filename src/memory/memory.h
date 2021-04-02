#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <cctype>

namespace memory {

class MemoryElement {
public:
	virtual ~MemoryElement() {}
};

// A MemoryElement to store a single object
template<typename T>
class Data : public MemoryElement {
private:
	T data;
public:
	Data();
	Data(T data);
	T& read();
	void write(T data);
	~Data();
};

class Memory {
private:
	const std::size_t n_elements;
	MemoryElement **elements;
	Memory();
public:
	Memory(std::size_t n);
	MemoryElement &operator[](std::size_t i);
	~Memory();
};

}

#endif // __MEMORY_H__
