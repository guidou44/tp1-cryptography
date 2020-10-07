//
// Created by Guillaume Doucet on 2020-10-07.
//

#include "BinaryUtil.h"

#include "BinaryUtil.h"

/*
 * Fonction qui s'assure qu'un string représente un mote binaire, i.e. que des 1 et 0.
 *
 * */
bool BinaryUtil::textIsBinaryNumbers(const std::string &text) {
    for (const auto& c : text) {
        if (!charIsBit(c))
            return false;
    }
    return true;
}

/*
 * Fonction qui convertit un string qui représente un mot binaire en vecteur de bool équivalent.
 * 0 = false, 1 = true
 * */
std::vector<bool> BinaryUtil::getBinaryValues(const std::string &binaryText) {
    if (!textIsBinaryNumbers(binaryText))
        throw std::logic_error("text is not binary number");

    std::vector<bool> binaryValues;

    for (const auto& c : binaryText) {
        binaryValues.push_back(getBinaryValue(c));
    }

    return binaryValues;
}

/*
 * Fonction qui convertit un vecteur de bool en string représentant le mot binaire équivalent
 * 0 = false, 1 = true
 * */
std::string BinaryUtil::getCharValues(const std::vector<bool>& boolValues) {
    std::string output;

    for (const auto& val : boolValues) {
        output += getCharRepresentation(val);
    }

    return output;
}

/*
 * Fonction qui performe l'opération logique XOR entre 2 vecteurs de bool qui représentes des mots binaries.
 * Les vecteurs doivent avoir la même longeur.
 * Retourne le résultat du XOR dans un vecteur de booléan
 * */
std::vector<bool> BinaryUtil::XOR(const std::vector<bool> &first, const std::vector<bool> &second) {
    if (first.size() != second.size())
        throw std::logic_error("comparison of different size not supported");
    std::vector<bool> result;

    for (int i=0; i < first.size(); i++) {
        result.push_back(first[i] ^ second[i]);
    }

    return result;
}

/*
 * Fonction qui performe l'opération shift left sur un vecteur de bool qui représente un mot binaire.
 * Le nombre de bit à 'shift' doit ètre spécifié en entré.
 * Le vecteur est passé par référence.
 * */
void BinaryUtil::shiftLeft(std::vector<bool> &target, int numberOfBits) {
    target.erase(target.begin(), target.begin() + numberOfBits);
}

/*
 * Fonction qui incrémente de 1 un vecteur de bool représentant un mot binaire, et ce dans modulo N où N est la
 * longueur du mote binaire (i.e. l'incrémentation de 11111 donne 00000).
 * */
void BinaryUtil::incrementInModuloN(std::vector<bool> &target) {

    unsigned int lastTargetIndex = target.size() - 1;
    for (unsigned int i = lastTargetIndex; i >= 0; i--) {
        if (!target[i] && i == lastTargetIndex) {
            target[i] = true;
            return;//LSB est à 0, on incrémente et on retourne.
        }

        if (!target[i]) {
            target[i] = true;
            target[i+1] = false;
            return; //Premier bit à 0 rencontré (autre que le bit moins significatif) est mis à 1, et son bit de droite est remis à 0.
        }
    }

    //Si on se rend ici, tout les bits sont des 1, donc on remet tout à 0 pour rester dans modulo n où n est le nombre de bit.
    for  (auto && i : target) {
        i = false;
    }
}


//region private methods

/*
 * Fonction qui vérifie si un charactère représente un bit (0 ou 1). Retourne vraie si c'est la cas, faux sinon.
 * */
bool BinaryUtil::charIsBit(const char &c) {
    if (!std::isdigit(c))
        return false;
    int digit = c - '0';
    return !(digit != 0 && digit != 1);
}

/*
 * Fonction qui retourne la valeur booléenne équivalente d'un charactère s'il est 0 ou 1. Si ce n'est pas le cas, une
 * logic_error est lancée.
 * */
bool BinaryUtil::getBinaryValue(const char &c) {
    if (!charIsBit(c))
        throw std::logic_error("char does not represent bit");

    int digit = c - '0';
    return digit == 1;
}

/*
 * Fonction qui retourne le charactère équivalent d'un bool. true = 1, false = 0;
 * */
char BinaryUtil::getCharRepresentation(bool bit) {
    return (bit) ? '1' : '0';
}

//endregion
