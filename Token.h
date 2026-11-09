#pragma once
#include <string>
#include <iostream>

enum TokenType {Number, Operation, OpenBracket, CloseBracket};

struct Token {
	TokenType type;
	std::string str; // возможно лучше char
	double val;
	// приоритет
};
std::ostream& operator<<(std::ostream& os, const Token& t) {
	return os;
}