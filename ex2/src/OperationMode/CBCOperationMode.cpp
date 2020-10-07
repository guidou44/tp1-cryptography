//
// Created by Guillaume Doucet on 2020-10-07.
//

#include <bitset>
#include <Utils/BinaryUtil.h>
#include "CBCOperationMode.h"

using namespace std;

/*
 * Fonction qui encrypt le message text avec la clef key et le vecteur d'initalisation iv avec XOR et le mode d'opération CBC.
 *
 * */
std::string CBCOperationMode::encrypt(const std::string &text, const std::string &key, const std::string &iv) {
    vector<string> all7bitWords = separateInCharsWordsOfSize(text, BLOCK_SIZE); //séparation en mots de 7 bits
    vector<bool> keyBinary = BinaryUtil::getBinaryValues(key); //convertion en vecteur de bool
    vector<bool> ivBinary = BinaryUtil::getBinaryValues(iv);//convertion en vecteur de bool
    string cipherText = iv;//on ajoute IV0 au début du text cipher
    vector<vector<bool>> resultsBinary; //vecteur qui contient les résultat de chaque bloque

    for (int i = 0; i < all7bitWords.size(); i++) {
        vector<bool> temp;
        vector<bool> binaryWord = BinaryUtil::getBinaryValues(all7bitWords[i]);
        if (i == 0) {
            temp = BinaryUtil::XOR(binaryWord, ivBinary); //XOR entre M0 et IV0
        } else {
            temp = BinaryUtil::XOR(binaryWord, resultsBinary[i - 1]); //XOR entre M(i) et C(i-1)
        }

        vector<bool> result = BinaryUtil::XOR(keyBinary, temp); //XOR avec la clef
        resultsBinary.push_back(result);
        cipherText += BinaryUtil::getCharValues(result); //convertion en string
    }

    return cipherText;
}

/*
 * Fonction qui décrypte le message text avec la clef key avec XOR et le mode d'opération CBC.
 *
 * */
std::string CBCOperationMode::decrypt(const std::string &text, const std::string &key) {
    vector<string> all7bitWords = separateInCharsWordsOfSize(text, BLOCK_SIZE);//séparation en mots de 7 bits
    if (all7bitWords.size() == 1)
        throw logic_error("cannot decrypt word with only 1 7bits block with CBC");
    const string iv = all7bitWords.at(0);//extraction d'iv
    vector<bool> keyBinary = BinaryUtil::getBinaryValues(key);//convertion en vecteur de bool
    vector<bool> ivBinary = BinaryUtil::getBinaryValues(iv);//convertion en vecteur de bool
    string plainText;
    vector<vector<bool>> ciphersBinary;//vecteur qui contient les ciphers de chaque bloque
    ciphersBinary.push_back(ivBinary);

    for (int i = 1; i < all7bitWords.size(); i++) {
        vector<bool> result;
        vector<bool> binaryWord = BinaryUtil::getBinaryValues(all7bitWords[i]);//convertion en vecteur de bool
        ciphersBinary.push_back(binaryWord);//ajout au vecteur des ciphers

        vector<bool> temp = BinaryUtil::XOR(binaryWord, keyBinary);
        if (i == 1) {
            result = BinaryUtil::XOR(temp, ivBinary);//XOR entre IV(0) et le résultat de XOR (C(0) et KEY)
        } else {
            result = BinaryUtil::XOR(temp, ciphersBinary[i - 1]);//XOR entre C(i-1) et le résultat de XOR (C(i) et KEY)
        }

        plainText += BinaryUtil::getCharValues(result); //convertion en string
    }

    return plainText;
}

