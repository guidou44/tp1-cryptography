//
// Created by Guillaume Doucet on 2020-10-07.
//

#include "OperationModeBase.h"

#include <bitset>
#include "OperationModeBase.h"

/*
 * Fonction qui sépare un string en sous string de grandeur 'size', dans un vecteur. Si la taille de 'text' n'est pas un multiple de size,
 * le dernier mot sera plus petit.
 *
 * */
std::vector<std::string> OperationModeBase::separateInCharsWordsOfSize(const std::string &text, int size) {
    std::vector<std::string> output;

    std::string current;
    for (int i=0; i < text.size(); i++) {
        if (i % size == 0 && i != 0) {
            output.push_back(current);
            current.clear();
        }
        current += text[i];
    }

    output.push_back(current);
    return output;
}

/*
 * Fonction qui génère un string représentant un mot de 7 bits aléatoire
 *
 * */
std::string OperationModeBase::generateInitVector() {
    int iv = rand() % 128;
    std::string binary = std::bitset<7>(iv).to_string();
    return binary;
}

/*
 * Fonction qui génère int aléatoire de 1 à 7.
 *
 * */
int OperationModeBase::getRandomRParameter(int max) {
    return (rand() % max) + 1;
}
