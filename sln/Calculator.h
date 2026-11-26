#pragma once
#include <string>
#include "Container.h"
#include "Token.h"
#include <cctype>
#include <cstdlib>
#include "TDynamicStack.h"
#include <cmath>

// CalcPostfix -> Calc

using std::string;

class Calculator {
	string infix, postfix;
	Container<Token> inf_cont;
	TDynamicStack<Token> oper;
	TDynamicStack<double> num;
	// Очень хочется использовать хеш таблицу, ооооочень
	double varible[3] = { 0.0, 0.0, 0.0 };

	void infix_to_cont() {
		inf_cont.clear();
		inf_cont.push_back(Token{ OpenBracket, "(", 0.0, 0 });
		int i = 0;
		Token t_num, t_op, t_var;
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
				if ((infix[i] == '-' || infix[i] == '+') && inf_cont[inf_cont.size() - 1].type == OpenBracket) {
					inf_cont.push_back(Token{ Number, "0", 0});

				}
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
			if (infix[i] == 's') {
				if ((i + 2 <= infix.size() - 1) && (infix.substr(i, 3) == "sin")) {
					t_op.type = Function;
					t_op.str = "sin";
					t_op.priority = 1;
					inf_cont.push_back(t_op);
					i += 3;
					continue;
				}
			}
			if (infix[i] == 'c') {
				if (i + 2 <= infix.size() - 1) {
					if (infix.substr(i, 3) == "cos") {
						t_op.type = Function;
						t_op.str = "cos";
						t_op.priority = 1;
						inf_cont.push_back(t_op);
						i += 3;
						continue;
					}
					if (infix.substr(i, 3) == "ctg") {
						t_op.type = Function;
						t_op.str = "ctg";
						t_op.priority = 1;
						inf_cont.push_back(t_op);
						i += 3;
						continue;
					}
				}
			}

			if (infix[i] == 't') {
				if ((i + 1 <= infix.size() - 1) && (infix.substr(i, 2) == "tg")) {
					t_op.type = Function;
					t_op.str = "tg";
					t_op.priority = 1;
					inf_cont.push_back(t_op);
					i += 2;
					continue;
				}
			}

			if (infix[i] == 'l') {
				if ((i + 1 <= infix.size() - 1) && (infix.substr(i, 2) == "ln")) {
					t_op.type = Function;
					t_op.str = "ln";
					t_op.priority = 1;
					inf_cont.push_back(t_op);
					i += 2;
					continue;
				}
			}

			if (infix[i] == 'e') {
				if ((i + 2 <= infix.size() - 1) && (infix.substr(i, 3) == "exp")) {
					t_op.type = Function;
					t_op.str = "exp";
					t_op.priority = 3;
					inf_cont.push_back(t_op);
					i += 3;
					continue;
				}
			}

			if (infix[i] == 'x' || infix[i] == 'y' || infix[i] == 'z') {
				t_var.type = Variable;
				t_var.str = infix[i];
				inf_cont.push_back(t_var);
				i++;
				continue;
			}

			throw "Error"; // недопустимый символ
		}
		inf_cont.push_back(Token{ CloseBracket, ")", 0.0, 10 });
	}

	void apply_op() {
		double res = 0;
		if (oper.IsEmpty()) throw "Error";
		Token op = oper.pop();
		if (num.IsEmpty()) throw "Error";
		double right = num.pop();

		if (op.type == Function) {
			double t;
			if (op.str == "sin") res = std::sin(right);
			else if (op.str == "cos") res = std::cos(right);
			//else if (op.str == "tg") res = std::tan(right);
			else if (op.str == "tg") {
				t = std::cos(right);
				if (fabs(t) <= 1e-12) throw "Error";
				res = std::sin(right) / t;
			}
			else if (op.str == "ctg") {
				t = std::sin(right);
				if (fabs(t) <= 1e-12) throw "Error";
				res = std::cos(right) / t;
			}
			else if (op.str == "exp") res = std::exp(right);
			else if (op.str == "ln") {
				if (right <= 0) {
					throw "Error";
				}
				res = std::log(right);
			}
			num.push(res);
			return;	
		}

		if (num.IsEmpty()) throw "Error";
		double left = num.pop();


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

	void setvarible(double elem, int num) {
		if (num >= 0 && num < 3) {
			varible[num] = elem;
		}
	}


	double Calc() {
		num.clear();
		oper.clear();
		for (int i = 0; i < inf_cont.size(); i++) {

			if (inf_cont[i].type == Number) {
				num.push(inf_cont[i].val);
					continue;
				}
			if (inf_cont[i].type == Variable) {
				// Очень хочется использовать хеш таблицу, ооооочень
				int val;
				if (inf_cont[i].str == "x") {
					val = varible[0];
				}
				if (inf_cont[i].str == "y") {
					val = varible[1];
				}
				if (inf_cont[i].str == "z") {
					val = varible[2];
				}
				num.push(val);
				continue;
			}
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

			if (inf_cont[i].type == Function) {
				if (i + 1 >= inf_cont.size() || inf_cont[i + 1].type != OpenBracket) {
					throw "Error";
				}
				oper.push(inf_cont[i]);
				continue;
			}

			if (inf_cont[i].type == OpenBracket) {
				oper.push(inf_cont[i]);
				continue;
			}

			if (inf_cont[i].type == CloseBracket) {
				while (!oper.IsEmpty() && oper.top().type != OpenBracket) {
					apply_op();
				}
				if (oper.IsEmpty()) {
					throw "Error";
				}
				oper.pop();
				if (!oper.IsEmpty() && oper.top().type == Function) {
					apply_op();
				}
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

