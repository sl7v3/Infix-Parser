#include <iostream>
#include <string>
#include <sstream>
#include "InfixParser.h"
#include "Syntax_Error.h"

struct TestCase {
    std::string exp;
    int result;
};

/*
 * For testing purposes -- parse t.exp and compare to t.result.
 */
bool test(TestCase t) {
    InfixParser parser(t.exp);

    int r = parser.evaluate();
    if (r == t.result) {
        return true;
    } else {
        std::cerr << "TEST FAIL: \"" << t.exp << "\" evaluated to " << r
            << ", should be " << t.result << '\n';
        return false;
    }
}

int main() {
    // Feel free to add cases if you have more worth testing.
    TestCase cases[] = {
        {"1+2*3", 7},
        {"1 *   2+3", 5},
        {"2 + 2^2 * 3", 14},
        {"1 == 2", 0},
        {"1 + 3 > 2", 1},
        {"4 >= 4 && 0", 0},
        {"(1+2) * 3", 9},
        {"++++2 - 5 * (3^2)", -41},
    };

    int fails = 0;
    for (unsigned int i = 0; i < sizeof(cases) / sizeof(TestCase); i++) {
        if (!test(cases[i])) fails++;
    }
    std::cout << "\nTOTAL FAILED: " << fails << "/" << sizeof(cases) / sizeof(TestCase) << '\n';
}
