#include "Utility.h"

// Utility function to recognize if a string
// is an integer accepted by the grammar
bool Utility::isInteger(const std::string& str) {
	size_t start = 0;
	// Check for the '-' for negative numbers
	if (str[0] == '-') {
		start = 1;
	}
	if (str[start] == '0') {
		if (str.size() > start + 1 && std::isdigit(str[start + 1])) {
			return false;
		}
	}
	// Check that all characters are digits
	for (size_t i = start; i < str.size(); ++i) {
		if (!std::isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

// Utility function to recognize if a string
// is a variable or keyword
// accepted by the grammar
bool Utility::is_alpha(const std::string& str) {
	for (char c : str) {
		if (!isalpha(c)) {
			return 0;
		}
	}
	return 1;
}