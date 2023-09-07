#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

#include "Parser.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Exceptions.h"
#include "Visitor.h"

// Debug levels
constexpr int TOKENIZER = 1;
constexpr int PRINT_VISITOR = 2;
constexpr int ALL = 3;
constexpr int OFF = 0;

// Set the desired debug level here
constexpr int DEBUG = 0;

#define DEBUG_EXECUTE(level, code) if (DEBUG == level || DEBUG == ALL) code

int main(int argc, char* argv[])
{
    // Check that I have enough parameters (I need a parameter with the program)
    if (argc < 2) {
        std::cerr << "Unspecified file!" << std::endl;
        std::cerr << "Use: " << argv[0] << " <file_name>" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream inputFile;

    // Handling exceptions on file opening
    try {
        inputFile.open(argv[1]);
        if (!inputFile.is_open()) {
            std::cerr << "(ERROR generic: cannot open file " << argv[1] << " )";
            return EXIT_FAILURE;
        }
    }
    catch (std::exception& exc) {
        std::cerr << "(ERROR generic: opening of the file " << argv[1] << " failed )" << std::endl;
        std::cerr << exc.what() << std::endl;
        return EXIT_FAILURE;
    }

    Tokenizer tokenize;
    std::vector<Token> inputTokens;

    // Handling exceptions in phase
    // of Tokenization
    try {
        inputTokens = std::move(tokenize(inputFile));
        inputFile.close();
    }
    catch (LexicalError& le) {
        std::cerr << "(ERROR in tokenizer: ";
        std::cerr << le.what() << " )" << std::endl;
        return EXIT_FAILURE;
    }
    catch (std::exception& exc) {
        std::cerr << "(ERROR generic: impossible to read from " << argv[1] << " )" << std::endl;
        std::cerr << exc.what() << std::endl;
        return EXIT_FAILURE;
    }

    // Set the DEBUG level to 1 or 4
    // to print the inputTokens Vector
    DEBUG_EXECUTE(TOKENIZER,
        {
            std::cout << "The tokens read are: " << std::endl;
            for (Token t : inputTokens) {
            std::cout << t << std::endl;
            }
        }
    );

    // Create all the managers for all the nodes
    BlockManager bm;
    StmtManager sm;
    NumExprManager nem;
    BoolExprManager bem;

    // Create the table of variables
    VariableTable vt;

    ParseProgram parse{ bm, sm, nem, bem };

    // Handling esceptions in phase of
    // Parsing and Evaluation
    try {
        Program* program = parse(inputTokens);

        // Useful for DEBUG
        // Set the DEBUG level to 2 or 4
        // to print all the program read using
        // the PrintVisitor
        DEBUG_EXECUTE(PRINT_VISITOR, 
            {
            PrintVisitor * p = new PrintVisitor();
            std::cout << "The program read is: " << std::endl;
            program->accept(p);
            }
        );

        EvaluationVisitor* v = new EvaluationVisitor(vt);
        program->accept(v);

        delete program;
    }
    catch (ParseError& pe) {
        std::cout << "(ERROR in parser: ";
        std::cerr << pe.what() << " )" << std::endl;
        return EXIT_FAILURE;
    }
    catch (EvaluationError& ee) {
        std::cerr << "(ERROR in evaluator: ";
        std::cerr << ee.what() << " )" << std::endl;
        return EXIT_FAILURE;
    }
    catch (std::exception& exc) {
        std::cerr << "(ERROR generic: ";
        std::cerr << exc.what() << " )" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}