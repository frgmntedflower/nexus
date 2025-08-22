//
// Created by aki on 8/22/2025.
//

#pragma once
#ifndef NEXUS_MAIN_H
#define NEXUS_MAIN_H

#include "json.hpp"
#include <fstream>

using json = nlohmann::json;


// ========== Config ========== //
struct Notifications {
    bool sound = true;
    bool popup = true;
};

struct Config {
    std::string username;
    std::string server_url;
    std::string theme;
    Notifications notifications;

    void load(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) return;
        json j;
        file >> j;
        username = j.value("username", "default_user");
        server_url = j.value("server_url", "https://api.example.com");
        theme = j.value("theme", "light");
        notifications.sound = j["notifications"].value("sound", true);
        notifications.popup = j["notifications"].value("popup", true);
    }

    void save(const std::string& path) {
        json j;
        j["username"] = username;
        j["server_url"] = server_url;
        j["theme"] = theme;
        j["notifications"]["sound"] = notifications.sound;
        j["notifications"]["popup"] = notifications.popup;
        std::ofstream file(path);
        file << j.dump(4);
    }
};
// =========================== //

#endif //NEXUS_MAIN_H