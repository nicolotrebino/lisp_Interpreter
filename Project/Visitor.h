#ifndef VISITOR_H
#define VISITOR_H

#include <iostream>
#include <vector>

#include "Exceptions.h"
#include "Program.h"
#include "Block.h"
#include "Statement.h"
#include "NumExpr.h"
#include "BoolExpr.h"
#include "VariableTable.h"
#include "Utility.h"

class Visitor {
public:
	virtual void visitArOperator(ArOp* ArOpNode) = 0;
	virtual void visitNumber(Number* numNode) = 0;
	virtual void visitVariable(Variable* varNode) = 0;
	virtual void visitRelOp(RelOp* RelOpNode) = 0;
	virtual void visitBoolConst(BoolConst* boolNode) = 0;
	virtual void visitBoolOp(BoolOp* BoolOpNode) = 0;
	virtual void visitSetStmt(SetStmt* setNode) = 0;
	virtual void visitPrintStmt(PrintStmt* printNode) = 0;
	virtual void visitInputStmt(InputStmt* inputNode) = 0;
	virtual void visitWhileStmt(WhileStmt* whileNode) = 0;
	virtual void visitIfStmt(IfStmt* ifNode) = 0;
	virtual void visitBlock(Block* blockNode) = 0;
	virtual void visitProgram(Program* programNode) = 0;
};

// Concrete visitor for program evaluation
class EvaluationVisitor : public Visitor {
public:
	EvaluationVisitor(VariableTable& vart) : accumulator{ }, vt{ vart } { }
	~EvaluationVisitor() = default;
	EvaluationVisitor(const EvaluationVisitor& other) = default;

	void visitArOperator(ArOp* ArOpNode) override;
	void visitNumber(Number* numNode) override;
	void visitVariable(Variable* varNode) override;
	void visitRelOp(RelOp* RelOpNode) override;
	void visitBoolConst(BoolConst* boolNode) override;
	void visitBoolOp(BoolOp* BoolOpNode) override;
	void visitSetStmt(SetStmt* setNode) override;
	void visitPrintStmt(PrintStmt* printNode) override;
	void visitInputStmt(InputStmt* inputNode) override;
	void visitWhileStmt(WhileStmt* whileNode) override;
	void visitIfStmt(IfStmt* ifNode) override;
	void visitBlock(Block* blockNode) override;
	void visitProgram(Program* programNode) override;

	int64_t getValue() const;

private:
	std::vector<int64_t> accumulator;
	VariableTable& vt;
};

// Concrete Visitor for printing the program
// PrintVisitor is not strictly necessary for
// the correct and complete functioning of the interpreter
// but very useful for DEBUG and for future updates
// of the project itself
class PrintVisitor : public Visitor {
public:
	void visitArOperator(ArOp* ArOpNode) override;
	void visitNumber(Number* numNode) override;
	void visitVariable(Variable* varNode) override;
	void visitRelOp(RelOp* RelOpNode) override;
	void visitBoolConst(BoolConst* boolNode) override;
	void visitBoolOp(BoolOp* BoolOpNode) override;
	void visitSetStmt(SetStmt* setNode) override;
	void visitPrintStmt(PrintStmt* printNode) override;
	void visitInputStmt(InputStmt* inputNode) override;
	void visitWhileStmt(WhileStmt* whileNode) override;
	void visitIfStmt(IfStmt* ifNode) override;
	void visitBlock(Block* blockNode) override;
	void visitProgram(Program* programNode) override;
};
#endif
