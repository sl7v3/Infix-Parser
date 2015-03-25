#include <iostream>
#include <cctype>
#include "InfixParser.h"
#include "Syntax_Error.h"

InfixParser::InfixParser(std::string s) {
    set(s);
}

void InfixParser::set(std::string s) {
    expression.clear();
    expression.str(s);
}

int InfixParser::evaluate() {
    while (expression.good()) {
        Token t = nextToken();
        handleToken(t);
    }
	if (!values.empty()) {
		int answer = values.top().i;
		values.pop();
		if (values.empty()) {
			return answer;
		}
		else {
			throw Syntax_Error("Stack should be empty");
		}
	}
	else {
		throw Syntax_Error("Stack is empty");
	}
    // TODO: loop until operators/values stacks are empty.

    return -1;  // TODO: return actual value
}

Token InfixParser::nextToken() {
    Token t;
    char c;
    expression >> c;
    if (c == ' ') return nextToken();

    if (isdigit(c)) {  // Value
        expression.putback(c);
        t.isOperator = false;
        expression >> t.i;
    }

    else {
        t.isOperator = true;
        char next;
        expression >> next;
        // TODO: make this less ugly.
        switch (c) {  // Operator.
            case '!':
                if (next == '=') {
                    t.s = "!=";
                } else {
                    t.s = "!";
                    expression.putback(next);
                }
                break;
            case '+':  // + or ++
                if (next == '+') {
                    t.s = "++";
                } else {
                    t.s = "+";
                    expression.putback(next);
                }
                break;
            case '-':  // -, --, or negative
                if (next == '-') {
                    t.s = "--";
                } else {
                    // TODO: differentiate negative vs subtraction
                    t.s = "-";
                    expression.putback(next);
                }
                break;
            case '>':  // > or >=
                if (next == '=') {
                    t.s = ">=";
                } else {
                    t.s = ">";
                    expression.putback(next);
                }
                break;
            case '<':  // < or <=
                if (next == '=') {
                    t.s = "<=";
                } else {
                    t.s = '<';
                    expression.putback(next);
                }
                break;
            case '=':
                if (next == '=') {
                    t.s = "==";
                } else {
                    t.s = "=";
                    expression.putback(next);
                }
                break;
            case '&':
                if (next == '&') {
                    t.s = "&&";
                } else {
                    // TODO: raise error
                }
                break;
            case '|':
                if (next == '|') {
                    t.s = "||";
                } else {
                    // TODO: raise error
                }
                break;
            default:  // All the other operators.
                // TODO: raise error if not in operatorTable
                expression.putback(next);
                t.s = c;
                break;
        }
    }

    return t;
}

void InfixParser::handleToken(Token t) {
    // TODO: this is the logic for handling each parsed Token.
    // Determine whether anything needs to be popped from either stack and/or
    // if the Token needs to be pushed onto a stack... or something along those
    // lines.
	
			if ( isdigit(t.i)) {
				values.push(t);
			}
			else if ((t.isOperator)) {
				process_operator(t);
			}
			else {
				  throw Syntax_Error("Unexpected Character Encountered");
			}
		}
// End while
		// Pop any remaining operators and append them to postfix
		/*while (!operator_stack.empty()) {
			char op = operator_stack.top();
			operator_stack.pop();
			if (op == '(' || op == '[' || op == '}') {
				throw Syntax_Error("Unmatched open parenthesis");
			}
			postfix += op;
			postfix += " ";
		}
		return postfix;
	*/

void InfixParser::process_operator(Token t)
{
	if (operators.empty() || (t.s[0] == '(')) {
		if (t.s[0] == ')')
			//throw Syntax_Error("Unmatched close parenthesis");
			operators.push(t);
	}
	else {
		std::unordered_map<std::string, Operator>::const_iterator checkItr = operatorTable.find(t.s);
		std::unordered_map<std::string, Operator>::const_iterator checkTopItr = operatorTable.find(operators.top().s);
		if (checkItr->second.precedence > checkTopItr->second.precedence)
		{
			operators.push(t);
		}
		else {
			// Pop all stacked operators with equal
			// or higher precedence than op.
			while (!operators.empty()
				&& (checkTopItr->first[0] != '(')
				&& (checkTopItr->first[0] != '[')
				&& (checkTopItr->first[0] != '{')
				&& (checkItr->second.precedence <= checkTopItr->second.precedence)) {
				int result = 0;
				if (values.empty())
					throw Syntax_Error("Stack is empty");
				int rhs = values.top().i;
				values.pop();
				if (checkTopItr->first == "!")
				{
					result = !rhs;

				}
				else if (checkTopItr->first == "++")
				{
					result = rhs + 1;

				}
				else if (checkTopItr->first == "--")
				{
					result = rhs - 1;

				}
				else if (checkTopItr->first == "#")
				{
					result = -1 * rhs;

				}
				Token T;
				T.isOperator = false;
				T.i = result;
				values.push(T);
				break;
				if (values.empty())
					throw Syntax_Error("Stack is empty");
				int lhs = values.top().i;
				values.pop();
				if (checkTopItr->first == "+")
				{
					result = lhs + rhs;
				}
				else if (checkTopItr->first == "-")
				{
					result = lhs - rhs;
				}
				else if (checkTopItr->first == "*")
				{
					result = lhs * rhs;
				}
				else if (checkTopItr->first == "/")
				{
					result = lhs / rhs;
				}
				else if (checkTopItr->first == "%")
				{
					result = lhs % rhs;
				}
				else if (checkTopItr->first == "^")
				{
					result = lhs^rhs;
				}
				else if (checkTopItr->first == ">")
				{
					result = lhs > rhs;
				}
				else if (checkTopItr->first == "<")
				{
					result = lhs < rhs;
				}
				else if (checkTopItr->first == ">=")
				{
					result = lhs >= rhs;
				}
				else if (checkTopItr->first == "<=")
				{
					result = lhs <= rhs;
				}
				else if (checkTopItr->first == "==")
				{
					result = lhs == rhs;
				}
				else if (checkTopItr->first == "!=")
				{
					result = lhs != rhs;
				}
				else if (checkTopItr->first == "&&")
				{
					result = lhs && rhs;
				}
				else if (checkTopItr->first == "||")
				{
					result = lhs || rhs;
				}
				Token S;
				S.isOperator = false;
				S.i = result;
				values.push(S);
				operators.pop();
			}
			// assert: Operator stack is empty or 
			//         top of stack is '(' or current
			//         operator precedence > top of stack operator
			//         precedence;
			if (t.s == ")") {
				if (!operators.empty()
					&& (operators.top().s == "(")) {
					operators.pop();
				}
				else {
					throw Syntax_Error("Unmatched close parentheses");
				}
			}

			else {
				operators.push(t);
			}

		}
	}
}