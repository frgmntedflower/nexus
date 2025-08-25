//
// Created by FrgmntedFlower on 8/22/2025.
//
#include "main_ui.h"
#include <QApplication>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QListWidget>
#include <QSplitter>
#include <QScrollBar>
#include <QMainWindow>
#include <QToolBar>
#include <QLabel>
#include <QtSvg/qsvgrenderer.h>
#include <QPainter>

#include "components/NewChatDialog.hpp"
#include "components/SettingsDialog.hpp"
#include "components/ProfileDialog.hpp"

class NewChatDialog;

QIcon makeWhiteIcon(const QString &path, int size = 64);
void setup_toolbar(QMainWindow *window);


void setup_ui(QApplication &app, const Config& cfg) {
    auto* window = new QMainWindow();
    window->setWindowTitle("Nexus Chat");
    window->resize(800, 500);

    // Menu bar
    // auto* menuBar = window->menuBar();
    // auto* fileMenu = menuBar->addMenu("File");
    // fileMenu->addAction("Exit", window, &QMainWindow::close);


    setup_toolbar(window);


    // auto* editMenu = menuBar->addMenu("Edit");
    // editMenu->addAction("Preferences", []() {
    //     qDebug("Preferences dialog would open here.");
    // });

    // Central widget
    auto* centralWidget = new QWidget();
    window->setCentralWidget(centralWidget);

    // Splitter: left chat list / right chat area
    auto* splitter = new QSplitter(centralWidget);

    // Profile section
    auto* profileWidget = new QWidget();
    auto* profileLayout = new QHBoxLayout(profileWidget);
    profileLayout->setAlignment(Qt::AlignLeft);

    auto* profilePic = new QLabel();
    QPixmap pix(":/images/default_profile.png");
    pix = pix.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    profilePic->setPixmap(pix);
    profilePic->setFixedSize(40, 40);
    profilePic->setStyleSheet("border-radius: 100px;");

    // Name label
    auto* nameLabel = new QLabel("No User");
    nameLabel->setStyleSheet("font-weight:bold; margin-left: 8px;");

    profileLayout->addWidget(profilePic);
    profileLayout->addWidget(nameLabel);

    auto* chatList = new QListWidget();

    auto* chatWidget = new QWidget();
    auto* chatLayout = new QVBoxLayout(chatWidget);

    auto* chatDisplay = new QTextEdit();
    chatDisplay->setReadOnly(true);

    auto* inputLayout = new QHBoxLayout();
    auto* messageInput = new QLineEdit();
    auto* sendButton = new QPushButton("Send");

    inputLayout->addWidget(messageInput);
    inputLayout->addWidget(sendButton);

    auto* leftPane = new QWidget();
    auto* leftLayout = new QVBoxLayout(leftPane);
    leftLayout->addWidget(profileWidget);
    leftLayout->addWidget(chatList);
    leftLayout->setStretch(1,1);

    chatLayout->addWidget(chatDisplay);
    chatLayout->addLayout(inputLayout);

    splitter->addWidget(leftPane);
    splitter->addWidget(chatWidget);
    splitter->setStretchFactor(1, 3);

    auto* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(splitter);

    // Connect send button
    QObject::connect(sendButton, &QPushButton::clicked, [&]() {
        auto message = messageInput->text().trimmed();
        if (!message.isEmpty()) {
            chatDisplay->append("<div style='background-color:#5c5c5c; padding:5px; border-radius:5px;'><b>You:</b> " + message + "</div>");
            messageInput->clear();
            chatDisplay->verticalScrollBar()->setValue(chatDisplay->verticalScrollBar()->maximum());
        }
    });

    QObject::connect(messageInput, &QLineEdit::returnPressed, sendButton, &QPushButton::click);

    const QString darkStyle = R"(
        QWidget {
            background-color: #2b2b2b;
            color: #ffffff;
            font-family: Arial;
            font-size: 12pt;
        }
        QListWidget {
            background-color: #3c3f41;
            border: none;
        }
        QTextEdit, QLineEdit {
            background-color: #3c3f41;
            color: #ffffff;
            border-radius: 5px;
            border: 1px solid #555555;
        }
        QPushButton {
            background-color: #5c5c5c;
            color: #ffffff;
            border-radius: 5px;
            padding: 5px;
        }
        QPushButton:hover {
            background-color: #707070;
        }

    )";
    app.setStyleSheet(darkStyle);

    window->show();
}

void setup_toolbar(QMainWindow *window) {
    auto *toolbar = window->addToolBar("Nexus Chat");
    toolbar->setIconSize(QSize(32, 32));

    toolbar->setOrientation(Qt::Vertical);
    toolbar->setMovable(false);

    auto *newChatAction = toolbar->addAction(makeWhiteIcon(":/icons/chat-overview.svg"), "New Chat");
    newChatAction->setToolTip("Start a new chat");
    auto *profileAction = toolbar->addAction(makeWhiteIcon(":/icons/profile.svg"), "Profile");
    profileAction->setToolTip("Open Profile");

    const auto spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    toolbar->addWidget(spacer);

    auto *settingsAction = toolbar->addAction(makeWhiteIcon(":/icons/settings-modern.svg"), "Settings");
    settingsAction->setToolTip("Open settings");

    auto* logoutAction = toolbar->addAction(makeWhiteIcon(":/icons/logout.svg"), "Logout");
    logoutAction->setToolTip("Logout User");

    QObject::connect(newChatAction, &QAction::triggered, []() {
        if (NewChatDialog dlg; dlg.exec() == QDialog::Accepted) {
            qDebug("New chat dialog accepted!");
        } else {
            qDebug("New chat dialog canceled!");
        }
    });
    QObject::connect(settingsAction, &QAction::triggered, [window]() {
        if (SettingsDialog dlg(window); dlg.exec() == QDialog::Accepted) {
            qDebug("Settings accepted!");
        } else {
            qDebug("Settings canceled!");
        }
    });
    QObject::connect(profileAction, &QAction::triggered, [window]() {
        if (ProfileDialog dlg(window); dlg.exec() == QDialog::Accepted) {
            qDebug("Profile dialog accepted!");
        } else {
            qDebug("Profile dialog canceled!");
        }
    });
    QObject::connect(logoutAction, &QAction::triggered, []() {
        qDebug("Logout action triggered.");
    });

    toolbar->setStyleSheet(R"(
         QToolBar {
            background-color: transparent;
            border: none;
        }
        QToolButton {
            background-color: transparent;
            border-left: 2px solid transparent;
            padding: 8px;
        }
        QToolButton:hover {
            background-color: #3c3f41;
            border-left: 2px solid #5c5c5c;
        }
    )");
    window->addToolBar(Qt::LeftToolBarArea, toolbar);
}

QIcon makeWhiteIcon(const QString &path, const int size) {
    QPixmap pixmap(size, size);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    QSvgRenderer renderer(path);
    renderer.render(&painter);

    QPixmap whitePixmap(pixmap.size());
    whitePixmap.fill(Qt::transparent);
    QPainter p(&whitePixmap);
    p.setCompositionMode(QPainter::CompositionMode_Source);
    p.drawPixmap(0, 0, pixmap);
    p.setCompositionMode(QPainter::CompositionMode_SourceIn);
    p.fillRect(whitePixmap.rect(), Qt::white);
    p.end();

    return QIcon(whitePixmap);
}