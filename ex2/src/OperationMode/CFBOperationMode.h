//
// Created by Guillaume Doucet on 2020-10-07.
//

#ifndef EX2_CFBOPERATIONMODE_H
#define EX2_CFBOPERATIONMODE_H


#include "Base/OperationModeBase.h"

class CFBOperationMode : protected OperationModeBase {

public:
    std::string encrypt(const std::string& text, const std::string& key, const std::string& iv, const int& r);
    std::string decrypt(const std::string& text, const std::string& key, const int& r);
protected:
    std::string encryptDecryptInternal(const std::string& text, const std::string& key, const std::string& iv, const int& r, bool isEncrypting);
    static void appendBitsToNextInput(std::vector<bool>& nextEncryptionInput, const std::vector<bool>& bitsToAppend);
    virtual void prepareNextEncryptionInput(std::vector<bool>& nextEncryptionInput, const std::vector<bool>& blockResult,
                                            const std::vector<bool>& firstEncryptionResult, const std::vector<bool>& wordBinary, bool isEncrypting);
};

#endif //EX2_CFBOPERATIONMODE_H
