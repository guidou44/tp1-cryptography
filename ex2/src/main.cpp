#include <iostream>
#include <vector>
#include <OperationMode/CBCOperationMode.h>
#include <OperationMode/ECBOperationMode.h>
#include <OperationMode/CFBOperationMode.h>
#include <OperationMode/OFBOperationMode.h>
#include <OperationMode/CTROperationMode.h>

using namespace std;
void extractArguments(string& message, string& key, string& operation, string& operationMode, string& iv, int& r, vector<string>& all_args);
void toLowerCase(string& target);
bool messageIsMultipleOf7Bits(const string& message);
void checkInitVector(string &iv);
void checkRArgument(int& r);

int main(int argc, char *argv[]) {

    try {
        //tous les arguments possibles pour ce programme
        string message;
        string key;
        string operation;
        string operationMode;
        string iv;
        int r;
        vector<string> all_args;
        if (argc > 1) {
            all_args.assign(argv + 1, argv + argc); //le premier argument est omis, c'est le nom de l'executable
        }

        if (all_args.size() <= 1) {
            cout << "pas assez d'arguments spécifiés" << endl;
            return 1;
        }

        extractArguments(message, key, operation, operationMode, iv, r, all_args);
        toLowerCase(operation); //mettre en minuscule au cas pour supporter min et maj
        toLowerCase(operationMode); //mettre en minuscule au cas pour supporter min et maj

        //Classes de modes d'operation:
        ECBOperationMode ecb;
        CBCOperationMode cbc;
        CFBOperationMode cfb;
        OFBOperationMode ofb;
        CTROperationMode ctr;
        string result = "Resultat: ";

        if (operationMode == "ecb") {

            bool messageIsValid = messageIsMultipleOf7Bits(message);
            bool keyIsValid = messageIsMultipleOf7Bits(key);
            if (!messageIsValid || !keyIsValid) {
                cout << "[ERROR] le message ou la clef n'a pas une longueur d'un multiple de 7" << endl;
                return 1;
            }
            if (operation == "enc" || operation == "dec") {
                result += ecb.encryptDecrypt(message, key);
            } else {
                cout << "L'opération entrée n'est pas valide." << endl;
            }

        } else if (operationMode == "cbc") {

            bool messageIsValid = messageIsMultipleOf7Bits(message);
            bool keyIsValid = messageIsMultipleOf7Bits(key);
            if (!messageIsValid || !keyIsValid) {
                cout << "[ERROR] le message ou la clef n'a pas une longueur d'un multiple de 7" << endl;
                return 1;
            }
            if (operation == "enc") {

                checkInitVector(iv);
                result += cbc.encrypt(message, key, iv);

            } else if (operation == "dec") {

                result += cbc.decrypt(message, key);

            } else {
                cout << "L'opération entrée n'est pas valide." << endl;
            }

        } else if (operationMode == "cfb") {

            if (operation == "enc") {

                checkInitVector(iv);
                checkRArgument(r);
                result += cfb.encrypt(message, key, iv, r);

            } else if (operation == "dec") {

                checkRArgument(r);
                result += cfb.decrypt(message, key, r);

            } else {
                cout << "L'opération entrée n'est pas valide." << endl;
            }

        } else if (operationMode == "ofb") {

            if (operation == "enc") {

                checkInitVector(iv);
                checkRArgument(r);
                result += cfb.encrypt(message, key, iv, r);

            } else if (operation == "dec") {

                checkRArgument(r);
                result += cfb.decrypt(message, key, r);

            } else {
                cout << "L'opération entrée n'est pas valide." << endl;
            }

        } else if (operationMode == "ctr") {

            bool messageIsValid = messageIsMultipleOf7Bits(message);
            bool keyIsValid = messageIsMultipleOf7Bits(key);
            if (!messageIsValid || !keyIsValid) {
                cout << "[ERROR] le message ou la clef n'a pas une longueur d'un multiple de 7" << endl;
                return 1;
            }

            if (operation == "enc") {

                checkInitVector(iv);
                ctr.encrypt(message, key, iv);

            } else if (operation == "dec") {

                ctr.decrypt(message, key);

            } else {
                cout << "L'opération entrée n'est pas valide." << endl;
            }
        } else {
            cout << "Le mode d'opération entré n'est pas valide." << endl;
        }

        //imprime le resultat sur la console
        cout << result << endl;

    } catch(logic_error& ex) {
        cout << ex.what() << endl;
        return 1;
    }

    return 0;
}

void checkInitVector(string &iv) {
    if (iv.empty()) {
        cout << "aucun vecteur d'initialisation spécifié. Le vecteur suivant est utilisé : ";
        iv = OperationModeBase::generateInitVector(); //generation aleatoire de IV
        cout << iv << endl;
    }
}

void extractArguments(string &message, string &key, string &operation, string &operationMode, string &iv, int &r, vector<string>& all_args) {

    //constantes des nom d'argument:
    const string msgArg = "-msg";
    const string keyArg = "-key";
    const string opArg = "-op";
    const string modeArg = "-mode";
    const string ivArg = "-iv";
    const string rArg = "-r";

    for (unsigned int i = 0; i < all_args.size(); i++) { //extraction des arguments
        if (all_args[i] == msgArg) {
            message = all_args[i+1];
        } else if (all_args[i] == keyArg) {
            key = all_args[i+1];
        } else if (all_args[i] == opArg) {
            operation = all_args[i+1];
        } else if (all_args[i] == modeArg) {
            operationMode = all_args[i+1];
        } else if (all_args[i] == ivArg) {
            iv = all_args[i+1];
        } else if (all_args[i] == rArg) {
            r =std::stoi(all_args[i+1]);
        }
    }
}

void toLowerCase(string &target) {
    for (auto& c : target) {
        c = tolower(c);
    }
}

bool messageIsMultipleOf7Bits(const string &message) {
    vector<string> all7BitsString = OperationModeBase::separateInCharsWordsOfSize(message, OperationModeBase::BLOCK_SIZE);
    for (const auto& word : all7BitsString) {
        if (word.size() != OperationModeBase::BLOCK_SIZE) {
            return false;
        }
    }
    return true;
}

void checkRArgument(int &r) {
    if (r <= 0 || r > 7) {
        cout << "l'argument R n'a pas été spécifié ou  est invalide. L'argumetn suivant est utilisé : ";
        r = OperationModeBase::getRandomRParameter(OperationModeBase::BLOCK_SIZE);
        cout << r << endl;
    }
}

