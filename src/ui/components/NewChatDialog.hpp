#ifndef NEXUS_NEWCHATDIALOG_H
#define NEXUS_NEWCHATDIALOG_H

#pragma once
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QScreen>
#include <QGuiApplication>

class NewChatDialog final : public QDialog {
    Q_OBJECT
public:
    explicit NewChatDialog(QWidget* parent = nullptr)
        : QDialog(parent)
    {
        setWindowTitle("Start new chat");
        setMinimumSize(300, 150);

        auto* mainLayout = new QVBoxLayout(this);

        mainLayout->addStretch();

        auto* fileLayout = new QHBoxLayout();
        auto* addUserEdit = new QLineEdit(this);
        addUserEdit->setPlaceholderText("Enter username...");
        addUserEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

        auto* openFileButton = new QPushButton("Send", this);
        openFileButton->setFixedWidth(100);

        fileLayout->addWidget(addUserEdit, 3);
        fileLayout->addWidget(openFileButton, 1);

        mainLayout->addLayout(fileLayout);

        mainLayout->addStretch();

        auto* buttonLayout = new QHBoxLayout();
        auto* okButton = new QPushButton("Ok", this);
        auto* cancelButton = new QPushButton("Cancel", this);

        connect(okButton, &QPushButton::clicked, this, &NewChatDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &NewChatDialog::reject);

        buttonLayout->addStretch();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);

        mainLayout->addLayout(buttonLayout);

        adjustSize();
        if (parent) {
            move(parent->geometry().center() - rect().center());
        } else {
            const auto screenGeometry = QGuiApplication::primaryScreen()->geometry();
            move(screenGeometry.center() - rect().center());
        }
    }
};

#endif // NEXUS_NEWCHATDIALOG_H
