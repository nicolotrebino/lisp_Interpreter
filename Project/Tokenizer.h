#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <fstream>

#include "Token.h"
#include "Utility.h"
#include "Exceptions.h"

class Tokenizer {

public:
	Tokenizer() = default;
	~Tokenizer() = default;

	std::vector<Token> operator()(std::ifstream& inputFile) {
		std::vector<Token> inputTokens;
		tokenizeInputFile(inputFile, inputTokens);
		return inputTokens;
	}

private:
	void tokenizeInputFile(std::ifstream& inputFile, std::vector<Token>& inputTokens);
};
#endif