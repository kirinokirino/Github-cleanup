//
// Created by kirinokirino on 10/20/17.
//

#include "Interpreter.h"

void Interpreter::writeToFile(const string &filename) {
    std::FILE *file = std::fopen(filename.data(), "w");
    if (!file)
        throw fmt::SystemError(errno, "cannot open file '{}'", filename.data());
    fmt::print(file, "This is a line.\n");
    fmt::print(file, "This is another line.\n");
    fclose(file);
}

void Interpreter::writeToFile(const string &filename, const string &contents) {
    std::FILE *file = std::fopen(filename.data(), "w");
    if (!file)
        throw fmt::SystemError(errno, "cannot open file '{}'", filename.data());
    fmt::print(file, contents.data());
    fclose(file);
}

string Interpreter::readFile(const string &filename) {
    ifstream file(filename.data());
    if (file.is_open()) {
        return string { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
    } else {
        fmt::SystemError(errno, "cannot open file '{}'", filename.data());
        string {"err: Unable to open file\n"};
    }
}

void Interpreter::processFile(const string &filename) {
    string line;
    ifstream file(filename.data());
    if (file.is_open()) {
        while (getline(file, line)) {
            processLine(line);
        }
        file.close();
    } else fmt::SystemError(errno, "cannot open file '{}'", filename.data());
}

void Interpreter::processLine(const string &line) {
    const string delimiter = " ";
    std::vector<string> tokenList;
    size_t last = 0;
    size_t next = 0;
    while (next != string::npos) {
        next = line.find(delimiter, last);
        auto temp = line.substr(last, next - last);
        if (temp != "") tokenList.emplace_back(temp);
        last = next + 1;
    }
    processTokens(tokenList);
}

void Interpreter::processTokens(const std::vector<string> tokenList) {
    for (auto i : tokenList) fmt::print("{} ", i);
}