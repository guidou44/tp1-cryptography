//
// Created by Guillaume Doucet on 2020-10-07.
//

#include <Utils/BinaryUtil.h>
#include "OFBOperationMode.h"
using namespace std;


/*
 * Fonction qui prépare le prochain vecteur d'initialisation (prochaine itération, prochain block) pour l'encryption
 * avec le mode d'opération OFB. le paramètre 'isEncrypting' sert seulement dans CFB, mais la méthode ici est un override.
 * */
void OFBOperationMode::prepareNextEncryptionInput(std::vector<bool> &nextEncryptionInput, //prochain vecteur d'initilisation
                                                  const std::vector<bool> &blockResult, //resultat du block courant
                                                  const std::vector<bool> &firstEncryptionResult, //dernier resultat de XOR entre key et iv
                                                  const std::vector<bool> &wordBinary, bool isEncrypting) {
    nextEncryptionInput = firstEncryptionResult;
    //on prend la sortie de l'encryption précédente, soit XOR entre IV(i) et KEY, comme prochain vecteur d'initilisation.
    //sinon le reste de l'algorithme est comme CFB
    //Note: plusieurs resources n'implémentent pas ce mode d'opération de cette façon. voir: https://www.youtube.com/watch?v=GsSJt6NZF9E
    //La méthode présentée en cours est préconisée.
}
