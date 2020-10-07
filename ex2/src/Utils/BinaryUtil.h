//
// Created by Guillaume Doucet on 2020-10-07.
//

#ifndef EX2_BINARYUTIL_H
#define EX2_BINARYUTIL_H


#include <string>
#include <stdexcept>
#include <vector>

class BinaryUtil {
public:
    static bool textIsBinaryNumbers(const std::string& text);
    static std::vector<bool> getBinaryValues(const std::string& binaryText);
    static std::string getCharValues(const std::vector<bool>& boolValues);
    static std::vector<bool> XOR(const std::vector<bool>& first, const std::vector<bool>& second);
    static void shiftLeft(std::vector<bool>& target, int numberOfBits);
    static void incrementInModuloN(std::vector<bool>& target);

private:
    static bool charIsBit(const char& c);
    static bool getBinaryValue(const char& c);
    static char getCharRepresentation(bool bit);

};

#endif //EX2_BINARYUTIL_H
