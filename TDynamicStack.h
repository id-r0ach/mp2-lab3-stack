#pragma once

#include <climits>

template <typename T>
class TDynamicStack{
	static constexpr unsigned int maxValue = UINT_MAX; // Максимальная высота стека
	int top_i;
	size_t size;
	T* pMem;
public:
	// Конструкторы
	TDynamicStack(size_t _size = 1) {
		if (_size == 0 || _size > UINT_MAX) {
			throw "incorrect size";
		}
		size = _size;
		top_i = -1;
		pMem = new T[size];
	}
	~TDynamicStack() {
		size = 0;
		top_i = -1;
		delete[] pMem;
	}
	TDynamicStack(const TDynamicStack& st) {
		size = st.size;
		pMem = new T[size];
		top_i = st.top_i;
		for (int i = 0; i <= top_i; i++) {
			pMem[i] = st.pMem[i];
		}
	}
	TDynamicStack& operator=(const TDynamicStack& st) {
		if (this != &st) {
			size = st.size;
			delete[] pMem;
			pMem = new T[size];
			top_i = st.top_i;
			for (int i = 0; i <= top_i; i++) {
				pMem[i] = st.pMem[i];
			}
		}
		return *this;
	}
	TDynamicStack(TDynamicStack&& st) noexcept{
		size = st.size;
		top_i = st.top_i;
		pMem = st.pMem;
		st.pMem = nullptr;
		st.size = 0;
		st.top_i = -1;
	}
	TDynamicStack& operator=(TDynamicStack&& st) noexcept {
		if (this != &st) {
			size = st.size;
			top_i = st.top_i;
			delete[] pMem;
			pMem = st.pMem;
			st.pMem = nullptr;
			st.size = 0;
			st.top_i = -1;
		}
		return *this;
	}

	// Операторы сравнения
	bool operator==(const TDynamicStack& st) const noexcept {
		if (size == st.size && top_i == st.top_i) {
			for (int i = 0; i <= top_i; i++) {
				if (pMem[i] != st.pMem[i]) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
	bool operator!=(const TDynamicStack& st) const noexcept {
		return !(*this == st);
	}

	// Методы пустой/целый
	bool IsFull() const noexcept {
		return top_i == size - 1;
	}
	bool IsEmpty() const noexcept {
		return top_i == -1;
	}

	// Вставить/получить элемент
	void push(const T& elem) {
		if (IsFull()) {
			throw "Stack is full";
		}
		pMem[++top_i] = elem;
	}
	T pop() {
		if (IsEmpty()) {
			throw "Stack is empty";
		}
		return pMem[top_i--];
	}

	void clear() noexcept {
		top_i = -1;
	}
};

