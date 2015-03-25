#ifndef _infix_parser_h
#define _infix_parser_h
#include <stack>
#include <unordered_map>
#include <string>
#include <sstream>
#include "Syntax_Error.h"

struct Token {
    bool isOperator;
    std::string s;  // For operator, used in conjunction with operatorTable
    int i;  // For value
};

class InfixParser {
    public:
        InfixParser() { }  // Intentionally empty.
        InfixParser(std::string s);
        void set(std::string s);
        int evaluate();
		void process_operator(Token t); //Sulaimon added this on 3/17 to process each operator
										// it will be called by the evaluate function when necessary.

    private:
        struct Operator {
            int precedence;
            bool leftAssociative;
        };
        // Reference/lookup table.
        const std::unordered_map<std::string, Operator> operatorTable {
            {"!", {8, true}},
            {"++", {8, true}},
            {"--", {8, true}},
            {"#", {8, true}},  // This represents a negative sign.
            {"^", {7, false}},
            {"*", {6, true}},
            {"/", {6, true}},
            {"%", {6, true}},
            {"+", {5, true}},
            {"-", {5, false}},  // This represents subtraction, not negative.
            // TODO: Don't konw if ones below are left or right associative... or if it matters.
            {">", {4, true}},
            {">=", {4, true}},
            {"<", {4, true}},
            {"<=", {4, true}},
            {"==", {3, true}},
            {"!=", {3, true}},
            {"&&", {2, true}},
            {"||", {1, true}},
            {"(", {0, true}},  // TODO Should parentheses be a higher priority?
            {")", {0, true}},
        };

        std::stringstream expression;
        std::stack<Token> operators;
        std::stack<Token> values;

        Token nextToken();
        void handleToken(Token t);
};

#endif
