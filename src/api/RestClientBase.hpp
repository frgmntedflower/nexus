//
// Created by FrgmntedFlower on 8/22/2025.
//

#ifndef NEXUS_RESTCLIENT_H
#define NEXUS_RESTCLIENT_H

#include <cpr/cpr.h>
#include <string>

namespace api {

    class RestClientBase {
        std::string apiUrl;

    public:
        explicit RestClientBase(std::string hostUrl)
            : apiUrl(std::move(hostUrl)) {}

        // GET request
        cpr::Response get(const std::string& path) const {
            return cpr::Get(cpr::Url{apiUrl + path});
        }

        // POST request with parameters
        cpr::Response post(const std::string& path, const cpr::Parameters& params) const {
            return cpr::Post(cpr::Url{apiUrl + path}, params);
        }

        // PUT request with parameters
        cpr::Response put(const std::string& path, const cpr::Parameters& params) const {
            return cpr::Put(cpr::Url{apiUrl + path}, params);
        }

        // DELETE request
        cpr::Response del(const std::string& path) const {
            return cpr::Delete(cpr::Url{apiUrl + path});
        }
    };

} // namespace api

#endif // NEXUS_RESTCLIENT_H
