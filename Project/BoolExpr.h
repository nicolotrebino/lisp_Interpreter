#ifndef BOOLEXPR_H
#define BOOLEXPR_H

#include <sstream>

#include "NumExpr.h"

// "Forward" declaration of the Visitor class
// The class is implemented in another module
class Visitor;

class BoolExpr {
public:
	virtual ~BoolExpr() {};
	virtual void accept(Visitor* v) = 0;
};

// Relational Operator
class RelOp : public BoolExpr {
public:
	enum RelOpCode { LT, GT, EQ };

	RelOp(RelOpCode o, NumExpr* lop, NumExpr* rop) :
		relop{ o }, left{ lop }, right{ rop } { }
	~RelOp() = default;
	RelOp(const RelOp& other) = default;
	RelOp& operator=(const RelOp& other) = default;

	RelOpCode getRelOp() const {
		return relop;
	}

	NumExpr* getLeft() const {
		return left;
	}

	NumExpr* getRight() const {
		return right;
	}

	void accept(Visitor* v) override;

	// Utility method to convert StringStream to RelOpCode
	// used by the Parser
	static RelOpCode sstreamToRelOpCode(std::stringstream& ss);

	// Utility method to convert OpCode to StringStream
	// used by the PrintVisitor
	static std::stringstream RelOpCodeToSStream(RelOpCode op);

private:
	RelOpCode relop;
	NumExpr* left;
	NumExpr* right;
};

// Boolean Constant
class BoolConst : public BoolExpr {
public:
	BoolConst(bool b) : bc{ b } { }
	~BoolConst() = default;
	BoolConst(const BoolConst& other) = default;
	BoolConst& operator=(const BoolConst& other) = default;

	bool getBool() const {
		return bc;
	}

	void accept(Visitor* v) override;

	// Utility method to convert StringStream to BoolConst
	// used by the Parser
	static bool sstreamToBoolConst(std::stringstream& ss);

private:
	bool bc;
};

// Boolean Operator
class BoolOp : public BoolExpr {
public:
	enum BoolOpCode { AND, OR, NOT };

	BoolOp(BoolOpCode o, BoolExpr* lop, BoolExpr* rop) :
		boolop{ o }, left{ lop }, right{ rop } { }
	~BoolOp() = default;
	BoolOp(const BoolOp& other) = default;
	BoolOp& operator=(const BoolOp& other) = default;

	BoolOpCode getBoolOp() const {
		return boolop;
	}

	BoolExpr* getLeft() const {
		return left;
	}

	BoolExpr* getRight() const {
		return right;
	}

	void accept(Visitor* v) override;

	// Utility method to convert StringStream to BoolOpCode
	// used by the Parser
	static BoolOpCode sstreamToBoolOpCode(std::stringstream& ss);

	// Utility method to convert OpCode to StringStream
	// used by the PrintVisitor
	static std::stringstream BoolOpCodeToSStream(BoolOpCode op);

private:
	BoolOpCode boolop;
	BoolExpr* left;
	BoolExpr* right;
};
#endif
