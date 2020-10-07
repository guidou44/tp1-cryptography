//
// Created by Guillaume Doucet on 2020-10-07.
//

#ifndef EX2_ECBOPERATIONMODE_H
#define EX2_ECBOPERATIONMODE_H



#include <string>
#include "Base/OperationModeBase.h"

class ECBOperationMode : protected OperationModeBase {

public:
    std::string encryptDecrypt(const std::string& targetText, const std::string& key);
private:
    static std::string encryptDecryptInternal(const std::string& text, const std::string& key);
};



#endif //EX2_ECBOPERATIONMODE_H
