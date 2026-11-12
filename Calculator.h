#pragma once
#include <string>
#include "Container.h"
#include "Token.h"
#include <cctype>
#include <cstdlib>
#include "TDynamicStack.h"
#include <cmath>

// Дописать приоритизацию
// Дописать теста
// Добавить проверку на пустой стек в префикс

using std::string;

class Calculator {
	string infix, postfix;
	Container<Token> inf_cont, post_cont;
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
public:
	Calculator(const string& s = "") {
		set_infix(s);
	}
	void set_infix(const string& s) {
		infix = s;
		postfix = "";
		inf_cont.clear();
		post_cont.clear();
		// Если s = "", то скип, иначе разбиваем строку на токены
		if (!infix.empty()) {
			infix_to_cont();
		}
	}

	void to_postfix() {
		oper.clear();
		post_cont.clear();
		for (int i = 0; i < inf_cont.size(); i++) {

			if (inf_cont[i].type == OpenBracket) {
				oper.push(inf_cont[i]);
				continue;
			}

			if (inf_cont[i].type == Number) {
				post_cont.push_back(inf_cont[i]);
				continue;
			}

			if (inf_cont[i].type == CloseBracket) {
				while (oper.top().type != OpenBracket) {
					post_cont.push_back(oper.pop());
				}
				if (oper.IsEmpty()) {
					throw "Error"; // была закрывающаяся скобка, но нет открывающейся скобки, после отладки удалить
				}
				oper.pop();
				continue;
			}

			if (inf_cont[i].type == Operation) {
				while (inf_cont[i].priority <= oper.top().priority) {
					post_cont.push_back(oper.pop());
				}
				oper.push(inf_cont[i]);
				continue;
			}
		}
		if (post_cont.size() > 0) {
			postfix += post_cont[0].str;
			for (int i = 1; i < post_cont.size(); i++) {
				postfix += " " + post_cont[i].str;
			}
		}
	}

	double CalcPostfix() {
		num.clear();
		for (int i = 0; i < post_cont.size(); i++) {
			if (post_cont[i].type == Number) {
				num.push(post_cont[i].val);
					continue;
				}
			if (post_cont[i].type == Operation) {
				double right, left, res;
				if (num.IsEmpty()) {
					throw "Error"; // Стек пустой, после отладки удалить
				}
				right = num.pop();
				if (num.IsEmpty()) {
					throw "Error"; // Стек пустой, после отладки удалить
				}
				left = num.pop();
				if (post_cont[i].str == "+") {
					res = left + right;
				}
				if (post_cont[i].str == "-") {
					res = left - right;
				}
				if (post_cont[i].str == "*") {
					res = left * right;
				}
				if (post_cont[i].str == "/") {
					if (right == 0) {
						throw "Error"; // Деление на ноль
					}
					res = left / right;
				}
				if (post_cont[i].str == "^") {
					res = pow(left, right);
				}
				num.push(res);
				continue;
			}
		}
		if (num.IsEmpty()) {
			throw "Error"; // Нет ответа, после отладки удалить
		}
		double ans = num.pop();
		if (!num.IsEmpty()) {
			throw "Error";
		}
		return ans;
	}
};

