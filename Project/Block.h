#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

#include "Statement.h"

// "Forward" declaration of the Visitor class
// The class is implemented in another module
class Visitor;

class Block {
public:
	Block(std::vector<Statement*> vs) : stmt_list{ vs } {}
	~Block() = default;
	Block(const Block& other) = default;

	std::vector<Statement*> getStmtList() const {
		return stmt_list;
	}

	Statement* getStmt(const int i) const {
		return stmt_list[i];
	}

	void accept(Visitor* v);

private:
	std::vector<Statement*> stmt_list;
};
#endif
