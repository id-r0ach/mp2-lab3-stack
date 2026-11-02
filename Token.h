#pragma once
#include <string>

enum TokenType {Number, Operation, OpenBracket, CloseBracket};

struct Token {
	TokenType type;
	std::string str; // возможно лучше char
	double val;
	// приоритет
};