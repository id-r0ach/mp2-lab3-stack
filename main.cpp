#include <iostream>

#include "Calculator.h"



int main() {
	using std::cout;
	using std::cin;
	Calculator calculator;
	cout << "Enter a mathematical expression: ";
	try {
		cin >> calculator;
		double res = calculator.Calc();
		cout << "Infix_form: " << calculator.getInfix() << "\n";
		cout << "Result: " << res;
	}
	catch (...) {
		cout << "Error";
	}
}