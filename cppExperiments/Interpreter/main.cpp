#include "Interpreter.h"

int main() {
    string testFileName = "test.txt";
    Interpreter::writeToFile(testFileName, "Test message\n t e s t .");
    fmt::print("{}\n", Interpreter::readFile("test.txt"));
    Interpreter::processFile(testFileName);
    return 0;
}