#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>

#include "Exceptions.h"
#include "Token.h"
#include "Manager.h"
#include "Program.h"

class ParseProgram {
public:
    ParseProgram(BlockManager& bmanager, StmtManager& smanager,
        NumExprManager& nemanager, BoolExprManager& bemanager) :
        bm{ bmanager }, sm{ smanager }, nem{ nemanager }, bem{ bemanager } { }

    Program* operator()(const std::vector<Token>& inputTokens) {
        // The programmer can choose whether to read a file
        // empty will lead to an error, or parsing
        // and on subsequent evaluation 
        // with an empty output
        /*
        if (inputTokens.empty()) {
            return new Program();
        }
        */
        // I choose to throw an error
        if (inputTokens.empty()) {
            throw std::runtime_error("empty program");
        }
        auto tokenItr = inputTokens.begin();
        streamEnd = inputTokens.end();
        Block* program = parseStmtBlock(tokenItr);
        // Check if I've reached the end of the inputTokens
        if (tokenItr != streamEnd) {
            throw ParseError("unexpected stop, check if there are multiple"
                " Stmts not enclosed by a Stmt_Block");
        }
        return new Program(program);
    }

private:
    std::vector<Token>::const_iterator streamEnd;

    // Reference to the Block Manager
    BlockManager& bm;

    // Reference to the Statement Manager
    StmtManager& sm;

    // Reference to the NumExpr Manager
    NumExprManager& nem;

    // Reference to the BoolExpr Manager
    BoolExprManager& bem;

    // Function for parsing a number
    NumExpr* parseNumber(std::vector<Token>::const_iterator& tokenItr);

    // Function for parsing a variable
    NumExpr* parseVariable(std::vector<Token>::const_iterator& tokenItr);

    // Function for parsing a NumExpr
    NumExpr* recursiveParseNumExpr(std::vector<Token>::const_iterator& tokenItr);

    // Function for parsing a BoolExpr
    BoolExpr* recursiveParseBoolExpr(std::vector<Token>::const_iterator& tokenItr);

    // Function for parsing a Statement
    Statement* recursiveParseStmt(std::vector<Token>::const_iterator& tokenItr);

    // Function for parsing a Stmt_Block
    Block* parseStmtBlock(std::vector<Token>::const_iterator& tokenItr);

    // Safe progress of an iterator
    void safe_next(std::vector<Token>::const_iterator& itr) {
        if (itr == streamEnd) {
            throw ParseError("overflow in token stream");
        }
        ++itr;
    }

    // I check if I haven't reached the end of the Vector
    // I need to call this method before each comparison
    // which requires the use of an iterator; because if
    // the iterator has reached the end of the Vector the comparison
    // results in an error
    void check_end(std::vector<Token>::const_iterator& itr) {
        if (itr == streamEnd) {
            throw ParseError("overflow in token stream");
        }
    }

    // Utility functions to recognize the Token read
    // I define these methods as 'private' because
    // are used in this application
    // from class methods only
    // ParseProgram itself
    // No need to make them 'public'
    inline bool isStmt(int tag);
    inline bool isArOperator(int tag);
    inline bool isRelOperator(int tag);
    inline bool isBoolOperator(int tag);
    inline bool isBoolConst(int tag);
};
#endif