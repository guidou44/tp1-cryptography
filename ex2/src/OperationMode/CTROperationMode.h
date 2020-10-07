//
// Created by Guillaume Doucet on 2020-10-07.
//

#ifndef EX2_CTROPERATIONMODE_H
#define EX2_CTROPERATIONMODE_H


#include "Base/OperationModeBase.h"

class CTROperationMode : protected OperationModeBase {

public:
    std::string encrypt(const std::string& text, const std::string& key, const std::string& iv);
    std::string decrypt(const std::string& text, const std::string& key);
private:
    static std::string encryptDecryptInternal(const std::string& text, const std::string& key, const std::string& iv);
};


#endif //EX2_CTROPERATIONMODE_H
