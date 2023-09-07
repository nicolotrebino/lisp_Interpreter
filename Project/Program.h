#ifndef PROGRAM_H
#define PROGRAM_H

#include "Block.h"

// "Forward" declaration of the Visitor class
// The class is implemented in another module
class Visitor;

class Program {
public:
	Program() = default;
	Program(Block* p) : program{ p } {}
	~Program() = default;
	Program(const Program& other) = default;

	Block* getProgram() const {
		return program;
	}

	void accept(Visitor* v);

private:
	Block* program;
};
#endif
