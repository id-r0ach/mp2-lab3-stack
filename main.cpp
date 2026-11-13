#include <iostream>

#include "Calculator.h"



int main() {
	using std::cout;
	using std::cin;
	Calculator calculator;
	cout << "Enter a mathematical expression: ";
	try {
		cin >> calculator;
		calculator.to_postfix();
		double res = calculator.CalcPostfix();
		cout << "Infix_form: " << calculator.getInfix() << "\n";
		cout << "Postfix_form: " << calculator.getPostfix() << "\n";
		cout << "Result: " << res;
	}
	catch (...) {
		cout << "Error";
	}
}