//
// Created by user on 5/28/2024.
//

#ifndef POO_LAB_10_11_COSREADONLYGUI_H
#define POO_LAB_10_11_COSREADONLYGUI_H

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <qlayout.h>
#include <QMessageBox>
#include <QPainter>
#include <random>
#include <utility>
#include "observer.h"
#include "service/FilmContainerService.h"
#include "exceptions/FilmRepositoryException.h"

class CosReadOnlyGUI : public QWidget, public Observer {
private:
    FilmContainerService& containerService;

    std::map<string, std::pair<int, int>> positions;
    std::map<string, std::pair<int, int>> newPositions;


    static std::pair<int, int> generateRandomPosition(int width, int height) {
        std::mt19937 mt{std::random_device{}()};
        std::uniform_int_distribution<> dist{0, width};
        std::mt19937 mty{std::random_device{}()};
        std::uniform_int_distribution<> disty{0, height};
        return {dist(mt), disty(mty)};
    }

    void paintEvent(QPaintEvent *event) override {
        QPainter p{this};

        for (auto& film : containerService.getAllFilms()) {
            std::pair<int, int> pos;
            if (positions.find(film.getTitle()) == positions.end()) {
                pos = generateRandomPosition(this->width(), this->height());
                positions[film.getTitle()] = {pos.first, pos.second};
            } else {
                pos = positions[film.getTitle()];
            }
            newPositions[film.getTitle()] = {pos.first, pos.second};
            p.drawText(pos.first, pos.second, QString::fromStdString(film.getTitle()));
            p.drawRect(pos.first-5, pos.second-20, 7 * film.getTitle().size(), 40);
        }
        positions = newPositions;
    }


public:
    CosReadOnlyGUI(FilmContainerService& cs) : containerService(cs) {
        this->containerService.addObserver(this);
    }

    void update() override {
        repaint();
    }

    ~CosReadOnlyGUI() override {
        this->containerService.removeObserver(this);
    }
};

#endif //POO_LAB_10_11_COSREADONLYGUI_H
