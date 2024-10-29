//
// Created by user on 5/28/2024.
//

#ifndef POO_LAB_10_11_COSCRUDGUI_H
#define POO_LAB_10_11_COSCRUDGUI_H

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <qlayout.h>
#include <QMessageBox>
#include "observer.h"
#include "service/FilmContainerService.h"
#include "exceptions/FilmRepositoryException.h"

class CosCRUDGUI : public QWidget, public Observer {
private:
    FilmContainerService& containerService;

    QListWidget* listCos{};

    QLineEdit* editGenerateCos{};
    QPushButton* btnGenerateCos{};

    QPushButton* btnClearCos{};

    void initGUI() {
        QVBoxLayout* lyMain = new QVBoxLayout;
        listCos = new QListWidget;
        lyMain->addWidget(listCos);

        QHBoxLayout* lyGenerate = new QHBoxLayout;
        lyMain->addLayout(lyGenerate);
        editGenerateCos = new QLineEdit;
        lyGenerate->addWidget(editGenerateCos);
        btnGenerateCos = new QPushButton("Genereaza cos");
        lyGenerate->addWidget(btnGenerateCos);

        btnClearCos = new QPushButton("Goleste cos");
        lyMain->addWidget(btnClearCos);

        this->setLayout(lyMain);
    }

    void connectSignals() {
        QObject::connect(btnGenerateCos, &QPushButton::clicked, this, &CosCRUDGUI::guiGenerateCos);
        QObject::connect(btnClearCos, &QPushButton::clicked, this, &CosCRUDGUI::guiClearCos);
    }

    void reloadCos(vector <Film> films) {
        this->listCos->clear();
        for (const auto& film : films) {
            this->listCos->addItem(QString::fromStdString(film.getTitle()));
        }
    }


public:
    CosCRUDGUI(FilmContainerService& cs) : containerService(cs) {
        initGUI();
        connectSignals();
        reloadCos(containerService.getAllFilms());
        this->containerService.addObserver(this);
    }

    void update() override {
        reloadCos(containerService.getAllFilms());
    }

    void guiGenerateCos() {
        try {
            int nr = editGenerateCos->text().toInt();
            this->containerService.generateFilms(nr);

            QMessageBox::information(this, "Info", QString::fromStdString("Filme generate in cos."));
        }
        catch (FilmRepositoryException& re) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
        }
    }

    void guiClearCos() {
        this->containerService.emptyContainer();

        QMessageBox::information(this, "Info", QString::fromStdString("Cos golit."));
    }

    ~CosCRUDGUI() override{
        delete listCos;
        delete editGenerateCos;
        delete btnGenerateCos;
        delete btnClearCos;
        this->containerService.removeObserver(this);
    }
};

#endif //POO_LAB_10_11_COSCRUDGUI_H
