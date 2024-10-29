//
// Created by user on 4/17/2024.
//

#include <random>
#include <algorithm>
#include <fstream>

#include "FilmContainerService.h"
#include "../exceptions/FilmContainerServiceException.h"

FilmContainerService::FilmContainerService(FilmRepositoryAbstract &source): source(source) {
    cos = {};
}

void FilmContainerService::addFilmAfterTitle(const string &title) {
    const Film& film = source.getFilmByTitle(title);
    auto iterator = std::find_if(cos.begin(), cos.end(), [&title](const Film &f) -> bool {
        return f.getTitle() == title;
    });
    if (iterator == cos.end()) {
        cos.push_back(film);
        notify();
        return;
    }
    throw FilmContainerServiceException("Film already exists!");
}

void FilmContainerService::emptyContainer() {
    cos.clear();
    notify();
}

void FilmContainerService::generateFilms(int numberOfFilms) {
    const vector<Film>& films = source.findAllFilms();
    int len = (int) films.size();

    std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution<> dist{0, len - 1};

    for (int i = 0; i < numberOfFilms; i++) {
        int index = dist(mt);
        const Film& film = films[index];
        auto iterator = std::find_if(cos.begin(), cos.end(), [&film](const Film &f) -> bool {
            return f == film;
        });
        if (iterator == cos.end()) {
            cos.push_back(film);
        }
    }
    notify();
}

void FilmContainerService::exportFilms(const string &filename) {
    std::ofstream file(filename + ".csv");

    for (const Film &film : cos) {
        file << film.getTitle() << "," << film.getGenre() << "," << film.getYearOfRelease() << "," << film.getPrincipalActor() << "\n";
    }

    file.close();
}

int FilmContainerService::getNumberOfFilms() const noexcept {
    return (int) cos.size();
}

const vector<Film> &FilmContainerService::getAllFilms() const noexcept {
    return cos;
}
