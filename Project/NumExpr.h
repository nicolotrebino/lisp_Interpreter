#ifndef NUMEXPR_H
#define NUMEXPR_H

#include <string>
#include <sstream>

// "Forward" declaration of the Visitor class
// The class is implemented in another module
class Visitor;

class NumExpr {
public:
	virtual ~NumExpr() {};
	virtual void accept(Visitor* v) = 0;
};

// Arithmetic Operator
class ArOp : public NumExpr {
public:
	enum ArOpCode { ADD, SUB, MUL, DIV };

	ArOp(ArOpCode o, NumExpr* lop, NumExpr* rop) :
		op{ o }, left{ lop }, right{ rop } { }
	~ArOp() = default;
	ArOp(const ArOp& other) = default;
	ArOp& operator=(const ArOp& other) = default;

	ArOpCode getArOp() const {
		return op;
	}

	NumExpr* getLeft() const {
		return left;
	}

	NumExpr* getRight() const {
		return right;
	}

	void accept(Visitor* v) override;

	// Utility method to convert StringStream to OpCode
	// used by the Parser
	static ArOpCode sstreamToArOpCode(std::stringstream& ss);

	// Utility method to convert OpCode to StringStream
	// used by the PrintVisitor
	static std::stringstream ArOpCodeToSStream(ArOpCode op);

private:
	ArOpCode op;
	NumExpr* left;
	NumExpr* right;
};

// Number
class Number : public NumExpr {
public:
	Number(int64_t v) : value{ v } {}
	~Number() = default;
	Number(const Number& other) = default;
	Number& operator=(const Number& other) = default;

	int64_t getValue() const {
		return value;
	}

	void accept(Visitor* v) override;

private:
	int64_t value;
};

// Variable
class Variable : public NumExpr {
public:
	Variable(const std::string& n) : name{ n } {}
	~Variable() = default;
	Variable(const Variable& other) = default;
	Variable& operator=(const Variable& other) = default;

	std::string getName() const {
		return name;
	}

	void accept(Visitor* v) override;

private:
	std::string name;
};
#endif
