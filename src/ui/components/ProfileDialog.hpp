//
// Created by aki on 8/22/2025.
//

#ifndef NEXUS_PROFILEDIALOG_H
#define NEXUS_PROFILEDIALOG_H

#pragma once
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>

#include "src/util/key_gen.hpp"

class ProfileDialog final : public QDialog {
    Q_OBJECT
    const bool user_logged_in = false;
    QLineEdit* usernameEdit;
public:
    QString username() const { return usernameEdit->text(); }
    explicit ProfileDialog(QWidget* parent = nullptr)
        : QDialog(parent)
    {
        setWindowTitle("Profile");
        setMinimumSize(400, 300);

        auto* mainLayout = new QVBoxLayout(this);

        if (!user_logged_in) {
            render_no_user_ui(mainLayout);
        } else {
            render_logged_in_ui(mainLayout);
        }
    }

    void render_no_user_ui(QVBoxLayout *mainLayout)
    {
        auto* noUserLabel = new QLabel("Register Account", this);
        noUserLabel->setAlignment(Qt::AlignCenter);
        noUserLabel->setStyleSheet("font-size: 16px; font-weight: bold;");
        mainLayout->addWidget(noUserLabel);

        usernameEdit = new QLineEdit(this);
        usernameEdit->setPlaceholderText("Enter a username...");
        auto* registerButton = new QPushButton("Register", this);
        mainLayout->addWidget(usernameEdit);
        mainLayout->addWidget(registerButton);

        mainLayout->addStretch();

        auto* login = new QLabel("Login", this);
        login->setAlignment(Qt::AlignCenter);
        login->setStyleSheet("font-size: 16px; font-weight: bold;");
        mainLayout->addWidget(login);

        usernameEdit = new QLineEdit(this);
        usernameEdit->setPlaceholderText("Enter auth token...");
        auto* loginButton = new QPushButton("Login", this);
        mainLayout->addWidget(usernameEdit);
        mainLayout->addWidget(loginButton);

        connect(loginButton, &QPushButton::clicked, this, &QDialog::accept);
        connect(registerButton, &QPushButton::clicked, this, &QDialog::accept);
    }

    void render_logged_in_ui(QVBoxLayout *mainLayout)
    {
        auto* profilePicLabel = new QLabel(this);
        QPixmap pix(":/images/default_profile.png");
        pix = pix.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        profilePicLabel->setPixmap(pix);
        profilePicLabel->setFixedSize(80, 80);
        profilePicLabel->setStyleSheet("border-radius: 40px; margin-bottom: 10px;");

        mainLayout->addWidget(profilePicLabel, 0, Qt::AlignHCenter);

        auto* usernameLabel = new QLabel("Username:", this);
        auto* usernameEdit = new QLineEdit(this);
        usernameEdit->setText("Lulu");

        mainLayout->addWidget(usernameLabel);
        mainLayout->addWidget(usernameEdit);

        auto* publicKeyLabel = new QLabel("Public Key Path:", this);

        auto* publicKeyEdit = new QLineEdit(this);
        publicKeyEdit->setText("/path/to/public_key.pem");

        auto* openFileButton = new QPushButton("Browse...", this);
        connect(openFileButton, &QPushButton::clicked, this, [publicKeyEdit, this]() {
            const QString filePath = QFileDialog::getOpenFileName(
                this,
                "Select Public Key File",
                QString(),
                "PEM Files (*.pem);;All Files (*)"
            );

            if (!filePath.isEmpty()) {
                publicKeyEdit->setText(filePath);
            }
        });

        auto* fileLayout = new QHBoxLayout();
        fileLayout->addWidget(publicKeyEdit);
        fileLayout->addWidget(openFileButton);

        auto* noPublicKeyInfo = new QLabel("You don't have a public key?", this);
        noPublicKeyInfo->setStyleSheet("font-size: 14px; color: gray;");
        auto* genPubKey = new QPushButton("Generate public key", this);

        connect(genPubKey, &QPushButton::clicked, this, [publicKeyEdit, this]()
        {
            const QString filePath = QFileDialog::getSaveFileName(
               this,
                "Save Public Key As",
                QString(),
                "PEM Files (*.pem);;All Files (*)"
           );

            const std::string newPubKey = generate_ed25519_public_key(filePath.toStdString());
            if (!newPubKey.empty()) {
                QMessageBox::information(
                    this,
                    "Success",
                    "Public and private key-pair generated and saved.\nSaved under: " + filePath
                    );
            } else {
                QMessageBox::warning(this, "Error", "Failed to generate public key. Please retry.");
            }

            if (!filePath.isEmpty()) {
                publicKeyEdit->setText(filePath);
            }
        });

        auto* genKeyLayout = new QHBoxLayout();
        genKeyLayout->addWidget(noPublicKeyInfo);
        genKeyLayout->addWidget(genPubKey);

        mainLayout->addWidget(publicKeyLabel);
        mainLayout->addLayout(fileLayout);
        mainLayout->addLayout(genKeyLayout);

        mainLayout->addStretch();

        auto* buttonLayout = new QHBoxLayout();
        auto* okButton = new QPushButton("OK", this);
        auto* cancelButton = new QPushButton("Cancel", this);

        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

        buttonLayout->addStretch();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);

        mainLayout->addLayout(buttonLayout);

    }
};

#endif // NEXUS_PROFILEDIALOG_H
