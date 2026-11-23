#pragma once
#include <string>
#include "Container.h"
#include "Token.h"
#include <cctype>
#include <cstdlib>
#include "TDynamicStack.h"
#include <cmath>

using std::string;

class Calculator {
	string infix, postfix;
	Container<Token> inf_cont;
	TDynamicStack<Token> oper;
	TDynamicStack<double> num;
	void infix_to_cont() {
		inf_cont.clear();
		inf_cont.push_back(Token{ OpenBracket, "(", 0.0, 0 });
		int i = 0;
		Token t_num, t_op;
		while (i < infix.size()) {
			if (infix[i] == ' ') {
				i++;
				continue;
			}
			if (infix[i] == '(') {
				inf_cont.push_back(Token{ OpenBracket, "(", 0.0, 0 });
				i++;
				continue;
			}
			if (infix[i] == ')') {
				inf_cont.push_back(Token{ CloseBracket, ")", 0.0, 10 });
				i++;
				continue;
			}
			if (std::isdigit(infix[i]) || infix[i] == '.') {
				char* p;
				t_num.val = std::strtod(&infix[i], &p);
				t_num.type = Number;
				int d = p - &infix[i];
				if (d == 0) {
					throw "Error"; // Считана один символ '.', неверный ввод
				}
				t_num.str = infix.substr(i, d);
				inf_cont.push_back(t_num);
				i += d;
				continue;
			}
			if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^') {
				t_op.type = Operation;
				t_op.str = infix[i];
				if (infix[i] == '+' || infix[i] == '-') {
					t_op.priority = 1;
				}
				if (infix[i] == '*' || infix[i] == '/') {
					t_op.priority = 2;
				}
				if (infix[i] == '^') {
					t_op.priority = 3;
				}
				inf_cont.push_back(t_op);
				i++;
				continue;
			}
			throw "Error"; // недопустимый символ
		}
		inf_cont.push_back(Token{ CloseBracket, ")", 0.0, 10 });
	}

	void apply_op() {
		if (oper.IsEmpty()) throw "Error";
		Token op = oper.pop();
		if (num.IsEmpty()) throw "Error";
		double right = num.pop();
		if (num.IsEmpty()) throw "Error";
		double left = num.pop();

		double res = 0;
		if (op.str == "+") res = left + right;
		else if (op.str == "-") res = left - right;
		else if (op.str == "*") res = left * right;
		else if (op.str == "/") {
			if (right == 0) throw "Error";
			res = left / right;
		}
		else if (op.str == "^") res = std::pow(left, right);
		else throw "Error";

		num.push(res);
	}
public:
	Calculator(const string& s = "") : oper(100), num(100) {
		set_infix(s);
	}
	void set_infix(const string& s) {
		infix = s;
		postfix = "";
		inf_cont.clear();
		// Если s = "", то скип, иначе разбиваем строку на токены
		if (!infix.empty()) {
			infix_to_cont();
		}
	}
	double CalcPostfix() {
		num.clear();
		oper.clear();
		for (int i = 0; i < inf_cont.size(); i++) {

			if (inf_cont[i].type == Number) {
				num.push(inf_cont[i].val);
					continue;
				}

			// Много дубликата кода, надо подумать как это вынести
			if (inf_cont[i].type == Operation) {
				if (inf_cont[i].str == "^") {
					while (!oper.IsEmpty() && inf_cont[i].priority < oper.top().priority) {
						apply_op();
					}
				}
				else {
					while (!oper.IsEmpty() && inf_cont[i].priority <= oper.top().priority) {
						apply_op();
					}
				}
				oper.push(inf_cont[i]);
				continue;
			}

			if (inf_cont[i].type == OpenBracket) {
				oper.push(inf_cont[i]);
				continue;
			}

			if (inf_cont[i].type == CloseBracket) {
				while (oper.top().type != OpenBracket) {
					apply_op();
				}
				if (oper.IsEmpty()) {
					throw "Error";
				}
				oper.pop();
				continue;

			}
		}
		if (num.IsEmpty() || !oper.IsEmpty()) {
			throw "Error"; // Нет ответа, после отладки удалить
		}
		double ans = num.pop();
		if (!num.IsEmpty()) {
			throw "Error";
		}
		return ans;
	}

	string getInfix() const {
		return infix;
	}

	friend std::ostream& operator<<(std::ostream& os, const Calculator& c) {
		os << c.infix;
		return os;	
	}
	friend std::istream& operator>>(std::istream& is, Calculator& c) {
		string s;
		getline(is, s);
		c.set_infix(s);
		return is;
	}
};

