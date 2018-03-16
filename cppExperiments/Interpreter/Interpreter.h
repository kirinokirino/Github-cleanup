//
// Created by kirinokirino on 10/20/17.
//

#ifndef INTERPRETER_INTERPRETER_H
#define INTERPRETER_INTERPRETER_H

#include "format.h"
#include <cstdio>
#include <fstream>
#include <vector>

using std::string;
using std::ifstream;
using std::ofstream;
class Interpreter {
private:
public:
    static void writeToFile(const string &filename);

    static void writeToFile(const string &filename, const string &contents);

    static string readFile(const string &filename);

    static void processFile(const string &filename);

    static void processLine(const string &line);

    static void processTokens(const std::vector<string> tokenList);
};

#endif //INTERPRETER_INTERPRETER_H
