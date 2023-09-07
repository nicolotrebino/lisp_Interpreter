#include "NumExpr.h"
#include "Visitor.h"

void ArOp::accept(Visitor* v) {
	v->visitArOperator(this);
}

// Utility method to convert StringStream to OpCode
// used by the Parser
ArOp::ArOpCode ArOp::sstreamToArOpCode(std::stringstream& ss) {
	std::string cleanedstring;
	ss >> std::ws >> cleanedstring;
	if (cleanedstring == "ADD") return ADD;
	else if (cleanedstring == "SUB") return SUB;
	else if (cleanedstring == "MUL") return MUL;
	else if (cleanedstring == "DIV") return DIV;
	else throw std::runtime_error("invalid ArOpCode");
}

// Utility method to convert OpCode to StringStream
// used by the PrintVisitor
std::stringstream ArOp::ArOpCodeToSStream(ArOpCode op) {
	std::stringstream ss;
	switch (op) {
	case ADD: ss << "ADD"; break;
	case SUB: ss << "SUB"; break;
	case MUL: ss << "MUL"; break;
	case DIV: ss << "DIV"; break;
	}
	return ss;
}

void Number::accept(Visitor* v) {
	v->visitNumber(this);
}

void Variable::accept(Visitor* v) {
	v->visitVariable(this);
}
