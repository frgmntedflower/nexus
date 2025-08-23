//
// Created by aki on 8/22/2025.
//

#ifndef NEXUS_SETTINGSDIALOG_H
#define NEXUS_SETTINGSDIALOG_H

// SettingsDialog.h
#pragma once
#include <QDialog>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class SettingsDialog final : public QDialog {
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget* parent = nullptr)
        : QDialog(parent)
    {
        setWindowTitle("Settings");
        setMinimumSize(400, 300);

        auto* layout = new QVBoxLayout(this);

        auto* darkModeCheck = new QCheckBox("Enable Dark Mode", this);
        darkModeCheck->setChecked(true); // default value

        auto* notificationsCheck = new QCheckBox("Enable Notifications", this);
        notificationsCheck->setChecked(false);

        layout->addWidget(new QLabel("Application Settings:", this));
        layout->addWidget(darkModeCheck);
        layout->addWidget(notificationsCheck);

        layout->addStretch();

        auto* buttonLayout = new QHBoxLayout();
        auto* okButton = new QPushButton("OK", this);
        auto* cancelButton = new QPushButton("Cancel", this);

        connect(okButton, &QPushButton::clicked, this, &SettingsDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &SettingsDialog::reject);

        buttonLayout->addStretch();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);

        layout->addLayout(buttonLayout);
    }
};


#endif //NEXUS_SETTINGSDIALOG_H