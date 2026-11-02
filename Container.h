#pragma once
#include <iostream>
#include <algorithm>
template <typename T>
class Container {
private:
	int size;
	T* pmem;

public:
	Container(int _size = 10) {
		if (_size <= 0) {
			throw "Размер меньше 0";
		}
		size = _size;
		pmem = new T[size];
	}
	~Container() {
		if (pmem != nullptr) {
			delete[] pmem;
		}
	}
	Container(const Container& c) : size(c.size) {
		pmem = new T[size];
		for (int i = 0; i < size; i++) {
			pmem[i] = c.pmem[i];
		}
	}
	Container(Container&& c) noexcept {
		size = c.size;
		pmem = c.pmem;
		c.size = 0;
		c.pmem = nullptr;
	}


	Container& operator=(const Container& c) {
		if (this != &c) {
			T* new_pmem = new T[c.size];
			for (int i = 0; i < c.size; i++) {
				new_pmem[i] = c.pmem[i];
			}
			delete[] pmem;
			pmem = new_pmem;
			size = c.size;
		}
		return *this;
	}
	Container& operator=(Container&& c) noexcept {
		if (this != &c) {
			size = c.size;
			delete[] pmem;
			pmem = c.pmem;
			c.size = 0;
			c.pmem = nullptr;
		}
		return *this;
	}


	T& operator[](int index) {
		if (index < 0 || index >= size) {
			throw "Неверный индекс";
		}
		return pmem[index];
	}
	const T& operator[](int index) const {
		if (index < 0 || index >= size) {
			throw "Неверный индекс";
		}
		return pmem[index];
	}


	void resize(const int& _size) {
		int new_size = size + _size;
		if (new_size <= 0) {
			throw "Размер меньше 0";
		}
		T* new_pmem = new T[size + _size];
		int min_size = std::min(new_size, size);
		for (int i = 0; i < min_size; i++) {
			new_pmem[i] = pmem[i];
		}
		delete[] pmem;
		pmem = new_pmem;
		size = new_size;
	}

	friend std::ostream& operator<<(std::ostream& os, const Container& c) {
		for (int i = 0; i < c.size; i++) {
			os << c.pmem[i] << " ";
		}
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Container& c) {
		std::cout << "В первой строке введите размер" << std::endl
			<< "Во второй значения через пробел" << std::endl;
		is >> c.size;
		delete[] c.pmem;
		c.pmem = new T[c.size];
		for (int i = 0; i < c.size; i++) {
			is >> c.pmem[i];
		}
		return is;
	}



	Container operator+(const Container& _c) {
		Container res(size + _c.size);
		for (int i = 0; i < size; i++) {
			res[i] = pmem[i];
		}
		for (int i = 0; i < _c.size; i++) {
			res.pmem[i + size] = _c.pmem[i];
		}
		return res;
	}


	Container& operator++() {
		this->resize(1);
		return *this;
	}

	Container operator++(int c) {
		Container temp(*this);
		this->resize(1);
		return temp;
	}

	Container& operator+=(const Container& c) {
		int old_size = size;
		this->resize(c.size);
		for (int i = 0; i < c.size; i++) {
			pmem[i + old_size] = c.pmem[i];
		}
		return *this;
	}


	Container operator-(const Container& _c) {
		int new_size = size - _c.size;
		if (new_size <= 0) {
			throw "Новый размер должен быть больше 0";
		}
		Container res(new_size);
		for (int i = 0; i < new_size; i++) {
			res[i] = pmem[i];
		}
		return res;
	}

	Container& operator--() {
		this->resize(-1);
		return *this;
	}

	Container operator--(int c) {
		Container temp(*this);
		this->resize(-1);
		return temp;
	}

	Container& operator-=(const Container& c) {
		int old_size = size;
		this->resize(-c.size);
		return *this;
	}
};

