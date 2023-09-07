#include "Visitor.h"

void EvaluationVisitor::visitArOperator(ArOp* ArOpNode) {
	NumExpr* left = ArOpNode->getLeft();
	left->accept(this);
	NumExpr* right = ArOpNode->getRight();
	right->accept(this);
	int64_t rval = accumulator.back(); accumulator.pop_back();
	int64_t lval = accumulator.back(); accumulator.pop_back();
	switch (ArOpNode->getArOp()) {
	case ArOp::ADD:
		accumulator.push_back(lval + rval); return;
	case ArOp::SUB:
		accumulator.push_back(lval - rval); return;
	case ArOp::MUL:
		accumulator.push_back(lval * rval); return;
	case ArOp::DIV:
		if (rval == 0) {
			throw EvaluationError("division by zero");
		}
		accumulator.push_back(lval / rval); return;
	default:
		return;
	}
}
void EvaluationVisitor::visitNumber(Number* numNode) {
	accumulator.push_back(numNode->getValue());
}
void EvaluationVisitor::visitVariable(Variable* varNode) {
	accumulator.push_back(vt.getVar(varNode->getName()));
}
void EvaluationVisitor::visitRelOp(RelOp* RelOpNode) {
	NumExpr* left = RelOpNode->getLeft();
	left->accept(this);
	NumExpr* right = RelOpNode->getRight();
	right->accept(this);
	int64_t rval = accumulator.back(); accumulator.pop_back();
	int64_t lval = accumulator.back(); accumulator.pop_back();
	switch (RelOpNode->getRelOp()) {
	case RelOp::LT:
		accumulator.push_back(lval < rval); return;
	case RelOp::GT:
		accumulator.push_back(lval > rval); return;
	case RelOp::EQ:
		accumulator.push_back(lval == rval); return;
	default:
		return;
	}
}
void EvaluationVisitor::visitBoolConst(BoolConst* boolNode) {
	accumulator.push_back(boolNode->getBool());
}
void EvaluationVisitor::visitBoolOp(BoolOp* BoolOpNode) {
	if (BoolOpNode->getBoolOp() == BoolOp::NOT) {
		BoolExpr* left = BoolOpNode->getLeft();
		left->accept(this);
		int64_t lval = accumulator.back(); accumulator.pop_back();
		if (lval == 0) accumulator.push_back(1);
		else accumulator.push_back(0);
	}
	else if (BoolOpNode->getBoolOp() == BoolOp::AND) {
		BoolExpr* left = BoolOpNode->getLeft();
		left->accept(this);
		int64_t lval = accumulator.back(); accumulator.pop_back();
		if (lval == 0) { accumulator.push_back(0); return; }
		BoolExpr* right = BoolOpNode->getRight();
		right->accept(this);
		int64_t rval = accumulator.back(); accumulator.pop_back();
		if (rval == 0) { accumulator.push_back(0); return; }
		else accumulator.push_back(1);
	}
	else if (BoolOpNode->getBoolOp() == BoolOp::OR) {
		BoolExpr* left = BoolOpNode->getLeft();
		left->accept(this);
		BoolExpr* right = BoolOpNode->getRight();
		right->accept(this);
		int64_t rval = accumulator.back(); accumulator.pop_back();
		int64_t lval = accumulator.back(); accumulator.pop_back();
		if (lval != 0) accumulator.push_back(1);
		else if (rval != 0) accumulator.push_back(1);
		else accumulator.push_back(0);
	}
	else return;
}
void EvaluationVisitor::visitSetStmt(SetStmt* setNode) {
	NumExpr* numexpr = setNode->getNumExpr();
	numexpr->accept(this);
	int64_t value = accumulator.back(); accumulator.pop_back();
	vt.setVar(setNode->getVar()->getName(), value);
}
void EvaluationVisitor::visitPrintStmt(PrintStmt* printNode) {
	NumExpr* numexpr = printNode->getNumexpr();
	numexpr->accept(this);
	int64_t value = accumulator.back();
	std::cout << value << std::endl;
}
void EvaluationVisitor::visitInputStmt(InputStmt* inputNode) {
	Variable* var = inputNode->getVar();
	std::string value{};
	std::cin >> value;
	// isInteger function implemented as 'static' method
	// of the Utility class in the "Utility.h" file
	if (Utility::isInteger(value)) vt.setVar(var->getName(), std::stoll(value));
	else throw EvaluationError("the input is not a valid integer for the grammar");
}
void EvaluationVisitor::visitWhileStmt(WhileStmt* whileNode) {
	BoolExpr* boolexpr = whileNode->getBoolExpr();
	boolexpr->accept(this);
	int64_t value = accumulator.back(); accumulator.pop_back();
	while (value) {
		Block* block = whileNode->getBlock();
		block->accept(this);
		boolexpr->accept(this);
		value = accumulator.back(); accumulator.pop_back();
	}
}
void EvaluationVisitor::visitIfStmt(IfStmt* ifNode) {
	BoolExpr* boolexpr = ifNode->getBoolExpr();
	boolexpr->accept(this);
	int64_t value = accumulator.back(); accumulator.pop_back();
	if (value) {
		Block* block = ifNode->getLeftB();
		block->accept(this);
	}
	else {
		Block* block = ifNode->getRightB();
		block->accept(this);
	}
}
void EvaluationVisitor::visitBlock(Block* blockNode) {
	for (int i = 0; i < blockNode->getStmtList().size(); i++) {
		Statement* stmt = blockNode->getStmt(i);
		stmt->accept(this);
	}
}
void EvaluationVisitor::visitProgram(Program* programNode) {
	Block* block = programNode->getProgram();
	block->accept(this);
}
int64_t EvaluationVisitor::getValue() const {
	return accumulator.back();
}

void PrintVisitor::visitArOperator(ArOp* ArOpNode) {
	std::cout << "(";
	std::cout << ArOp::ArOpCodeToSStream(ArOpNode->getArOp()).str() << " ";
	ArOpNode->getLeft()->accept(this);
	ArOpNode->getRight()->accept(this);
	std::cout << ")" << std::endl;
}
void PrintVisitor::visitNumber(Number* numNode) {
	std::cout << numNode->getValue() << " ";
}
void PrintVisitor::visitVariable(Variable* varNode) {
	std::cout << varNode->getName() << " ";
}
void PrintVisitor::visitRelOp(RelOp* RelOpNode) {
	std::cout << "(";
	std::cout << RelOp::RelOpCodeToSStream(RelOpNode->getRelOp()).str() << " ";
	RelOpNode->getLeft()->accept(this);
	RelOpNode->getRight()->accept(this);
	std::cout << ")" << std::endl;
}
void PrintVisitor::visitBoolConst(BoolConst* boolNode) {
	if (boolNode->getBool()) std::cout << "TRUE";
	else std::cout << "FALSE";
}
void PrintVisitor::visitBoolOp(BoolOp* BoolOpNode) {
	std::cout << "(";
	if (BoolOp::BoolOpCodeToSStream(BoolOpNode->getBoolOp()).str() == "NOT") {
		std::cout << BoolOp::BoolOpCodeToSStream(BoolOpNode->getBoolOp()).str() << " ";
		BoolOpNode->getLeft()->accept(this);
		std::cout << ")" << std::endl;
	}
	else {
		std::cout << BoolOp::BoolOpCodeToSStream(BoolOpNode->getBoolOp()).str() << " ";
		BoolOpNode->getLeft()->accept(this);
		BoolOpNode->getRight()->accept(this);
		std::cout << ")" << std::endl;
	}
}
void PrintVisitor::visitSetStmt(SetStmt* setNode) {
	std::cout << "(SET ";
	setNode->getVar()->accept(this);
	setNode->getNumExpr()->accept(this);
	std::cout << ")" << std::endl;
}
void PrintVisitor::visitPrintStmt(PrintStmt* printNode) {
	std::cout << "(PRINT ";
	printNode->getNumexpr()->accept(this);
	std::cout << ")" << std::endl;
}
void PrintVisitor::visitInputStmt(InputStmt* inputNode) {
	std::cout << "(INPUT ";
	inputNode->getVar()->accept(this);
	std::cout << ")" << std::endl;
}
void PrintVisitor::visitWhileStmt(WhileStmt* whileNode) {
	std::cout << "(WHILE ";
	whileNode->getBoolExpr()->accept(this);
	whileNode->getBlock()->accept(this);
	std::cout << ")" << std::endl;
}
void PrintVisitor::visitIfStmt(IfStmt* ifNode) {
	std::cout << "(IF ";
	ifNode->getBoolExpr()->accept(this);
	ifNode->getLeftB()->accept(this);
	ifNode->getRightB()->accept(this);
	std::cout << ")" << std::endl;
}
void PrintVisitor::visitBlock(Block* blockNode) {
	if (blockNode->getStmtList().size() > 1) {
		std::cout << "(BLOCK" << std::endl;
		int i = 0;
		while (i < blockNode->getStmtList().size()) {
			blockNode->getStmt(i)->accept(this);
			i += 1;
		}
		std::cout << ")" << std::endl;
	}
	else if (blockNode->getStmtList().size() == 1) {
		blockNode->getStmt(0)->accept(this);
	}
}
void PrintVisitor::visitProgram(Program* programNode) {
	programNode->getProgram()->accept(this);
}

