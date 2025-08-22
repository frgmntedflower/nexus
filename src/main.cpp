#include <QApplication>
#include <thread>

#include "../include/nexus.h"
#include "api/RestClientBase.hpp"
#include "ui/main_ui.h"

int main(int argc, char *argv[]) {
    Config cfg;
    cfg.load(std::string("../resources/config.json"));
    QApplication app(argc, argv);
    setup_ui(app, cfg);

    std::thread networkThread([&]() {
        api::RestClientBase client(std::move(cfg.server_url));
    });

    const int result = QApplication::exec();
    if (networkThread.joinable()) {
        networkThread.join();
    }

    return result;
}