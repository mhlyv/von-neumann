#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <stddef.h>
#include <stdexcept>

namespace vector {

template<typename T>
class Vector {
private:
	size_t len;
	T *data;
public:
	Vector();
	Vector(size_t len);
	Vector(Vector<T> &vec);
	Vector(const Vector<T> &vec);
	Vector<T> &operator=(Vector<T> &vec);
	Vector<T> &operator=(const Vector<T> &vec);
	size_t size() const;
	T& operator[](size_t i);
	void append(T data);
	void clean();
	~Vector();
};

template<typename T>
Vector<T>::Vector() {
	this->data = NULL;
	this->len = 0;
}

template<typename T>
Vector<T>::Vector(size_t len) : len(len) {
	this->data = new T[len];
}

template<typename T>
Vector<T>::Vector(Vector<T> &vec) {
	this->len = vec.size();
	this->data = new T[this->len];

	for (size_t i = 0; i < this->len; i++) {
		this->data[i] = vec[i];
	}
}

template<typename T>
Vector<T>::Vector(const Vector<T> &vec) {
	this->len = vec.size();
	this->data = new T[this->len];

	for (size_t i = 0; i < this->len; i++) {
		this->data[i] = vec[i];
	}
}

template<typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &vec) {
	if (vec.size() != this->len) {
		delete[] this->data;
		this->len = vec.size();
		this->data = new T[this->len];
	}

	for (size_t i = 0; i < this->len; i++) {
		this->data[i] = vec[i];
	}

	return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &vec) {
	if (vec.size() != this->len) {
		delete[] this->data;
		this->len = vec.size();
		this->data = new T[this->len];
	}

	for (size_t i = 0; i < this->len; i++) {
		this->data[i] = vec[i];
	}

	return *this;
}

template<typename T>
size_t Vector<T>::size() const {
	return this->len;
}

template<typename T>
T &Vector<T>::operator[](size_t i) {
	if (i >= this->len) {
		throw std::out_of_range("index is out of bounds");
	}
	return this->data[i];
}

template<typename T>
void Vector<T>::append(T data) {
	T *backup = this->data;
	this->data = new T[this->len + 1];
	for (size_t i = 0; i < this->len; i++) {
		this->data[i] = backup[i];
	}
	this->data[this->len] = data;
	if (this->len != 0) {
		delete[] backup;
	}
	this->len++;
}

template<typename T>
void Vector<T>::clean() {
	if (this->len != 0) {
		delete[] this->data;
		this->len = 0;
	}
}

template<typename T>
Vector<T>::~Vector() {
	this->clean();
}

}

#endif // __VECTOR_HPP__
