#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <stddef.h>
#include <stdexcept>

namespace vector {

// object to hold a list of data
template<typename T>
class Vector {
private:
	size_t length;
	T *data;
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	Vector();
	Vector(size_t len);
	Vector(Vector<T> &vec);
	Vector(const Vector<T> &vec);
	size_t size() const;
	Vector<T> &operator=(Vector<T> &vec);
	Vector<T> &operator=(const Vector<T> &vec);
	T& operator[](size_t i);
	const T& operator[](size_t i) const;
	iterator begin();
	iterator end();
	const_iterator cbegin() const;
	const_iterator cend() const;
	void append(T d);
	void clean();
	virtual bool operator==(const Vector<T> &vec) const;
	virtual bool operator!=(const Vector<T> &vec) const;
	virtual ~Vector();
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
		if (this->length != 0) {
			this->data = new T[this->length];
		}
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
		if (this->length != 0) {
			this->data = new T[this->length];
		}
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
const T &Vector<T>::operator[](size_t i) const {
	if (i >= this->length) {
		throw std::out_of_range("index is out of bounds");
	}
	return this->data[i];
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin() {
	return this->data;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::end() {
	return this->data + this->length;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const {
	return this->data;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const {
	return this->data + this->length;
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
bool Vector<T>::operator==(const Vector<T> &vec) const {
	if (this->length != vec.size()) {
		return false;
	} else {
		for (size_t i = 0; i < this->length; i++) {
			if (this->data[i] != vec[i]) {
				return false;
			}
		}
	}

	return true;
}

template<typename T>
bool Vector<T>::operator!=(const Vector<T> &vec) const {
	return !(*this == vec);
}

template<typename T>
Vector<T>::~Vector() {
	this->clean();
}

}

#endif // VECTOR_HPP
