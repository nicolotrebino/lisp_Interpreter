#include <sstream>

#include "Parser.h"

// Utility function to recognize a Statement
inline bool ParseProgram::isStmt(int tag) {
    return tag == 3 || tag == 4 || tag == 5
        || tag == 6 || tag == 7;
}

// Utility function to recognize an Arithmetic Operator
inline bool ParseProgram::isArOperator(int tag) {
    return tag == 8 || tag == 9 || tag == 10 || tag == 11;
}

// Utility function to recognize a Relational Operator
inline bool ParseProgram::isRelOperator(int tag) {
    return tag == 12 || tag == 13 || tag == 14;
}

// Utility function to recognize a Boolean Operator
inline bool ParseProgram::isBoolOperator(int tag) {
    return tag == 15 || tag == 16 || tag == 17;
}

// Utility function to recognize a Boolean Constant
inline bool ParseProgram::isBoolConst(int tag) {
    return tag == 18 || tag == 19;
}

// Function for "building" a number
NumExpr* ParseProgram::parseNumber(std::vector<Token>::const_iterator& itr) {
    // Storing the number
    std::stringstream temp{};
    temp << itr->word;
    int value;
    temp >> value;
    return nem.makeNumber(value);
}

// Function for "building" a variable
NumExpr* ParseProgram::parseVariable(std::vector<Token>::const_iterator& itr) {
    return nem.makeVariable(itr->word);
}

// Function for parsing and "building" an arithmetic expression
NumExpr* ParseProgram::recursiveParseNumExpr(std::vector<Token>::const_iterator& itr) {
    check_end(itr);
    // Parsing a NumExpr
    if (itr->tag == Token::LP) {
        safe_next(itr);
        check_end(itr);
        // If I read an arithmetic operator I expect
        // two numeric expressions
        if (isArOperator(itr->tag)) {
            // Storing the arithmetic operator
            std::stringstream temp{};
            temp << itr->word;
            safe_next(itr);

            NumExpr* left = recursiveParseNumExpr(itr);
            safe_next(itr);

            NumExpr* right = recursiveParseNumExpr(itr);
            safe_next(itr);

            check_end(itr);
            if (itr->tag != Token::RP) {
                std::stringstream tmp{};
                tmp << "mismatched parenthesis at token '" << itr->tag << ";"
                    << itr->word << "'";
                throw ParseError(tmp.str());
            }
            return nem.makeArOperator(ArOp::sstreamToArOpCode(temp), left, right);
        }
        // If after a left parenthesis I don't have a keyword
        // related to an arithmetic operator 
        // I have a syntax error
        else {
            std::stringstream tmp{};
            tmp << "unrecognized operator " << itr->word;
            throw ParseError(tmp.str());
            return nullptr;
        }
    }
    // Parsing a number
    else if (itr->tag == Token::NUM) {
        return parseNumber(itr);
    }
    // Parsing a variable
    else if (itr->tag == Token::VAR) {
        return parseVariable(itr);
    }
    // Syntax error
    else {
        std::stringstream tmp{};
        tmp << "unexpected token '" << itr->word << "'";
        throw ParseError(tmp.str());
        return nullptr;
    }
}

// Function for parsing and "building" a boolean expression
BoolExpr* ParseProgram::recursiveParseBoolExpr(std::vector<Token>::const_iterator& itr) {
    check_end(itr);
    // Parsing a BoolExpr
    if (itr->tag == Token::LP) {
        safe_next(itr);
        check_end(itr);
        // If I read a relational operator I expect
        // two numeric expressions
        if (isRelOperator(itr->tag)) {
            // Storing the relational operator
            std::stringstream temp{};
            temp << itr->word;
            safe_next(itr);

            NumExpr* left = recursiveParseNumExpr(itr);
            safe_next(itr);

            NumExpr* right = recursiveParseNumExpr(itr);
            safe_next(itr);

            check_end(itr);
            if (itr->tag != Token::RP) {
                std::stringstream tmp{};
                tmp << "mismatched parenthesis at token '" << itr->tag << ";"
                    << itr->word << "'";
                throw ParseError(tmp.str());
            }
            safe_next(itr);
            return bem.makeRelOperator(RelOp::sstreamToRelOpCode(temp), left, right);
        }
        // If I read a boolean operator I expect 
        // a boolean expression for NOT and 
        // two boolean expressions for OR and AND
        else if (isBoolOperator(itr->tag)) {
            // NOT
            if (itr->tag == Token::NOT) {
                // Storing the boolean operator
                std::stringstream temp{};
                temp << itr->word;
                safe_next(itr);

                BoolExpr* be = recursiveParseBoolExpr(itr);

                check_end(itr);
                if (itr->tag != Token::RP) {
                    std::stringstream tmp{};
                    tmp << "mismatched parenthesis at token '" << itr->tag << ";"
                        << itr->word << "'";
                    throw ParseError(tmp.str());
                }
                safe_next(itr);
                return bem.makeBoolOperator(BoolOp::sstreamToBoolOpCode(temp), be, nullptr);
            }
            // AND o OR
            else {
                // Storing the boolean operator
                std::stringstream temp{};
                temp << itr->word;
                safe_next(itr);

                BoolExpr* left = recursiveParseBoolExpr(itr);

                BoolExpr* right = recursiveParseBoolExpr(itr);

                check_end(itr);
                if (itr->tag != Token::RP) {
                    std::stringstream tmp{};
                    tmp << "mismatched parenthesis at token '" << itr->tag << ";"
                        << itr->word << "'";
                    throw ParseError(tmp.str());
                }
                safe_next(itr);
                return bem.makeBoolOperator(BoolOp::sstreamToBoolOpCode(temp), left, right);
            }
        }
        // If after a left parenthesis I don't have
        // a keyword related to a relational operator
        // or a boolean operator I have a syntactic error
        else {
            std::stringstream tmp{};
            tmp << "unrecognized operator " << itr->word;
            throw ParseError(tmp.str());
            return nullptr;
        }
    }
    // Parsing a boolean constant
    else if (isBoolConst(itr->tag)) {
        // Storing the read boolean constant
        std::stringstream temp{};
        temp << itr->word;
        safe_next(itr);
        return bem.makeBoolConst(BoolConst::sstreamToBoolConst(temp));
    }
    // Syntax error
    else {
        std::stringstream tmp{};
        tmp << "unexpected token '" << itr->word << "'";
        throw ParseError(tmp.str());
        return nullptr;
    }
}

// Function for parsing and "building" a statement
Statement* ParseProgram::recursiveParseStmt(std::vector<Token>::const_iterator& itr) {
    check_end(itr);
    // Checking for a left parethesis
    if (itr->tag == Token::LP) {
        safe_next(itr);
        check_end(itr);
        // After the first left parenthesis I expect a 
        // keyword related to a statement
        if (isStmt(itr->tag)) {
            // SET
            // I expect a variable and a numeric expression
            if (itr->tag == Token::SET) {
                safe_next(itr);
                check_end(itr);
                if (itr->tag != Token::VAR) {
                    std::stringstream tmp{};
                    tmp << "expected a variable, got token '" << itr->tag << ";" << itr->word << "'";
                    throw ParseError(tmp.str());
                }

                NumExpr* var = parseVariable(itr);
                safe_next(itr);

                NumExpr* ne = recursiveParseNumExpr(itr);
                safe_next(itr);

                check_end(itr);
                if (itr->tag != Token::RP) {
                    std::stringstream tmp{};
                    tmp << "mismatched parenthesis at token '" << itr->tag << ";"
                        << itr->word << "'";
                    throw ParseError(tmp.str());
                }
                safe_next(itr);
                return sm.makeSetStmt(dynamic_cast<Variable*>(var), ne);
            }
            // PRINT
            // I expect a numeric expression
            else if (itr->tag == Token::PRI) {
                safe_next(itr);

                NumExpr* ne = recursiveParseNumExpr(itr);
                safe_next(itr);

                check_end(itr);
                if (itr->tag != Token::RP) {
                    std::stringstream tmp{};
                    tmp << "mismatched parenthesis at token '" << itr->tag << ";"
                        << itr->word << "'";
                    throw ParseError(tmp.str());
                }
                safe_next(itr);
                return sm.makePrintStmt(ne);
            }
            // INPUT
            // I expect a variable
            else if (itr->tag == Token::INP) {
                safe_next(itr);
                check_end(itr);
                if (itr->tag != Token::VAR) {
                    std::stringstream tmp{};
                    tmp << "expected a variable, got token '" << itr->tag << ";" << itr->word << "'";
                    throw ParseError(tmp.str());
                }

                NumExpr* var = parseVariable(itr);
                safe_next(itr);

                check_end(itr);
                if (itr->tag != Token::RP) {
                    std::stringstream tmp{};
                    tmp << "mismatched parenthesis at token '" << itr->tag << ";"
                        << itr->word << "'";
                    throw ParseError(tmp.str());
                }
                safe_next(itr);
                return sm.makeInputStmt(dynamic_cast<Variable*>(var));
            }
            // IF
            // I expect a boolean expression, a statement block
            // and a statement block
            else if (itr->tag == Token::IF) {
                safe_next(itr);

                BoolExpr* be = recursiveParseBoolExpr(itr);

                Block* b_l = parseStmtBlock(itr);

                Block* b_r = parseStmtBlock(itr);

                check_end(itr);
                if (itr->tag != Token::RP) {
                    std::stringstream tmp{};
                    tmp << "mismatched parenthesis at token '" << itr->tag << ";"
                        << itr->word << "'";
                    throw ParseError(tmp.str());
                }
                safe_next(itr);
                return sm.makeIfStmt(be, b_l, b_r);
            }
            // WHILE
            // I expect a boolean expression and a statement block
            else if (itr->tag == Token::WHI) {
                safe_next(itr);

                BoolExpr* be = recursiveParseBoolExpr(itr);

                Block* block = parseStmtBlock(itr);

                check_end(itr);
                if (itr->tag != Token::RP) {
                    std::stringstream tmp{};
                    tmp << "mismatched parenthesis at token '" << itr->tag << ";"
                        << itr->word << "'";
                    throw ParseError(tmp.str());
                }
                safe_next(itr);
                return sm.makeWhileStmt(be, block);
            }
            else {
                std::stringstream tmp{};
                tmp << "unexpected token '" << itr->word << "'";
                throw ParseError(tmp.str());
                return nullptr;
            }
        }
        // I get an error if I don't have a statement keyword
        // after the left parenthesis
        else {
            std::stringstream tmp{};
            tmp << "unexpected token '" << itr->word << "'";
            throw ParseError(tmp.str());
            return nullptr;
        }
    }
    // Syntax error
    else {
        std::stringstream tmp{};
        tmp << "unexpected token '" << itr->word << "'";
        throw ParseError(tmp.str());
        return nullptr;
    }
}

// Function for parsing and "building" a stmt_block
Block* ParseProgram::parseStmtBlock(std::vector<Token>::const_iterator& itr) {
    std::vector<Statement*> vs;
    check_end(itr);

    // A correct program starts with a Token::LP, '('
    if (itr->tag == Token::LP) {
        // After the first left parenthesis I have a 
        // keyword related to a statement or a 
        // keyword 'BLOCK'
        safe_next(itr);
        check_end(itr);
        // BLOCK
        // I expect at least a statement
        if (itr->tag == Token::B) {
            safe_next(itr);
            check_end(itr);
            // After a 'BLOCK' there must be at least one statement
            if (itr->tag == Token::RP) {
                throw ParseError("empty BLOCK statement");
            }
            while (itr->tag == Token::LP) {
                Statement* stmt = recursiveParseStmt(itr);
                vs.push_back(stmt);
                check_end(itr);
            }
            if (itr->tag != Token::RP) {
                std::stringstream tmp{};
                tmp << "mismatched parenthesis at token '" << itr->tag << ";"
                    << itr->word << "'";
                throw ParseError(tmp.str());
            }
            safe_next(itr);
            return bm.makeBlock(vs);
        }
        // If I don't read the 'BLOCK' keyword 
        // it means that it will have to parse 
        // only one statement
        else if (isStmt(itr->tag)) {
            itr--;
            Statement* stmt = recursiveParseStmt(itr);
            vs.push_back(stmt);
            return bm.makeBlock(vs);
        }
        // If after the first left parenthesis I don't have 
        // the keyword 'BLOCK' or a keyword relating to a statement, 
        // I have a syntax error
        else {
            std::stringstream tmp{};
            tmp << "unexpected token '" << itr->word << "'";
            throw ParseError(tmp.str());
            return nullptr;
        }
    }
    // If the program doesn't start with a left parenthesis
    // I have a syntax error
    else {
        std::stringstream tmp{};
        tmp << "missing left parenthesis at token '" << itr->tag << ";" << itr->word << "'";
        throw ParseError(tmp.str());
        return nullptr;
    }
}