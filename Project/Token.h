#ifndef TOKEN_H
#define TOKEN_H

#include <string>

struct Token {

	// Round brackets and block
	static constexpr int LP = 0;
	static constexpr int RP = 1;
	static constexpr int B = 2;

	// Statement
	static constexpr int SET = 3;
	static constexpr int PRI = 4;
	static constexpr int INP = 5;
	static constexpr int IF = 6;
	static constexpr int WHI = 7;

	// Arithmetic operator
	static constexpr int ADD = 8;
	static constexpr int SUB = 9;
	static constexpr int MUL = 10;
	static constexpr int DIV = 11;

	// Relational operator
	static constexpr int LT = 12;
	static constexpr int GT = 13;
	static constexpr int EQ = 14;

	// Boolean operator
	static constexpr int AND = 15;
	static constexpr int OR = 16;
	static constexpr int NOT = 17;

	// Boolean constant
	static constexpr int T = 18;
	static constexpr int F = 19;

	// Number, variable
	static constexpr int NUM = 20;
	static constexpr int VAR = 21;

	static constexpr const char* id2word[]{
		"(", ")", "BLOCK",
		"SET", "PRINT", "INPUT", "IF", "WHILE",
		"ADD", "SUB", "MUL", "DIV",
		"LT", "GT", "EQ",
		"AND", "OR", "NOT",
		"TRUE", "FALSE",
		"NUM", "VAR"
	};

	Token(int t, const char* w) : tag{ t }, word{ w } {};

	Token(int t, std::string w) : tag{ t }, word{ w } {};

	int tag;
	std::string word;
};

// Useful for DEBUG the tokenizer but not strictly
// needed for interpreter purposes
std::ostream& operator<< (std::ostream& os, const Token& t);

#endif
