#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stddef.h>
#include <stdexcept>

namespace vector {

template<typename T>
class Vector {
private:
	size_t length;
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
	void append(T d);
	void clean();
	~Vector();
};

template<typename T>
Vector<T>::Vector() {
	this->data = nullptr;
	this->length = 0;
}

template<typename T>
Vector<T>::Vector(size_t len) : length(len) {
	if (len > 0) {
		this->data = new T[len];
	} else {
		this->data = nullptr;
	}
}

template<typename T>
Vector<T>::Vector(Vector<T> &vec) {
	this->length = vec.size();
	if (this->length > 0) {
		this->data = new T[this->length];
		for (size_t i = 0; i < this->length; i++) {
			this->data[i] = vec[i];
		}
	} else {
		this->data = nullptr;
	}
}

template<typename T>
Vector<T>::Vector(const Vector<T> &vec) {
	this->length = vec.size();
	if (this->length > 0) {
		this->data = new T[this->length];
		for (size_t i = 0; i < this->length; i++) {
			this->data[i] = vec[i];
		}
	} else {
		this->data = nullptr;
	}
}

template<typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &vec) {
	if (vec.size() != this->length) {
		delete[] this->data;
		this->length = vec.size();
		this->data = new T[this->length];
	}

	for (size_t i = 0; i < this->length; i++) {
		this->data[i] = vec[i];
	}

	return *this;
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &vec) {
	if (vec.size() != this->length) {
		delete[] this->data;
		this->length = vec.size();
		this->data = new T[this->length];
	}

	for (size_t i = 0; i < this->length; i++) {
		this->data[i] = vec[i];
	}

	return *this;
}

template<typename T>
size_t Vector<T>::size() const {
	return this->length;
}

template<typename T>
T &Vector<T>::operator[](size_t i) {
	if (i >= this->length) {
		throw std::out_of_range("index is out of bounds");
	}
	return this->data[i];
}

template<typename T>
void Vector<T>::append(T d) {
	T *backup = this->data;
	this->data = new T[this->length + 1];
	for (size_t i = 0; i < this->length; i++) {
		this->data[i] = backup[i];
	}
	this->data[this->length] = d;
	if (this->length != 0) {
		delete[] backup;
	}
	this->length++;
}

template<typename T>
void Vector<T>::clean() {
	if (this->length != 0) {
		delete[] this->data;
		this->length = 0;
	}
}

template<typename T>
Vector<T>::~Vector() {
	this->clean();
}

}

#endif // VECTOR_HPP
