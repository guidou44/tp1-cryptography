//
// Created by Guillaume Doucet on 2020-10-07.
//

#include <Utils/BinaryUtil.h>
#include "CFBOperationMode.h"
using namespace std;

/*
 * Fonction encrypte le message text avec la clef key en utilisant CFB et le vecteur d'initialisation iv. r représente le nombre de bit de chaque bloque de message à encrypter
 * */
std::string CFBOperationMode::encrypt(const std::string &text, const std::string &key, const std::string &iv, const int& r) {

    string cipherText = iv + encryptDecryptInternal(text, key, iv, r, true);
    return cipherText;
}

/*
 * Fonction decrypte le message text avec la clef key en utilisant CFB et le vecteur d'initialisation iv. r représente le nombre de bit de chaque bloque de message à décrypter
 * */
std::string CFBOperationMode::decrypt(const std::string &text, const std::string &key, const int& r) {
    vector<string> all7bitWords = separateInCharsWordsOfSize(text, BLOCK_SIZE); //séparation en mots de 7 bits
    string iv = all7bitWords.at(0); //extraction de IV0

    return encryptDecryptInternal(text.substr(BLOCK_SIZE), key, iv, r, false);
}

/*
 * Fonction interne qui decrypte ou encrypte le message text avec la clef key en utilisant CFB et le vecteur d'initialisation iv.
 * On utilise également le flag 'isEncrypting' car celui-ci influence l'opération de préparation du prochain vecteur d'initialisation.
 * L'algorithme est le même peut importe encryption ou décryption, mise à part la préparation du prochain vecteur d'initialisation.
 * */
std::string CFBOperationMode::encryptDecryptInternal(const std::string &text, const std::string &key, const std::string &iv,
                                                     const int &r, bool isEncrypting) {
    vector<string> allRbitWords = separateInCharsWordsOfSize(text, r); //séparation en mots de R bits
    vector<bool> ivBinary = BinaryUtil::getBinaryValues(iv); //convertion en vecteur de bool
    vector<bool> keyBinary = BinaryUtil::getBinaryValues(key);//convertion en vecteur de bool
    vector<bool> encryptionInput = ivBinary;//première entrée = IV0
    string outputText;

    for (const auto & allRbitWord : allRbitWords) {

        vector<bool> firstEncryptionOutput = BinaryUtil::XOR(encryptionInput, keyBinary);
        vector<bool> outputMRB(firstEncryptionOutput.begin(), firstEncryptionOutput.begin() + allRbitWord.size()); //on extrait les 'Most relevant bits' du premier XOR
        vector<bool> wordBinary = BinaryUtil::getBinaryValues(allRbitWord);//convertion en vecteur de bool
        vector<bool> blockResult = BinaryUtil::XOR(outputMRB, wordBinary);//convertion en vecteur de bool
        outputText += BinaryUtil::getCharValues(blockResult);
        BinaryUtil::shiftLeft(encryptionInput, allRbitWord.size());//on effectue un décalage vers la gauche de IV pour préparer le prochain IV
        prepareNextEncryptionInput(encryptionInput, blockResult, firstEncryptionOutput, wordBinary, isEncrypting); //préparation du prochain IV
    }

    return outputText;
}

/*
 * Fonction qui ajouter des bits (bitsToAppend) représentée sous la forme de vecteur de bool à la fin d'un autre mot binaire
 * (nextEncryptionInput) également représenté sous la forme de vecteur de bool.
 *
 * */
void CFBOperationMode::appendBitsToNextInput(std::vector<bool> &nextEncryptionInput,
                                             const std::vector<bool> &bitsToAppend) {
    nextEncryptionInput.insert(nextEncryptionInput.end(), bitsToAppend.begin(), bitsToAppend.end());
}


/*
 * Fonction qui prépare le prochain vecteur d'initialisation. Cette méthode est 'override' dans OFB
 * */
void CFBOperationMode::prepareNextEncryptionInput(std::vector<bool> &nextEncryptionInput,
                                                  const std::vector<bool> &blockResult,
                                                  const std::vector<bool> &firstEncryptionResult,
                                                  const std::vector<bool> &wordBinary, bool isEncrypting) {
    if (isEncrypting)
        appendBitsToNextInput(nextEncryptionInput, blockResult); //si encryption on ajoute le résultat de C(i) à IV(i) qui a été shift left
    else
        appendBitsToNextInput(nextEncryptionInput, wordBinary); //si décryption on ajoute C(i) à IV(i) qui a été shift left
}

