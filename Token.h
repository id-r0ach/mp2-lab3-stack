#pragma once
#include <string>
#include <iostream>

enum TokenType {Number, Operation, OpenBracket, CloseBracket};

struct Token {
	TokenType type;
	std::string str; // возможно лучше char
	double val;
	int priority;
	Token(TokenType t = Number, std::string s = "", double v = 0.0, int p = 0) : type(t), str(s), val(v), priority(p) {}
};
inline std::ostream& operator<<(std::ostream& os, const Token& t) {
	return os;
}
