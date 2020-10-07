//
// Created by Guillaume Doucet on 2020-10-07.
//

#include <Utils/BinaryUtil.h>
#include "CTROperationMode.h"
using namespace std;

/*
 * Fonction qui encrypte le message targetText avec la clef key en utilisant CTR et le vecteur d'initialisation iv
 * */
std::string CTROperationMode::encrypt(const std::string &text, const std::string &key, const std::string &iv) {
    string cipherText = iv + encryptDecryptInternal(text, key, iv);
    return cipherText;
}

/*
 * Fonction qui decrypte le message targetText avec la clef key en utilisant CTR
 * */
std::string CTROperationMode::decrypt(const std::string &text, const std::string &key) {
    vector<string> all7bitWords = separateInCharsWordsOfSize(text, BLOCK_SIZE); //séparation en mots de 7 bits
    string iv = all7bitWords.at(0); //on extrait iv0 du message

    return encryptDecryptInternal(text.substr(BLOCK_SIZE), key, iv);
}

/*
 * Fonction qui decrypte ou encrypte le message targetText avec la clef key en utilisant CTR et le vecteur d'initialisation iv.
 * L'algorithme est le même peut importe encryption ou décryption.
 * */
std::string
CTROperationMode::encryptDecryptInternal(const std::string &text, const std::string &key, const std::string &iv) {
    vector<string> all7bitWords = separateInCharsWordsOfSize(text, BLOCK_SIZE); //séparation en mots de 7 bits
    vector<bool> keyBinary = BinaryUtil::getBinaryValues(key); //convertion en vecteur de bool
    vector<bool> ivBinary = BinaryUtil::getBinaryValues(iv);//convertion en vecteur de bool
    string resultText;

    for (const auto & all7bitWord : all7bitWords) {
        vector<bool> temp;
        vector<bool> binaryWord = BinaryUtil::getBinaryValues(all7bitWord);
        temp = BinaryUtil::XOR(ivBinary, keyBinary);
        vector<bool> result = BinaryUtil::XOR(binaryWord, temp);
        resultText += BinaryUtil::getCharValues(result); //convertion en string
        BinaryUtil::incrementInModuloN(ivBinary); //on incrémente dans modulo N où N est la taille de ivBinary
    }

    return resultText;
}

