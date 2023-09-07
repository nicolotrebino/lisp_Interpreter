#ifndef STATEMENT_H
#define STATEMENT_H

#include "NumExpr.h"
#include "BoolExpr.h"

// "Forward" declaration of the Visitor class
// The class is implemented in another module
class Visitor;

// "Forward" declaration of the Block class
// The class is implemented in another module
class Block;

class Statement {
public:
	virtual ~Statement() {};
	virtual void accept(Visitor* v) = 0;
};

// Set
class SetStmt : public Statement {
public:
	SetStmt(Variable* var, NumExpr* ne) : variable{ var }, numexpr{ ne } {}
	~SetStmt() = default;
	SetStmt(const SetStmt& other) = default;

	Variable* getVar() const {
		return variable;
	}

	NumExpr* getNumExpr() const {
		return numexpr;
	}

	void accept(Visitor* v) override;

private:
	Variable* variable;
	NumExpr* numexpr;
};

// Print
class PrintStmt : public Statement {
public:
	PrintStmt(NumExpr* ne) : numexpr{ ne } {}
	~PrintStmt() = default;
	PrintStmt(const PrintStmt& other) = default;

	NumExpr* getNumexpr() {
		return numexpr;
	}

	void accept(Visitor* v) override;

private:
	NumExpr* numexpr;
};

// Input
class InputStmt : public Statement {
public:
	InputStmt(Variable* var) : variable{ var } {}
	~InputStmt() = default;
	InputStmt(const InputStmt& other) = default;

	Variable* getVar() {
		return variable;
	}

	void accept(Visitor* v) override;

private:
	Variable* variable;
};

// While
class WhileStmt : public Statement {
public:
	WhileStmt(BoolExpr* be, Block* b) : boolexpr{ be }, block{ b } {}
	~WhileStmt() = default;
	WhileStmt(const WhileStmt& other) = default;

	BoolExpr* getBoolExpr() {
		return boolexpr;
	}

	Block* getBlock() {
		return block;
	}

	void accept(Visitor* v) override;

private:
	BoolExpr* boolexpr;
	Block* block;
};

// If
class IfStmt : public Statement {
public:
	IfStmt(BoolExpr* be, Block* lb, Block* rb) : boolexpr{ be }, left_block{ lb }, right_block{ rb } {}
	~IfStmt() = default;
	IfStmt(const IfStmt& other) = default;

	BoolExpr* getBoolExpr() {
		return boolexpr;
	}

	Block* getLeftB() {
		return left_block;
	}

	Block* getRightB() {
		return right_block;
	}

	void accept(Visitor* v) override;

private:
	BoolExpr* boolexpr;
	Block* left_block;
	Block* right_block;
};
#endif
