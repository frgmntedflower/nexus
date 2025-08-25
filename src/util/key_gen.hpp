//
// Created by FrgmntedFlower on 8/25/2025.
//

#ifndef NEXUS_KEY_GEN_HPP
#define NEXUS_KEY_GEN_HPP

#include "include/nexus.h"

inline std::string generate_ed25519_public_key(const std::string& installPathForKey)
{
    const std::string sysCmd = R"(ssh-keygen -t ed25519 -C "" -f ")" +
                           installPathForKey + R"(" -N "")";

    if (const int retCode = system(sysCmd.c_str()); retCode != 0) {
        throw std::runtime_error("ssh-keygen failed");
    }

    const std::string pubKeyPath = installPathForKey + ".pub";
    std::ifstream pubKeyFile(pubKeyPath);
    if (!pubKeyFile.is_open()) {
        throw std::runtime_error("Failed to open public key file");
    }

    std::string publicKey((std::istreambuf_iterator(pubKeyFile)),
                          std::istreambuf_iterator<char>());

    return publicKey;
};

#endif //NEXUS_KEY_GEN_HPP