#include "memory/memory.h"

namespace memory {

template<typename T>
Data<T>::Data() {
}

template<typename T>
Data<T>::Data(T data) : data(data) {
}

template<typename T>
T& Data<T>::read() {
	return this->data;
}

template<typename T>
void Data<T>::write(T data) {
	this->data = data;
}

template<typename T>
Data<T>::~Data() {
}

}
