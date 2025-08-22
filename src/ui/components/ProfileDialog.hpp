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

class ProfileDialog final : public QDialog {
    Q_OBJECT
public:
    explicit ProfileDialog(QWidget* parent = nullptr)
        : QDialog(parent)
    {
        setWindowTitle("Profile");
        setMinimumSize(400, 300);

        auto* mainLayout = new QVBoxLayout(this);

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

        auto* emailLabel = new QLabel("Email:", this);
        auto* emailEdit = new QLineEdit(this);
        emailEdit->setText("lulu@example.com");

        mainLayout->addWidget(emailLabel);
        mainLayout->addWidget(emailEdit);

        // Public Key
        auto* publicKeyLabel = new QLabel("Public Key Path:", this);
        auto* publicKeyEdit = new QLineEdit(this);
        publicKeyEdit->setText("/path/to/public_key.pem");

        auto* openFileButton = new QPushButton("Browse...", this);

        auto* fileLayout = new QHBoxLayout();
        fileLayout->addWidget(publicKeyEdit);
        fileLayout->addWidget(openFileButton);

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

        mainLayout->addWidget(publicKeyLabel);
        mainLayout->addLayout(fileLayout);

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
