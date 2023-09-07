#ifndef UTILITY_H
#define UTILITY_H

#include <sstream>

// I define and implement these utility functions
// as 'static' methods of a new Utility class
// in this separate header file because they might
// serve myself on multiple .cpp files in the future

class Utility {
public:
	// For example I use isInteger in the Tokenizer
	// and in the EvaluationVisitor so this
	// implementation is useful to me

	// The same doesn't happen with is_alpha, which instead
	// is only used by the Tokenizer, but if in
	// future someone will want to expand the program
	// using is_alpha as a utility function in others
	// .cpp files, this implementation might make things easier

	// Utility function to recognize if a string
	// is an integer accepted by the grammar
	static bool isInteger(const std::string& str);

	// Utility function to recognize if a string
	// is a variable or keyword
	// accepted by the grammar
	static bool is_alpha(const std::string& str);
};
#endif

