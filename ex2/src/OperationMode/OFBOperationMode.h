//
// Created by Guillaume Doucet on 2020-10-07.
//

#ifndef EX2_OFBOPERATIONMODE_H
#define EX2_OFBOPERATIONMODE_H


#include "CFBOperationMode.h"

class OFBOperationMode : public CFBOperationMode {
protected:
    void prepareNextEncryptionInput(std::vector<bool>& nextEncryptionInput, const std::vector<bool>& blockResult,
                                    const std::vector<bool>& firstEncryptionResult,
                                    const std::vector<bool>& wordBinary, bool isEncrypting) override;
};


#endif //EX2_OFBOPERATIONMODE_H
