#pragma once
#include <string>
#include "Container.h"
#include "Token.h"
#include <cctype>
#include <cstdlib>

using std::string;

class Calculator {
	string infix, postfix;
	Container<Token> inf_cont, post_cont;
	void infix_to_cont() {
		inf_cont.clear();
		int i = 0;
		Token t;
		while (i < infix.size()) {
			if (infix[i] == '(') {
				t.type = OpenBracket;
				t.str = '(';
				inf_cont.push_back(t);
			}
			if (infix[i] == ')') {
				t.type = CloseBracket;
				t.str = ')';
				inf_cont.push_back(t);
			}
			if ('0' <= infix[i] && infix[i] <= '9' || infix[i] == '.') {
				char* p;
				t.val = std::strtod(&infix[i], &p);
				t.type = Number;
				int d = p - &infix[i];
				t.str = infix.substr(i, d);
				inf_cont.push_back(t);
				i += d - 1;
			}
			if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') {
				t.type = Operation;
				t.str = infix[i];
				inf_cont.push_back(t);
			}
			i++;
		}
	}
public:
	Calculator() {
		infix = "";
		postfix = "";
		inf_cont.clear();
		post_cont.clear();
	}
};

