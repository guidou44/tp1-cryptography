//
// Created by Guillaume Doucet on 2020-10-07.
//

#ifndef EX2_CBCOPERATIONMODE_H
#define EX2_CBCOPERATIONMODE_H


#include "Base/OperationModeBase.h"

class CBCOperationMode : protected OperationModeBase {

public:
    std::string encrypt(const std::string& text, const std::string& key, const std::string& iv);
    std::string decrypt(const std::string& text, const std::string& key);
};

#endif //EX2_CBCOPERATIONMODE_H
