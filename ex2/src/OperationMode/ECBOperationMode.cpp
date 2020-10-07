//
// Created by Guillaume Doucet on 2020-10-07.
//

#include <Utils/BinaryUtil.h>
#include "ECBOperationMode.h"

using  namespace std;

/*
 * Fonction qui encrypte ou décrypte le message targetText avec la clef key en utilisant ECB,
 * L'algorithme est le même que ce soit encryption ou décryption.
 * */
std::string ECBOperationMode::encryptDecrypt(const std::string &targetText, const std::string &key) {
    vector<string> all7bitWords = separateInCharsWordsOfSize(targetText, BLOCK_SIZE); //on sépare le message en mot de 7 bits.
    string text; //résultat

    for (const auto& word : all7bitWords) {
        text += encryptDecryptInternal(word, key);
    }

    return text;
}

/*
 * Fonction interne qui encrypte ou décrypte le message targetText avec la clef key en utilisant ECB,
 * L'algorithme est le même que ce soit encryption ou décryption.
 * */
std::string ECBOperationMode::encryptDecryptInternal(const std::string &text, const std::string &key) {

    vector<bool> binaryText = BinaryUtil::getBinaryValues(text);
    vector<bool> binaryKey = BinaryUtil::getBinaryValues(key);
    vector<bool> resultBinary = BinaryUtil::XOR(binaryText, binaryKey);

    return BinaryUtil::getCharValues(resultBinary);
}