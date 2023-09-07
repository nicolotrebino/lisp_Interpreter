#include <string>
#include <sstream>
#include <iostream>

#include "Tokenizer.h"

void Tokenizer::tokenizeInputFile(std::ifstream& inputFile, std::vector<Token>& inputTokens) {

	int count_line = 1;
	char ch;
	ch = inputFile.get();

	while (!inputFile.eof()) {

		// Ignoring whitespaces
		if (std::isspace(ch)) {
			if (ch == '\n') count_line += 1;
			ch = inputFile.get();
			continue;
		}

		// Round brackets
		else if (ch == '(') {
			inputTokens.push_back(Token{ Token::LP, Token::id2word[Token::LP] });
			ch = inputFile.get();
			continue;
		}
		else if (ch == ')') {
			inputTokens.push_back(Token{ Token::RP, Token::id2word[Token::RP] });
			ch = inputFile.get();
			continue;
		}

		// If I encounter a capital letter I have to understand 
		// if I'm parsing a keyword or a variable_id
		// So I load into a stringstream all the uppercase or lowercase 
		// alphabetic characters that I read after the capital letter and then 
		// I check if what I read is a keyword; if it is not, it is a variable_id
		else if (ch >= 'A' && ch <= 'Z') {
			std::stringstream tmp{};
			tmp << ch;
			while (true) {
				ch = inputFile.get();
				// "Loading" into tmp everything I read before a space or a parenthesis
				if (std::isspace(ch) || ch == ')' || ch == '(') break;
				tmp << ch;
			}
			// Check if tmp respects the grammar of the keywords or variables 
			// therefore if it contains only uppercase or lowercase alphabetic characters
			// is_alpha function implemented as 'static' method of the Utility class
			// in the "Utility.h" file
			if (Utility::is_alpha(tmp.str())) {
				// BLOCK
				if (tmp.str() == Token::id2word[Token::B])
					inputTokens.push_back(Token{ Token::B, Token::id2word[Token::B] });
				// SET
				else if (tmp.str() == Token::id2word[Token::SET])
					inputTokens.push_back(Token{ Token::SET, Token::id2word[Token::SET] });
				// PRINT
				else if (tmp.str() == Token::id2word[Token::PRI])
					inputTokens.push_back(Token{ Token::PRI, Token::id2word[Token::PRI] });
				// INPUT
				else if (tmp.str() == Token::id2word[Token::INP])
					inputTokens.push_back(Token{ Token::INP, Token::id2word[Token::INP] });
				// IF
				else if (tmp.str() == Token::id2word[Token::IF])
					inputTokens.push_back(Token{ Token::IF, Token::id2word[Token::IF] });
				// WHILE
				else if (tmp.str() == Token::id2word[Token::WHI])
					inputTokens.push_back(Token{ Token::WHI, Token::id2word[Token::WHI] });
				// ADD
				else if (tmp.str() == Token::id2word[Token::ADD])
					inputTokens.push_back(Token{ Token::ADD, Token::id2word[Token::ADD] });
				// SUB
				else if (tmp.str() == Token::id2word[Token::SUB])
					inputTokens.push_back(Token{ Token::SUB, Token::id2word[Token::SUB] });
				// MUL
				else if (tmp.str() == Token::id2word[Token::MUL])
					inputTokens.push_back(Token{ Token::MUL, Token::id2word[Token::MUL] });
				// DIV
				else if (tmp.str() == Token::id2word[Token::DIV])
					inputTokens.push_back(Token{ Token::DIV, Token::id2word[Token::DIV] });
				// LT
				else if (tmp.str() == Token::id2word[Token::LT])
					inputTokens.push_back(Token{ Token::LT, Token::id2word[Token::LT] });
				// GT
				else if (tmp.str() == Token::id2word[Token::GT])
					inputTokens.push_back(Token{ Token::GT, Token::id2word[Token::GT] });
				// EQ
				else if (tmp.str() == Token::id2word[Token::EQ])
					inputTokens.push_back(Token{ Token::EQ, Token::id2word[Token::EQ] });
				// AND
				else if (tmp.str() == Token::id2word[Token::AND])
					inputTokens.push_back(Token{ Token::AND, Token::id2word[Token::AND] });
				// OR
				else if (tmp.str() == Token::id2word[Token::OR])
					inputTokens.push_back(Token{ Token::OR, Token::id2word[Token::OR] });
				// NOT
				else if (tmp.str() == Token::id2word[Token::NOT])
					inputTokens.push_back(Token{ Token::NOT, Token::id2word[Token::NOT] });
				// TRUE
				else if (tmp.str() == Token::id2word[Token::T])
					inputTokens.push_back(Token{ Token::T, Token::id2word[Token::T] });
				// FALSE
				else if (tmp.str() == Token::id2word[Token::F])
					inputTokens.push_back(Token{ Token::F, Token::id2word[Token::F] });
				// Variable_id
				else
					inputTokens.push_back(Token{ Token::VAR, tmp.str() });
				continue;
			}
			// Lexical error
			else {
				std::stringstream error{};
				error << "the token " << tmp.str() << " at line " << count_line <<
					" is not valid, it doesn't respect the grammar";
				throw LexicalError(error.str());
			}
		}

		// Number
		else if (std::isdigit(ch) || ch == '-') {
			std::stringstream tmp{};
			tmp << ch;
			while (true) {
				ch = inputFile.get();
				// "Loading" into tmp everything I read before a space or a parenthesis
				if (std::isspace(ch) || ch == ')' || ch == '(') break;
				tmp << ch;
			}
			// Check if the read string is a number accepted by the grammar
			// isInteger function implemented as 'static' method 
			// of the Utility class in the "Utility.h" file
			if (Utility::isInteger(tmp.str())) inputTokens.push_back(Token{ Token::NUM, tmp.str() });
			else {
				std::stringstream error{};
				error << "the token " << tmp.str() << " at line " << count_line <<
					" is not valid, it doesn't respect the grammar";
				throw LexicalError(error.str());
			}
			continue;
		}

		// Variable_id
		// If I read a lowercase character I already know that it can only be a variable_id
		else if (ch >= 'a' && ch <= 'z') {
			std::stringstream tmp{};
			tmp << ch;
			while (true) {
				ch = inputFile.get();
				// "Loading" into tmp everything I read before a space or a parenthesis
				if (std::isspace(ch) || ch == ')' || ch == '(') break;
				tmp << ch;
			}
			// Check if the read string is a variable_id accepted by the grammar
			// is_alpha function implemented as 'static' method 
			// of the Utility class in the "Utility.h" file
			if (Utility::is_alpha(tmp.str())) inputTokens.push_back(Token{ Token::VAR, tmp.str() });
			else {
				std::stringstream error{};
				error << "the token " << tmp.str() << " at line " << count_line <<
					" is not valid, it doesn't respect the grammar";
				throw LexicalError(error.str());
			}
			continue;
		}

		// Handling all remaining lexical errors
		else {
			std::stringstream tmp{};
			tmp << "lexical error on the symbol " << ch << " at line " << count_line;
			throw LexicalError(tmp.str());
		}
	}
}