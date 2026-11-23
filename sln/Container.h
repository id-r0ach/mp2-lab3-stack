#pragma once
#include <iostream>
#include <algorithm>
#include <climits>
template <typename T>
class Container {
private:
	size_t capacity; // реальный размер(макс количество элементов)
	T* pmem;
	size_t count; // реальное количество элементов

	void resize() {
		size_t new_size;
		if (capacity == 0) {
			new_size = 1;
		}
		else {
			new_size = capacity * 2;
		}
		T* new_pmem = new T[new_size];
		for (size_t i = 0; i < count; i++) {
			new_pmem[i] = pmem[i];
		}
		delete[] pmem;
		pmem = new_pmem;
		capacity = new_size;
	}

public:
	Container(size_t _size = 10) {
		if (_size > UINT_MAX || _size == 0) {
			throw "Размер меньше 0";
		}
		capacity = _size;
		count = 0;
		pmem = new T[capacity];
	}
	~Container() {
		if (pmem != nullptr) {
			delete[] pmem;
		}
	}
	Container(const Container& c) : capacity(c.capacity), count(c.count) {
		pmem = new T[capacity];
		for (size_t i = 0; i < count; i++) {
			pmem[i] = c.pmem[i];
		}
	}
	Container(Container&& c) noexcept {
		capacity = c.capacity;
		pmem = c.pmem;
		count = c.count;
		c.capacity = 0;
		c.count = 0;
		c.pmem = nullptr;
	}


	Container& operator=(const Container& c) {
		if (this != &c) {
			T* new_pmem = new T[c.capacity];
			for (size_t i = 0; i < c.count; i++) {
				new_pmem[i] = c.pmem[i];
			}
			delete[] pmem;
			pmem = new_pmem;
			count = c.count;
			capacity = c.capacity;
		}
		return *this;
	}
	Container& operator=(Container&& c) noexcept {
		if (this != &c) {
			capacity = c.capacity;
			delete[] pmem;
			pmem = c.pmem;
			count = c.count;
			c.count = 0;
			c.capacity = 0;
			c.pmem = nullptr;
		}
		return *this;
	}


	T& operator[](int index) {
		if (index < 0 || index >= count) {
			throw "Неверный индекс";
		}
		return pmem[index];
	}
	const T& operator[](int index) const {
		if (index < 0 || index >= count) {
			throw "Неверный индекс";
		}
		return pmem[index];
	}

	void push_back(const T& elem) {
		if (count >= capacity) {
			resize();
		}
		pmem[count++] = elem;
	}

	T pop_back() {
		if (count == 0) {
			throw "Контейнер пустой";
		}
		return pmem[--count];
	}

	void clear() noexcept {
		count = 0;
	}

	bool operator==(const Container& c) const {
		if (this == &c) {
			return true;
		}
		if (this->size() != c.size()) {
			return false;
		}
		for (int i = 0; i < this->size(); i++) {
			if ((*this)[i] != c[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator!=(const Container& c) const {
		return !(*this == c);
	}

	/*
	void resize(const int& _size) {
		int new_size = capacity + _size;
		if (new_size <= 0) {
			throw "Размер меньше 0";
		}
		T* new_pmem = new T[capacity + _size];
		int min_size = std::min(new_size, capacity);
		for (int i = 0; i < min_size; i++) {
			new_pmem[i] = pmem[i];
		}
		delete[] pmem;
		pmem = new_pmem;
		capacity = new_size;
	}
	*/
	friend std::ostream& operator<<(std::ostream& os, const Container& c) {
		for (int i = 0; i < c.count; i++) {
			os << c.pmem[i] << " ";
		}
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Container& c) {
		is >> c.count;
		c.capacity = c.count * 2;
		delete[] c.pmem;
		c.pmem = new T[c.capacity];
		for (int i = 0; i < c.count; i++) {
			is >> c.pmem[i];
		}
		return is;
	}

	int size() const noexcept {
		return count;
	}


	/*
	Container operator+(const Container& _c) {
		Container res(capacity + _c.capacity);
		for (int i = 0; i < capacity; i++) {
			res[i] = pmem[i];
		}
		for (int i = 0; i < _c.capacity; i++) {
			res.pmem[i + capacity] = _c.pmem[i];
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
		int old_size = capacity;
		this->resize(c.capacity);
		for (int i = 0; i < c.capacity; i++) {
			pmem[i + old_size] = c.pmem[i];
		}
		return *this;
	}


	Container operator-(const Container& _c) {
		int new_size = capacity - _c.capacity;
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
		int old_size = capacity;
		this->resize(-c.capacity);
		return *this;
	}
	*/
};

