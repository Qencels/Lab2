#include <iostream>
#include <fstream>
#include "antlr4-runtime.h"
#include "TLexer.h"
#include "TParser.h"
#include "tree/IterativeParseTreeWalker.h"
#include "CalculatorInterpreter.h"
#include "TParserVisitor.h"

class ExceptionErrorListener : public antlr4::BaseErrorListener {
public:
    virtual void syntaxError(
        antlr4::Recognizer* recognizer, antlr4::Token* offendingSymbol,
        size_t line, size_t charPositionInLine, const std::string& msg,
        std::exception_ptr e) override {

        e = nullptr;
        std::ostringstream oss;
        oss << "line: " << line << ":" << charPositionInLine << " " << msg;
        error_msg = oss.str();
        throw antlr4::ParseCancellationException(error_msg);
    }
private:
    std::string error_msg;
};

using namespace antlrcpptest;
using namespace antlr4;

void execute_expression(const std::string& expr) {

    antlr4::ANTLRInputStream input(expr);

    TLexer lexer(&input);
    lexer.removeErrorListeners();
    lexer.addErrorListener(new ExceptionErrorListener());
    
    antlr4::CommonTokenStream tokens(&lexer);

    TParser parser(&tokens);
    parser.removeErrorListeners();
    parser.addErrorListener(new ExceptionErrorListener());

    antlr4::tree::ParseTree* tree = nullptr;

    try {
        tree = parser.input();
    }
    catch (antlr4::ParseCancellationException& e) {
        std::cout << e.what() << std::endl;
        exit(0);
    }

    CalculatorInterpreter interpreter;

    antlr4::tree::IterativeParseTreeWalker walker;
    walker.walk(&interpreter, tree);
}

int main(int argc, char* argv[]) {
    
    std::ifstream stream;

    if (argc == 1) {
        stream.open("..\\example.txt");
    }
    if (argc == 2) {
        std::cout << argv[1] << std::endl;
        stream.open(argv[1]);
    }
    if (argc > 2) throw std::invalid_argument("arc incorrect");

    std::string str((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

    std::cout << str << std::endl;
    
    execute_expression(str);
 
    return 0;
}

