#ifndef NEXUS_NEWCHATDIALOG_H
#define NEXUS_NEWCHATDIALOG_H

#pragma once
#include <QDialog>
#include <QCheckBox>
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
        setMinimumSize(400, 300);

        auto* mainLayout = new QVBoxLayout(this);

        auto* addUserEdit = new QLineEdit(this);
        addUserEdit->setText("Enter username...");

        auto* openFileButton = new QPushButton("Send request", this);

        auto* fileLayout = new QHBoxLayout();
        fileLayout->addWidget(addUserEdit);
        fileLayout->addWidget(openFileButton);

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

#endif //NEXUS_NEWCHATDIALOG_H
