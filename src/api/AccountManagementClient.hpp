//
// Created by aki on 8/22/2025.
//

#ifndef NEXUS_ACCOUNTMANAGEMENTCLIENT_H
#define NEXUS_ACCOUNTMANAGEMENTCLIENT_H

#include "RestClientBase.hpp"

namespace api {

    class AccountManagementClient : public RestClientBase {
    public:
        explicit AccountManagementClient(const std::string& hostUrl)
            : RestClientBase(hostUrl) {}

        cpr::Response login(const std::string& username, const std::string& password) const {
            const cpr::Parameters params{{"username", username}, {"password", password}};
            return post("/account/login", params);
        }

        cpr::Response createAccount(const std::string& username, const std::string& password) const {
            const cpr::Parameters params{{"username", username}, {"password", password}};
            return post("/account/create", params);
        }

        cpr::Response deleteAccount(const std::string& username) const {
            return del("/account/delete/" + username);
        }

        cpr::Response updateAccount(const std::string& username, const std::string& newPassword) const {
            const cpr::Parameters params{{"new_password", newPassword}};
            return put("/account/update/" + username, params);
        }
    };

} // namespace api

#endif // NEXUS_ACCOUNTMANAGEMENTCLIENT_H
