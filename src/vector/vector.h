#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h>

namespace vector {

template<typename T>
class Vector {
private:
	size_t len;
	T *data;
public:
	Vector();
	Vector(const Vector<T> &vec);
	Vector<T> &operator=(const Vector<T> &vec);
	size_t size() const;
	T& operator[](size_t i);
	void append(T data);
	void clean();
	~Vector();
};

}

#endif // __VECTOR_H__
