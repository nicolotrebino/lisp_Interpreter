#include "BoolExpr.h"
#include "Visitor.h"

void RelOp::accept(Visitor* v) {
	v->visitRelOp(this);
}

// Utility method to convert StringStream to RelOpCode
// used by the Parser
RelOp::RelOpCode RelOp::sstreamToRelOpCode(std::stringstream& ss) {
	std::string cleanedstring;
	ss >> std::ws >> cleanedstring;
	if (cleanedstring == "LT") return LT;
	else if (cleanedstring == "GT") return GT;
	else if (cleanedstring == "EQ") return EQ;
	else throw std::runtime_error("invalid RelOpCode");
}

// Utility method to convert OpCode to StringStream
// used by the PrintVisitor
std::stringstream RelOp::RelOpCodeToSStream(RelOpCode op) {
	std::stringstream ss;
	switch (op) {
	case LT: ss << "LT"; break;
	case GT: ss << "GT"; break;
	case EQ: ss << "EQ"; break;
	}
	return ss;
}

void BoolConst::accept(Visitor* v) {
	v->visitBoolConst(this);
}

// Utility method to convert StringStream to BoolConst
// used by the Parser
bool BoolConst::sstreamToBoolConst(std::stringstream& ss) {
	std::string cleanedstring;
	ss >> std::ws >> cleanedstring;
	if (cleanedstring == "TRUE") return true;
	else if (cleanedstring == "FALSE") return false;
	else throw std::runtime_error("invalid BoolConst");
}

void BoolOp::accept(Visitor* v) {
	v->visitBoolOp(this);
}

// Utility method to convert StringStream to BoolOpCode
// used by the Parser
BoolOp::BoolOpCode BoolOp::sstreamToBoolOpCode(std::stringstream& ss) {
	std::string cleanedstring;
	ss >> std::ws >> cleanedstring;
	if (cleanedstring == "AND") return AND;
	else if (cleanedstring == "OR") return OR;
	else if (cleanedstring == "NOT") return NOT;
	else throw std::runtime_error("invalid BoolOpCode");
}

// Utility method to convert OpCode to StringStream
// used by the PrintVisitor
std::stringstream BoolOp::BoolOpCodeToSStream(BoolOpCode op) {
	std::stringstream ss;
	switch (op) {
	case AND: ss << "AND"; break;
	case OR: ss << "OR"; break;
	case NOT: ss << "NOT"; break;
	}
	return ss;
}