//
// Created by Guillaume Doucet on 2020-10-07.
//

#ifndef EX2_OPERATIONMODEBASE_H
#define EX2_OPERATIONMODEBASE_H


#include <vector>
#include <string>

class OperationModeBase {

public:
    static std::string generateInitVector();
    static int getRandomRParameter(int max);
    static const int BLOCK_SIZE = 7;
    static std::vector<std::string> separateInCharsWordsOfSize(const std::string& text, int size);
};

#endif //EX2_OPERATIONMODEBASE_H
