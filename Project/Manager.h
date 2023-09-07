#ifndef MANAGER_H
#define MANAGER_H

#include <vector>

#include "Block.h"
#include "Statement.h"
#include "NumExpr.h"
#include "BoolExpr.h"

// Block Manager
class BlockManager {
public:
    BlockManager() = default;
    ~BlockManager() {
        clearMemory();
    }

    BlockManager(const BlockManager& other) = delete;
    BlockManager& operator=(const BlockManager& other) = delete;

    // Make Block
    Block* makeBlock(std::vector<Statement*> vs) {
        Block* b = new Block(vs);
        allocated.push_back(b);
        return b;
    }

    void clearMemory() {
        auto i = allocated.begin();
        for (; i != allocated.end(); ++i) {
            delete(*i);
        }
        allocated.resize(0);
    }

private:
    std::vector<Block*> allocated;
};

// Statement Manager
class StmtManager {
public:
    StmtManager() = default;
    ~StmtManager() {
        clearMemory();
    }

    StmtManager(const StmtManager& other) = delete;
    StmtManager& operator=(const StmtManager& other) = delete;

    // Make SetStmt
    Statement* makeSetStmt(Variable* v, NumExpr* ne) {
        Statement* ss = new SetStmt(v, ne);
        allocated.push_back(ss);
        return ss;
    }

    // Make PrintStmt
    Statement* makePrintStmt(NumExpr* ne) {
        Statement* ps = new PrintStmt(ne);
        allocated.push_back(ps);
        return ps;
    }

    // Make InputStmt
    Statement* makeInputStmt(Variable* v) {
        Statement* is = new InputStmt(v);
        allocated.push_back(is);
        return is;
    }

    // Make WhileStmt
    Statement* makeWhileStmt(BoolExpr* be, Block* b) {
        Statement* ws = new WhileStmt(be, b);
        allocated.push_back(ws);
        return ws;
    }

    // Make IfStmt
    Statement* makeIfStmt(BoolExpr* be, Block* lb, Block* rb) {
        Statement* ifs = new IfStmt(be, lb, rb);
        allocated.push_back(ifs);
        return ifs;
    }

    void clearMemory() {
        auto i = allocated.begin();
        for (; i != allocated.end(); ++i) {
            delete(*i);
        }
        allocated.resize(0);
    }

private:
    std::vector<Statement*> allocated;
};

// NumExpr Manager
class NumExprManager {
public:
    NumExprManager() = default;
    ~NumExprManager() {
        clearMemory();
    }

    NumExprManager(const NumExprManager& other) = delete;
    NumExprManager& operator=(const NumExprManager& other) = delete;

    // Make Number
    NumExpr* makeNumber(int64_t value) {
        NumExpr* n = new Number(value);
        allocated.push_back(n);
        return n;
    }

    // Make Arithmetic Operator
    NumExpr* makeArOperator(ArOp::ArOpCode op, NumExpr* l, NumExpr* r) {
        NumExpr* o = new ArOp(op, l, r);
        allocated.push_back(o);
        return o;
    }

    // Crea Variable
    NumExpr* makeVariable(std::string var) {
        NumExpr* v = new Variable(var);
        allocated.push_back(v);
        return v;
    }

    void clearMemory() {
        auto i = allocated.begin();
        for (; i != allocated.end(); ++i) {
            delete(*i);
        }
        allocated.resize(0);
    }

private:
    std::vector<NumExpr*> allocated;
};

// BoolExpr Manager
class BoolExprManager {
public:
    BoolExprManager() = default;
    ~BoolExprManager() {
        clearMemory();
    }

    BoolExprManager(const BoolExprManager& other) = delete;
    BoolExprManager& operator=(const BoolExprManager& other) = delete;

    // Make Relational Operator
    BoolExpr* makeRelOperator(RelOp::RelOpCode op, NumExpr* l, NumExpr* r) {
        BoolExpr* rop = new RelOp(op, l, r);
        allocated.push_back(rop);
        return rop;
    }

    // Make Boolean Constant
    BoolExpr* makeBoolConst(bool value) {
        BoolExpr* bc = new BoolConst(value);
        allocated.push_back(bc);
        return bc;
    }

    // Make Boolean Operator
    BoolExpr* makeBoolOperator(BoolOp::BoolOpCode op, BoolExpr* l, BoolExpr* r) {
        BoolExpr* bop = new BoolOp(op, l, r);
        allocated.push_back(bop);
        return bop;
    }

    void clearMemory() {
        auto i = allocated.begin();
        for (; i != allocated.end(); ++i) {
            delete(*i);
        }
        allocated.resize(0);
    }

private:
    std::vector<BoolExpr*> allocated;
};
#endif
